#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <gamelib/gamelib.h>

#include "team/team.h"
#include "player/player.h"
#include "graphics/pitch_renderable.h"
#include "graphics/player_sprite.h"

#include "match/match.h"
#include "pitch/pitch.h"
#include "ball/ball.h"
#include "graphics/ball_sprite.h"
#include "metrics/metrics.h"

const static std::string &senseless_soccer_version = "0.0.1";

using std::cout;
using std::endl;

// ------------------------------------------------------------
// GetCurrentWorkingDirectory
// ------------------------------------------------------------
std::string GetCurrentWorkingDirectory(void) {
	char path[1024];
	getcwd(path, sizeof(path));
	std::cout << "Working Directory: " << path << std::endl;
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
				std::cout <<  "GameLib version: " << GameLib::gamelib_version << std::endl;
				return false;
			}
		}

		else if (str == "--version") {
			if (argc >= i) {
				std::cout <<  "Version: " << senseless_soccer_version << std::endl;
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
	GameLib::Game senseless("Senseless Soccer", 1920, 0, 1200, 900, true);
	senseless.working_directory = GetCurrentWorkingDirectory();

	//
	// players
	//
	SenselessSoccer::Player player;
	GameLib::Physical physical;
	player.physical = &physical;
	SenselessSoccer::PlayerSprite player_sprite("gfx/player/player.png", 6, 24);
	SenselessSoccer::PlayerSprite player_shadow_sprite("gfx/player/player_shadow.png", 6, 24);
	player.ConnectSprite(player_sprite, player_shadow_sprite);
	player.SetPosition(100, 100);
	player.SetName( "player1" );

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
	SenselessSoccer::BallSprite ball_sprite("gfx/ball_new.png", 4, 2);
	SenselessSoccer::BallShadowSprite ball_shadow_sprite("gfx/ball_shadow.png", 1, 1);
	ball.ConnectSprite(ball_sprite, ball_shadow_sprite);
	ball.SetPosition(100, 100, 0);
	SenselessSoccer::Match::ball = &ball;
	SenselessSoccer::Player::ball = &ball;

	//
	// pitch
	//
	SenselessSoccer::Pitch pitch(SenselessSoccer::Metrics::MetersToPixels(5), SenselessSoccer::Metrics::MetersToPixels(5), SenselessSoccer::Metrics::MetersToPixels(68.5), SenselessSoccer::Metrics::MetersToPixels(100.5f));
	SenselessSoccer::PitchTiled pitch_renderable("gfx/grass_dry.png", senseless.camera);
	pitch.ConnectRenderable(pitch_renderable);

	//
	// goals
	//
	GameLib::GameEntity goal_north;
	GameLib::Renderable goal_north_sprite("gfx/goal_north.png");
	GameLib::Physical goal_physical;
	goal_north.physical = &goal_physical;
	goal_north.anchor_type = GameLib::ANCHOR_NONE;
	goal_north.SetPosition(750, -8);
	goal_north.renderable = &goal_north_sprite;
	goal_north_sprite.z_order = 20;
	goal_north.SetName ( "goal1" );

	//
	// input
	//
	GameLib::Keyboard keyboard;
	//player.AttachInput(&keyboard);

	//
	// test some text
	//
// 	GameLib::GameEntity text;
// 	GameLib::Label label ("fonts/swos.ttf", 20, "senseless soccer " + senseless_soccer_version);
// 	label.SetPosition (12, 12);
// 	text.renderable = &label;
// 	text.hud = true;

	//
	// add entities
	//
	senseless.AddEntity(pitch);
	senseless.AddEntity(team1);
	senseless.AddEntity(player);
	senseless.AddEntity(ball);
	senseless.AddEntity(goal_north);

	//
	// camera
	//
	senseless.camera.view.setSize(800, 600);
	senseless.camera.SetWorldRect(GameLib::Rectangle(0, 0, 10000, 10000));
//	senseless.camera.Follow(&ball);
	senseless.camera.Follow(&player);


	std::vector<std::string> params;
	params.push_back("300");
	params.push_back("300");
	player.SetBehaviour("arrive", params);
	//
	// main loop
	//
	const float dt = 0.001f;
	while (senseless.running) {
		senseless.Loop(dt);
	}

	cout << endl;
	cout << "============================" << endl;
	cout << "Exiting successfully" << endl;
	cout << "============================" << endl;
	cout << endl;
	return 0;
}
