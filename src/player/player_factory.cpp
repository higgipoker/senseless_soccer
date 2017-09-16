#include "player_factory.h"
namespace SenselessSoccer {

// ------------------------------------------------------------
// destruct
// ------------------------------------------------------------
PlayerFactory::~PlayerFactory() {
	for (auto it = players.begin(); it != players.end(); ++it) {
		delete (*it)->renderable->shadow;
		delete (*it)->renderable;
		delete (*it)->physical;
		delete (*it)->role;
		delete *it;
	}
}

// ------------------------------------------------------------
// MakePlayer
// ------------------------------------------------------------
Player *PlayerFactory::MakePlayer(const std::string &entityname, const std::string &role_filename) {

	// things that a player needs
	GameLib::Physical *physical = new GameLib::Physical;
	PlayerSprite *player_sprite = new PlayerSprite("gfx/player/player.png", 6, 24);
	PlayerShadowSprite *player_shadow_sprite = new PlayerShadowSprite("gfx/player/player_shadow.png", 6, 24);
	player_sprite->shadow = player_shadow_sprite;
	Role *role = new Role("data/" + role_filename);

	// set up the player
	Player *player = new Player(physical, player_sprite);
	player->SetName(entityname);
	player->SetPosition(100, 100);
	player->role = role;

	// save for deleting memory later
	players.push_back(player);

	// return the pointer
	return player;
}

} // namespace SenselessSoccer
