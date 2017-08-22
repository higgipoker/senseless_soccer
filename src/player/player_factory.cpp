#include "player_factory.h"
namespace SenselessSoccer {

PlayerFactory::~PlayerFactory() {
    for(auto it = players.begin(); it != players.end(); ++it) {
        delete(*it)->renderable->shadow;
        delete(*it)->renderable;
        delete(*it)->physical;
        delete(*it)->role;
        delete *it;
    }
}

Player *PlayerFactory::MakePlayer(const std::string &entityname, const std::string &role_filename) {

    // things that a player needs
    GameLib::Physical *physical = new GameLib::Physical;
    PlayerSprite *player_sprite = new PlayerSprite("gfx/player/player.png", 6, 24);
    PlayerShadowSprite *player_shadow_sprite = new PlayerShadowSprite("gfx/player/player_shadow.png", 6, 24);
    //PlayerSprite *player_shadow_sprite = nullptr;
    Role *role = new Role("data/" + role_filename);

    // set up the player
    Player *player = new Player(physical);
    player->SetName(entityname);
    player->ConnectSprite(*player_sprite, *player_shadow_sprite);
    player->SetPosition(100, 100);
    player->role = role;

    // save for deleting memory later
    players.push_back(player);

    // return the pointer
    return player;
}
}
