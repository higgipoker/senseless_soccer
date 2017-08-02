#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include <gamelib/gamelib.h>
#include <gamelib/utils/log.h>
#include <SFML/Graphics.hpp>

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
#include "team/roles/role.h"

using namespace SenselessSoccer;

const static std::string &senseless_soccer_version = "0.0.1";

// temp testing
std::string filenames[] = {"LEFT_BACK_POSITIONS.pos",
                           "LEFT_CENTER_ATTACKER_POSITIONS.pos",
                           "LEFT_CENTER_BACK_POSITIONS.pos",
                           "LEFT_CENTER_MIDFIELDER_POSITIONS.pos",
                           "LEFT_MIDFIELDER_POSITIONS.pos",
                           "RIGHT_BACK_POSITIONS.pos",
                           "RIGHT_CENTER_ATTACKER_POSITIONS.pos",
                           "RIGHT_CENTER_BACK_POSITIONS.pos",
                           "RIGHT_CENTER_MIDFIELDER_POSITIONS.pos",
                           "RIGHT_MIDFIELDER_POSITIONS.pos"};

Player* make_player(const std::string &rolefile){
    GameLib::Physical *physical = new GameLib::Physical;
    Player *player = new Player(physical);
    PlayerSprite *player_sprite = new PlayerSprite("gfx/player/player.png", 6, 24);
    PlayerSprite *player_shadow_sprite = new PlayerSprite("gfx/player/player_shadow.png", 6, 24);
    Role *role = new Role("data/"+rolefile);
    player->ConnectSprite(*player_sprite, *player_shadow_sprite);
    player->SetPosition(100, 100);
    player->SetName("player1");
    player->role = role;
    return player;
}

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
  GameLib::Game senseless("Senseless Soccer", 1980, 0, 1200, 900, false);
  senseless.working_directory = GetCurrentWorkingDirectory();
  SenselessGame::game = &senseless;

  //
  // players
  //  
  Player *player1 = make_player(filenames[0]);
  Player *player2 = make_player(filenames[1]);
  Player *player3 = make_player(filenames[2]);
  Player *player4 = make_player(filenames[3]);
  Player *player5 = make_player(filenames[4]);
  Player *player6 = make_player(filenames[5]);
  Player *player7 = make_player(filenames[6]);
  Player *player8 = make_player(filenames[7]);
  Player *player9 = make_player(filenames[8]);
  Player *player10 = make_player(filenames[9]);


  //
  // team
  //
  Team team1;
  team1.AddPlayer(player1);
  team1.AddPlayer(player2);
  team1.AddPlayer(player3);
  team1.AddPlayer(player4);
  team1.AddPlayer(player5);
  team1.AddPlayer(player6);
  team1.AddPlayer(player7);
  team1.AddPlayer(player8);
  team1.AddPlayer(player9);
  team1.AddPlayer(player10);


  //
  // ball
  //
  Ball ball;
  GameLib::Physical ball_physical;
  ball.physical = &ball_physical;
  BallSprite ball_sprite(senseless.working_directory + "/gfx/ball_new.png", 4,
                         2);
  BallShadowSprite ball_shadow_sprite(
      senseless.working_directory + "/gfx/ball_shadow.png", 1, 1);
  ball.ConnectSprite(ball_sprite, ball_shadow_sprite);
  ball.SetPosition(100, 100, 0);
  Match::ball = &ball;
  Player::ball = &ball;

  //
  // pitch
  //
  Pitch pitch(Metrics::MetersToPixels(5), Metrics::MetersToPixels(5),
              Metrics::MetersToPixels(68.5), Metrics::MetersToPixels(100.5f));

  PitchTiled pitch_renderable(
      senseless.working_directory + "/gfx/grass_dry.png", senseless.camera);
  pitch.ConnectRenderable(pitch_renderable);
  Player::pitch = &pitch;

  //
  // goals
  //
  GameLib::GameEntity goal_north;
  GameLib::Renderable goal_north_sprite(senseless.working_directory +
                                        "/gfx/goal_north.png");
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
  // player.AttachInput(&keyboard);

  //
  // test some text
  //
  GameLib::GameEntity text;
  GameLib::Label label(senseless.working_directory + "/fonts/swos.ttf", 20,
                       "senseless soccer " + senseless_soccer_version);
  label.SetPosition(12, 24);
  text.renderable = &label;
  text.physical = new GameLib::Physical();
  text.hud = true;

  //
  // add entities
  //
  senseless.AddEntity(pitch);
  senseless.AddEntity(team1);
  senseless.AddEntity(*player1);
  senseless.AddEntity(*player2);
  senseless.AddEntity(*player3);
  senseless.AddEntity(*player4);
  senseless.AddEntity(*player5);
  senseless.AddEntity(*player6);
  senseless.AddEntity(*player7);
  senseless.AddEntity(*player8);
  senseless.AddEntity(*player9);
  senseless.AddEntity(*player10);
  senseless.AddEntity(ball);
  senseless.AddEntity(goal_north);
  senseless.AddEntity(text);

  //
  // camera
  //
  senseless.camera.view.setSize(1200, 900);
  senseless.camera.SetWorldRect(GameLib::Rectangle(0, 0, 1900, 2600));
  // senseless.camera.Follow(&ball);
  senseless.camera.Follow(player1);

  std::vector<std::string> call;
  call.push_back("cover");
  player1->Call(call);
  player2->Call(call);
  player3->Call(call);
  player4->Call(call);
  player5->Call(call);
  player6->Call(call);
  player7->Call(call);
  player8->Call(call);
  player9->Call(call);
  player10->Call(call);

  //
  // run the game
  //
  senseless.Run(0.001f);

  // cleanup
  delete text.physical;

  GameLib::Log("Exiting successfully");
  return 0;
}
