#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>

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
#include "joysticker/cpu/controller_simulator.h"
#include "kit/kit_factory.h"
#include "match/match.h"
#include "metrics/metrics.h"
#include "pitch/pitch.h"
#include "player/player.h"
#include "player/player_factory.h"
#include "team/roles/role.h"
#include "team/team.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace SenselessSoccer;

const static std::string senseless_soccer_version = "0.0.1";

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
 "player1",  "player2",  "player3",  "player4",  "player5",  "player6",  "player7",  "player8",  "player9",  "player10",
 "player11", "player12", "player13", "player14", "player15", "player16", "player17", "player18", "player19", "player20",
};

// ------------------------------------------------------------
// GetCurrentWorkingDirectory
// ------------------------------------------------------------
std::string GetCurrentWorkingDirectory(void) {
	char path[128];
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
	SenselessGame senseless("Senseless Soccer", 1980, 0, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	Globals::sensi = &senseless;
	senseless.working_directory = GetCurrentWorkingDirectory();

    //
	// players
    //
	PlayerFactory player_factory;
	std::vector<Player *> players;
	for (unsigned int i = 0; i < 20; ++i) {
		players.push_back(player_factory.MakePlayer(playernames[i], filenames[i % 10]));
	}
	std::vector<std::string> call;
	call.push_back("support");
	for (auto it = players.begin(); it != players.end(); ++it) {
		(*it)->Call(call);
	}

    //
	// team
    //
	GameLib::Physical team_physical;
	GameLib::Renderable team_renderable;
	Team team1(&team_physical, &team_renderable);
	Team team2(&team_physical, &team_renderable);
	team1.side = SOUTH;
	team2.side = NORTH;
	for (auto it = players.begin(); it != players.end() - 10; ++it) {
		team1.AddPlayer(*it);
	}
	for (auto it = players.begin() + 10; it != players.end(); ++it) {
		team2.AddPlayer(*it);
	}
	team2.SetKit(KitFactory::GetDefaultBlueKit());

    //
	// ball
    //
	BallSprite ball_sprite(senseless.working_directory + "/gfx/ball_new.png", 4, 2);
	BallShadowSprite ball_shadow_sprite(senseless.working_directory + "/gfx/ball_shadow.png", 1, 1);
	ball_sprite.shadow = &ball_shadow_sprite;
	GameLib::Physical ball_physical;
	Ball ball(&ball_physical, &ball_sprite);
	ball.SetPosition(350, 350, 100);
	Match::ball = &ball;
	Player::ball = &ball;

    //
	// pitch
    //
	GameLib::Physical pitch_physical;
	PitchTiled pitch_renderable(senseless.working_directory + "/gfx/grass_dry.png", senseless.camera);
    Pitch pitch(&pitch_physical, &pitch_renderable, 250, 250, Metrics::MetersToPixels(68.5), Metrics::MetersToPixels(100.5f));
	Player::pitch = &pitch;

    //
	// goals
    //
	GameLib::Physical goal_north_physical;
	GameLib::Renderable goal_north_sprite(senseless.working_directory + "/gfx/goal_north.png");
	GameLib::GameEntity goal_north(&goal_north_physical, &goal_north_sprite);
	goal_north.anchor_type = GameLib::ANCHOR_NONE;
	goal_north.SetPosition(750, -8);
	goal_north_sprite.z_order = 20;
	goal_north.SetName("goal1");

    //
	// input
    //
	Controller keyboard;
	players[0]->AttachInput(&keyboard);

	ControllerSimulator cpu;
	players[1]->AttachInput(&cpu);

    //
	// test some text
    //
	GameLib::Physical text_physical;
	GameLib::Label label(senseless.working_directory + "/fonts/swos.ttf", 20,
                         "senseless soccer " + senseless_soccer_version);
	label.SetPosition(12, 24);
	GameLib::GameEntity text(&text_physical, &label);
	text.hud = true;

    //
	// add entities
    //
	senseless.AddEntity(pitch);
	senseless.AddEntity(team1);
	senseless.AddEntity(team2);

	for (auto it = players.begin(); it != players.end(); ++it) {
		senseless.AddEntity(*(*it));
	}
	senseless.AddEntity(ball);
	senseless.AddEntity(goal_north);
	senseless.AddEntity(text);

    //
	// camera
    //
	senseless.camera.view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	senseless.camera.SetWorldRect(GameLib::Rectangle(0, 0, 1900, 2600));
	senseless.camera.Follow(&ball);

    //
	// mtch
    //
	Match match(&team1, &team2);

    //
	// run the game
    //
	double dt = 0.001f;
	while (senseless.running) {
		match.Update(dt);
		senseless.MainLoop(dt);
	}

	GameLib::Log("Exiting successfully");
	return 0;
}
