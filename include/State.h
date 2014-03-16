#ifndef STATE_H
#define STATE_H

#include "NPC.h"
class NPC;

///State Machine.
///The different states a NPC can have.

class State{
    public:
        ///Calls a function in the NPC class.
        ///\param npc - the NPC the function will be called in.
        virtual void Execute(NPC* npc)=0;
};

class StateIdle : public State{
    public:
        ///Calls a function in the NPC class.
        ///\param npc - the NPC the function will be called in.
        void Execute(NPC* npc);
};

class StatePatrol : public State{
    public:
        ///Calls a function in the NPC class.
        ///\param npc - the NPC the function will be called in.
        void Execute(NPC* npc);
};

class StateChase : public State{
    public:
        ///Calls a function in the NPC class.
        ///\param npc - the NPC the function will be called in.
        void Execute(NPC* npc);
};

class StateFlee : public State{
    public:
        ///Calls a function in the NPC class.
        ///\param npc - the NPC the function will be called in.
        void Execute(NPC* npc);
};

class StateCombat : public State{
    public:
        ///Calls a function in the NPC class.
        ///\param npc - the NPC the function will be called in.
        void Execute(NPC* npc);
};

#endif // STATE_H
