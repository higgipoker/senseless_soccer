#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>

#include <gamelib/gamelib.h>
#include <gamelib/input/keyboard.h>
#include <gamelib/utils/log.h>

#include "ball/ball.h"
#include "game/game.h"
#include "globals.h"
#include "graphics/ball_sprite.h"
#include "graphics/pitch_renderable.h"
#include "graphics/player_sprite.h"
#include "match/match.h"
#include "metrics/metrics.h"
#include "pitch/pitch.h"
#include "player/player.h"
#include "player/player_factory.h"
#include "team/roles/role.h"
#include "team/team.h"

using namespace SenselessSoccer;

const static std::string &senseless_soccer_version = "0.0.1";

// temp testing
std::string filenames[] = {"LEFT_BACK_POSITIONS.pos",
                           "RIGHT_BACK_POSITIONS.pos",
                           "LEFT_CENTER_BACK_POSITIONS.pos",
                           "RIGHT_CENTER_BACK_POSITIONS.pos",
                           "LEFT_CENTER_MIDFIELDER_POSITIONS.pos",
                           "RIGHT_CENTER_MIDFIELDER_POSITIONS.pos",
                           "LEFT_MIDFIELDER_POSITIONS.pos",
                           "RIGHT_MIDFIELDER_POSITIONS.pos",
                           "LEFT_CENTER_ATTACKER_POSITIONS.pos",
                           "RIGHT_CENTER_ATTACKER_POSITIONS.pos"};

std::string playernames[] = {
    "player1", "player2", "player3", "player4", "player5", "player6", "player7", "player8", "player9", "player10",

};

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

        if (str == "--gamelib-version") {
            if (argc >= i) {
                GameLib::Log("GameLib version: " + GameLib::gamelib_version);
                return false;
            }
        }

        else if (str == "--version") {
            if (argc >= i) {
                GameLib::Log("Senseless Soccer Version: " + senseless_soccer_version);
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
    SenselessGame senseless("Senseless Soccer", 1980, 0, 1200, 900, false);
    Globals::sensi = &senseless;
    senseless.working_directory = GetCurrentWorkingDirectory();

    //
    // players
    //
    PlayerFactory player_factory;
    std::vector<Player *> players;
    for (unsigned int i = 0; i < 10; ++i) {
        players.push_back(player_factory.MakePlayer(playernames[i], filenames[i]));
    }

    //
    // team
    //
    Team team1;
    for (auto it = players.begin(); it != players.end(); ++it) {
        team1.AddPlayer(*it);
    }

    //
    // ball
    //
    Ball ball;
    GameLib::Physical ball_physical;
    ball.physical = &ball_physical;
    BallSprite ball_sprite(senseless.working_directory + "/gfx/ball_new.png", 4, 2);
    BallShadowSprite ball_shadow_sprite(senseless.working_directory + "/gfx/ball_shadow.png", 1, 1);
    ball.ConnectSprite(ball_sprite, ball_shadow_sprite);
    ball.SetPosition(1000, 1000, 100);
    Match::ball = &ball;
    Player::ball = &ball;

    //
    // pitch
    //
    Pitch pitch(250, 250, Metrics::MetersToPixels(68.5), Metrics::MetersToPixels(100.5f));

    PitchTiled pitch_renderable(senseless.working_directory + "/gfx/grass_dry.png", senseless.camera);
    pitch.ConnectRenderable(pitch_renderable);
    Player::pitch = &pitch;

    //
    // goals
    //
    GameLib::GameEntity goal_north;
    GameLib::Renderable goal_north_sprite(senseless.working_directory + "/gfx/goal_north.png");
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
    players[0]->AttachInput(&keyboard);

    //
    // test some text
    //
    GameLib::GameEntity text;
    GameLib::Label label(senseless.working_directory + "/fonts/swos.ttf", 20, "senseless soccer " + senseless_soccer_version);
    label.SetPosition(12, 24);
    text.renderable = &label;
    text.physical = new GameLib::Physical();
    text.hud = true;

    //
    // add entities
    //
    senseless.AddEntity(pitch);
    senseless.AddEntity(team1);
    for (auto it = players.begin(); it != players.end(); ++it) {
        senseless.AddEntity(*(*it));
    }
    senseless.AddEntity(ball);
    senseless.AddEntity(goal_north);
    senseless.AddEntity(text);

    //
    // camera
    //
    senseless.camera.view.setSize(1200, 900);
    senseless.camera.SetWorldRect(GameLib::Rectangle(0, 0, 1900, 2600));
    senseless.camera.Follow(&ball);
    // senseless.camera.Follow(player1);

    std::vector<std::string> call;
    call.push_back("support");
    for (auto it = players.begin(); it != players.end(); ++it) {
        (*it)->Call(call);
    }

    //
    // run the game
    //
    senseless.Run(0.001f);

    // cleanup
    delete text.physical;

    GameLib::Log("Exiting successfully");
    return 0;
}
