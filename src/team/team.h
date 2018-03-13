#pragma once

#include <gamelib/game/game_entity.h>
#include <gamelib/math/shapes.h>
#include <gamelib/statemachine/state_machine.h>

#include "../player/player.h"

namespace SenselessSoccer {

/** @brief this is how players know about other players */
struct KeyPlayers {

    /// player in possession
    Player *player_in_possession = nullptr;

    /// closest to ball
    Player *closest_to_ball = nullptr;

    /// player who should receive the pass
    Player *pass_recipient = nullptr;

    /// players in range for a short pass
    std::vector<Player *> short_pass_candidates;

    /// players who are pressing the opposition player
    std::vector<Player *> pressing_players;
};

class Team : public GameLib::StateMachine {
  public:
    /**
     * @brief constuct
     * @param other teams are always constructed in pairs
     */
    Team();

    /**
     * @brief on step
     * @param dt time delta
     */
    void Update(float dt);

    /**
     * @brief add a player
     * @param player pointer to player to add
     */
    void AddPlayer(Player *player);

    /**
     * @brief on player got possession
     */
    void OnGotPossession(Player *p);

    /**
     * @brief on player got possession
     */
    void OnLostPossession(Player *p);

    /**
     * @brief set the kit
     */
    void SetKit(std::vector<std::pair<GameLib::Color, GameLib::Color>> kit);

    /// players
    std::vector<Player *> players;

    /// encapsulate key players
    KeyPlayers key_players;

    /// the other team
    Team *other_team;

    /// side of pitch
    Compass side;

  protected:
    /// short pass range
    GameLib::Circle short_pass_range;

    /**
     * @brief helper set key players
     */
    void set_key_players();
};

} // SenselessSoccer
