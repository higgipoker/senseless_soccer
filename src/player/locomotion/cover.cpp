#include "cover.h"

#include <gamelib/utils/log.h>
#include "../player.h"

namespace SenselessSoccer {

// --------------------------------------------------
// Cover
// --------------------------------------------------
Cover::Cover(Player *p) : Locomotion(p) { last_ball_sector = -1; }

// --------------------------------------------------
// OnStart
// --------------------------------------------------
void Cover::OnStart() {
  state_over = false;
  destination_reached = false;
}

// --------------------------------------------------
// OnStep
// --------------------------------------------------
void Cover::OnStep(const float dt) {
  int ball_sector = player->pitch->grid.CoordinatesToSector(
      player->ball->physical->position.x, player->ball->physical->position.y);

  if (ball_sector != last_ball_sector) {
    int target_sector = player->role->GetPosition(ball_sector);

    if (target_sector != last_target_sector) {
      last_target_sector = target_sector;
      destination =
          player->pitch->grid.GetSectorCenter(target_sector).vector();
      player->physical->velocity = destination - player->physical->position;

      std::cout << destination.x << ", " << destination.y << std::endl;
    }
    last_ball_sector = ball_sector;
  }

  // check stop condition
  GameLib::Vector3 distance = player->physical->position - destination;
  std::cout << distance.magnitude() << std::endl;
  if (player->physical->position.equals(destination, 10)) {
    player->physical->ResetVelocity();
  }
  //std::cout << player->physical->position.x << ", " << player->physical->position.y << std::endl;
}

// --------------------------------------------------
// OnEnd
// --------------------------------------------------
void Cover::OnEnd() {
  destination = player->physical->position;
  destination_reached = true;
  state_over = true;
}

// --------------------------------------------------
// StateOver
// --------------------------------------------------
bool Cover::StateOver() { return state_over; }

// --------------------------------------------------
// ChangeToNextState
// --------------------------------------------------
void Cover::ChangeToNextState() {}

}  // namespace SenselessSoccer
