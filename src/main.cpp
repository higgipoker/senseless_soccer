#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <gamelib/gamelib.h>
#include <gamelib/utils/log.h>

#include "graphics/pitch_renderable.h"
#include "graphics/player_sprite.h"
#include "player/player.h"
#include "team/team.h"

#include "ball/ball.h"
#include "game/game.h"
#include "graphics/ball_sprite.h"
#include "match/match.h"
#include "metrics/metrics.h"
#include "pitch/pitch.h"

const static std::string &senseless_soccer_version = "0.0.1";

// ------------------------------------------------------------
// GetCurrentWorkingDirectory
// ------------------------------------------------------------
std::string GetCurrentWorkingDirectory(void) {

  char path[1024];
  getcwd(path, sizeof(path));
  GameLib::Log("Working Directory: " + std::string(path));

  return path;
}

// ------------------------------------------------------------
// parse_args
// ------------------------------------------------------------
static bool parse_args(int argc, char *argv[]) {

  for (unsigned int i = 0; i < argc; ++i) {
    std::string str(argv[i]);

    if (str == "--gamelib_version") {
      if (argc >= i) {
        GameLib::Log("GameLib version: " + GameLib::gamelib_version);
        return false;
      }
    }

    else if (str == "--version") {
      if (argc >= i) {
        GameLib::Log("Version: " + senseless_soccer_version);
        return false;
      }
    }
  }
  return true;
}

// ------------------------------------------------------------
// main
// ------------------------------------------------------------
int main(int argc, char *argv[]) {
  if (!parse_args(argc, argv)) {
    return 0;
  }

  //
  // main game
  //
  GameLib::Game senseless("Senseless Soccer", 1980, 0, 1200, 900, true);
  senseless.working_directory = GetCurrentWorkingDirectory();
  SenselessSoccer::SenselessGame::game = &senseless;

  //
  // players
  //
  GameLib::Physical physical;
  SenselessSoccer::Player player(&physical);
  player.physical = &physical;
  SenselessSoccer::PlayerSprite player_sprite(senseless.working_directory +"/gfx/player/player.png", 6, 24);
  SenselessSoccer::PlayerSprite player_shadow_sprite(senseless.working_directory +"/gfx/player/player_shadow.png", 6, 24);
  player.ConnectSprite(player_sprite, player_shadow_sprite);
  player.SetPosition(100, 100);
  player.SetName("player1");

  //
  // team
  //
  SenselessSoccer::Team team1;
  team1.AddPlayer(&player);

  //
  // ball
  //
  SenselessSoccer::Ball ball;
  GameLib::Physical ball_physical;
  ball.physical = &ball_physical;
  SenselessSoccer::BallSprite ball_sprite(senseless.working_directory +"/gfx/ball_new.png", 4, 2);
  SenselessSoccer::BallShadowSprite ball_shadow_sprite(senseless.working_directory +"/gfx/ball_shadow.png", 1, 1);
  ball.ConnectSprite(ball_sprite, ball_shadow_sprite);
  ball.SetPosition(100, 100, 0);
  SenselessSoccer::Match::ball = &ball;
  SenselessSoccer::Player::ball = &ball;

  //
  // pitch
  //
  SenselessSoccer::Pitch pitch(
      SenselessSoccer::Metrics::MetersToPixels(5),
      SenselessSoccer::Metrics::MetersToPixels(5),
      SenselessSoccer::Metrics::MetersToPixels(68.5),
      SenselessSoccer::Metrics::MetersToPixels(100.5f));

  SenselessSoccer::PitchTiled pitch_renderable(senseless.working_directory +"/gfx/grass_dry.png",senseless.camera);
  pitch.ConnectRenderable(pitch_renderable);

  //
  // goals
  //
  GameLib::GameEntity goal_north;
  GameLib::Renderable goal_north_sprite(senseless.working_directory +"/gfx/goal_north.png");
  GameLib::Physical goal_physical;
  goal_north.physical = &goal_physical;
  goal_north.anchor_type = GameLib::ANCHOR_NONE;
  goal_north.SetPosition(750, -8);
  goal_north.renderable = &goal_north_sprite;
  goal_north_sprite.z_order = 20;
  goal_north.SetName("goal1");

  //
  // input
  //
  GameLib::Keyboard keyboard;
  player.AttachInput(&keyboard);

  //
  // test some text
  //
  GameLib::GameEntity text;
  GameLib::Label label(senseless.working_directory +"/fonts/swos.ttf", 20, "senseless soccer " + senseless_soccer_version);
  label.SetPosition(12, 24);
  text.renderable = &label;
  text.physical = new GameLib::Physical();
  text.hud = true;

  //
  // add entities
  //
  senseless.AddEntity(pitch);
  senseless.AddEntity(team1);
  senseless.AddEntity(player);
  senseless.AddEntity(ball);
  senseless.AddEntity(goal_north);
  senseless.AddEntity(text);

  //
  // camera
  //
  senseless.camera.view.setSize(1200, 900);
  senseless.camera.SetWorldRect(GameLib::Rectangle(0, 0, 1900, 2600));
  senseless.camera.Follow(&ball);
  //senseless.camera.Follow(&player);

  //
  // run the game
  //  
  senseless.Run(0.001f);

  // cleanup
  delete text.physical;

  GameLib::Log("Exiting successfully");
  return 0;
}
