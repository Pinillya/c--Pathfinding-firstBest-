#include "State.h"

void StateIdle::Execute(NPC* npc){
    npc->Threatened();
}

void StatePatrol::Execute(NPC* npc){
    npc->Patrol();
    //npc->Threatened();
}

void StateChase::Execute(NPC* npc){
    npc->ChaseTarget();
    npc->AttackTarget();
}

void StateFlee::Execute(NPC* npc){
    npc->FleeFromTarget();
    npc->Safe();
}

void StateCombat::Execute(NPC* npc){
    npc->Combat();
}
