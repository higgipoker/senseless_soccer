#include "brain.h"

#include "../player.h"

namespace SenselessSoccer {

//  --------------------------------------------------
//  constructor
//  --------------------------------------------------
Brain::Brain(Player *p) :
    locomotion(p) {
	player = p;
}

//  --------------------------------------------------
//  Step
//  --------------------------------------------------
void Brain::Step(float dt){
	locomotion.UpdateLocomotion(dt);
}

}// namespace SenselessSoccer
