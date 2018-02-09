#include "team.h"

#include "../player/player.h"
#include "team_states/team_play.h"
#include <gamelib/physics/collision_detector.h>

namespace SenselessSoccer {

// --------------------------------------------------
// sort_player by distance from ball
// --------------------------------------------------
bool sort_players(SenselessSoccer::Player *p1, SenselessSoccer::Player *p2) {
    return p1->distance_from_ball < p2->distance_from_ball;
}

// ------------------------------------------------------------
// Construct
// ------------------------------------------------------------
Team::Team(GameLib::Physical *p, GameLib::Renderable *r) : GameEntity(p, r), other_team(nullptr) {
    short_pass_range.radius = 200;
    InitState(new TeamStatePlay());
    current_state->OnStart();
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Team::~Team() {
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Team::Update(float dt) {

    // update key players
    set_key_players();

    // base entity
    GameLib::GameEntity::Update(dt);

    // advance state machine
    GameLib::StateMachine::Step(dt);
}

// ------------------------------------------------------------
// AddPlayer
// ------------------------------------------------------------
void Team::AddPlayer(Player *player) {
    players.push_back(player);
    player->my_team = this;
    player->other_team = other_team;
}

// ------------------------------------------------------------
// OnGotPossession
// ------------------------------------------------------------
void Team::OnGotPossession(Player *p) {
    key_players.player_in_possession = p;
}

// ------------------------------------------------------------
// OnLostPossession
// ------------------------------------------------------------
void Team::OnLostPossession(Player *p) {
    if (key_players.player_in_possession == p) {
        key_players.player_in_possession = nullptr;
    }
}

//  --------------------------------------------------
//  set key players
//  --------------------------------------------------
void Team::set_key_players(void) {
    std::sort(key_players.short_pass_candidates.begin(), key_players.short_pass_candidates.end(), sort_players);
}

void Team::SetKit(std::vector<std::pair<sf::Color, sf::Color>> kit) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        (*it)->renderable->SwapColors(kit);
    }
}

} // SenselessSoccer
