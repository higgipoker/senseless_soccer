#include "brain.h"

#include "../player.h"

namespace SenselessSoccer {

//  --------------------------------------------------
//  constructor
//  --------------------------------------------------
Brain::Brain(Player *p) :
	locomotion(p->physical) {
	player = p;
}

//  --------------------------------------------------
//  Step
//  --------------------------------------------------
void Brain::Step(float dt){
	locomotion.UpdateLocomotion(dt);
}

}// namespace SenselessSoccer
