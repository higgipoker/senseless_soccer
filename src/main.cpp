/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file filename
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include <gamelib/gamelib.h>
#include <gamelib/input/keyboard.h>
#include <gamelib/utils/converter.h>
#include <gamelib/utils/log.h>

#include "ball/ball.h"
#include "game/game.h"
#include "globals.h"
#include "graphics/ball_sprite.h"
#include "graphics/pitch_renderable.h"
#include "graphics/player_sprite.h"
#include "joysticker/controller.h"
#include "kit/kit_factory.h"
#include "match/match.h"
#include "metrics/metrics.h"
#include "pitch/pitch.h"
#include "player/player.h"
#include "player/player_factory.h"
#include "team/roles/role.h"
#include "team/team.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace SenselessSoccer;

const static std::string senseless_soccer_version = "0.0.1";

// temp testing
static std::string filenames[] = {"LEFT_BACK_POSITIONS.pos",
                                  "RIGHT_BACK_POSITIONS.pos",
                                  "LEFT_CENTER_BACK_POSITIONS.pos",
                                  "RIGHT_CENTER_BACK_POSITIONS.pos",
                                  "LEFT_CENTER_MIDFIELDER_POSITIONS.pos",
                                  "RIGHT_CENTER_MIDFIELDER_POSITIONS.pos",
                                  "LEFT_MIDFIELDER_POSITIONS.pos",
                                  "RIGHT_MIDFIELDER_POSITIONS.pos",
                                  "LEFT_CENTER_ATTACKER_POSITIONS.pos",
                                  "RIGHT_CENTER_ATTACKER_POSITIONS.pos"};

static std::string playernames[] = {
    "player1",  "player2",  "player3",  "player4",  "player5",
    "player6",  "player7",  "player8",  "player9",  "player10",
    "player11", "player12", "player13", "player14", "player15",
    "player16", "player17", "player18", "player19", "player20",
};

void print_license_info() {
  static const std::string notice =
      "\
    ************************************************************************************\n\
    *    Copyright (c) 2018 P. Higgins                                                 *\n\
    ************************************************************************************\n\
    *    This software is provided 'as-is', without any express or implied             *\n\
    *    warranty. In no event will the authors be held liable for any damages         *\n\
    *    arising from the use of this software.                                        *\n\
    *                                                                                  *\n\
    *    Permission is granted to anyone to use this software for any purpose,         *\n\
    *    including commercial applications, and to alter it and redistribute it        *\n\
    *    freely, subject to the following restrictions:                                *\n\
    *                                                                                  *\n\
    *    1. The origin of this software must not be misrepresented; you must not       *\n\
    *       claim that you wrote the original software. If you use this software       *\n\
    *       in a product, an acknowledgment in the product documentation would be      *\n\
    *       appreciated but is not required.                                           *\n\
    *    2. Altered source versions must be plainly marked as such, and must not be    *\n\
    *       misrepresented as being the original software.                             *\n\
    *    3. This notice may not be removed or altered from any source distribution.    *\n\
    ************************************************************************************";
  std::cout << notice << std::endl;
}

// ------------------------------------------------------------
// parse_args
// ------------------------------------------------------------
static int parse_args(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    std::string str(argv[i]);

    if (str == "--gamelib-version") {
      if (argc >= i) {
        GameLib::Log("ss",
                     "GameLib version: ", GameLib::GAMELIB_VERSION.c_str());
        return 1;
      }
    }

    else if (str == "--version") {
      if (argc >= i) {
        GameLib::Log("ss", "Senseless Soccer Version: ",
                     senseless_soccer_version.c_str());
        return 1;
      }
    }
  }

  return 0;
}

// ------------------------------------------------------------
// main
// ------------------------------------------------------------
int main(int argc, char *argv[]) {
  // try to parse args, exit if return code
  if (parse_args(argc, argv)) {
    return 0;
  }

  // show some zlib info
  print_license_info();

  // main game
  SenselessGame game("Senseless Soccer", 1980, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                     false);
  Globals::sensi = &game;

  // a scoped player factory object
  PlayerFactory player_factory;

  // players
  std::vector<Player *> players;
  for (unsigned int i = 0; i < 20; ++i) {
    players.push_back(
        player_factory.MakePlayer(playernames[i], filenames[i % 10]));
  }

  // send all players the "support" call
  std::vector<std::string> call;
  call.push_back("support");
  for (auto player : players) {
    player->Call(call);
  }

  // teams
  Team team1(NORTH);
  Team team2(SOUTH);
  //    for (auto it = players.begin(); it != players.end() - 10; ++it) {
  //        team1.AddPlayer(*it);
  //    }
  //    for (auto it = players.begin() + 10; it != players.end(); ++it) {
  //        team2.AddPlayer(*it);
  //    }
  team2.AddPlayer(players[0]);
  team2.SetKit(KitFactory::GetDefaultRedKit());

  // ball
  BallSprite ball_sprite(game.WorkingDirectory() + "/gfx/ball_new.png", 4, 2);
  BallShadowSprite ball_shadow_sprite(
      game.WorkingDirectory() + "/gfx/ball_shadow.png", 1, 1);
  ball_sprite.shadow = &ball_shadow_sprite;
  GameLib::Physical ball_physical;
  Ball ball(&ball_physical, &ball_sprite);
  ball.SetPosition(200, 200, 0);
  Match::ball = &ball;

  // pitch
  GameLib::Physical pitch_physical;
  PitchTiled pitch_renderable(
      game.WorkingDirectory() + "/gfx/grass_dry.png", game.camera);
  Pitch pitch(&pitch_physical, &pitch_renderable, 100, 100,
              Metrics::MetersToPixels(72), Metrics::MetersToPixels(105));

  // goals
  GameLib::Physical goal_north_physical;
  GameLib::Renderable goal_north_sprite(game.WorkingDirectory() +
                                        "/gfx/goal_north.png");
  GameLib::GameEntity goal_north(goal_north_physical, goal_north_sprite);
  goal_north.anchor_type = GameLib::ANCHOR_NONE;
  goal_north.SetPosition(710, -24);
  goal_north_sprite.z_order = 20;
  goal_north.SetName("goal1");

  // input
  GameLib::Keyboard kb;
  Controller keyboard(&kb);
  players[0]->AttachInput(&keyboard);

  // pick teams!
  players[0]->AddtoTeam(&team2, &team1, &ball, &pitch);

  // test some text
  GameLib::Physical text_physical;
  GameLib::Label label(game.WorkingDirectory() + "/fonts/swos.ttf", 20,
                       "senseless soccer " + senseless_soccer_version);
  label.SetPosition(12, 12);
  GameLib::GameEntity text(text_physical, label);
  text.hud = true;

  // add entities
  game.AddEntity(pitch);
  game.AddEntity(*players[0]);

  //    for (auto it = players.begin(); it != players.end(); ++it) {
  //        senseless.AddEntity(*(*it));
  //    }
  game.AddEntity(ball);
  game.AddEntity(goal_north);
  game.AddEntity(text);

  // camera
  game.camera.Init(WINDOW_WIDTH, WINDOW_HEIGHT);
  game.camera.SetWorldRect(GameLib::Rectangle(0, 0, 1900, 2600));
  game.camera.Follow(&ball);

  // to get window events
  GameLib::WindowEvent event;

  // starts timers etc
  static float dt = 0.01f;

  // main loop
  while (game.running) {
    game.HandleInput(event);
    team1.Update(dt);
    team2.Update(dt);
    game.Simulate(dt);
    game.camera.Update(dt);
    game.OnFrame();
  }

  GameLib::Log("s", "Exiting successfully");
  return 0;
}
