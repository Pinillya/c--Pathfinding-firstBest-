#ifndef NPC_H
#define NPC_H

#include "BaseApplication.h"
#include <deque>

#include "GameObject.h"
#include "State.h"
class State;

///This is the NPC class.
///Can be either a ninja or a robot.
///This class holds most of the variables.

class NPC : public GameObject{
    public:
        ///Default constructor.
        NPC(Ogre::SceneManager* SceneMgr, Ogre::Real index, Ogre::Vector3 position, Ogre::Vector3 stop);
        ///Default destructor.
        virtual ~NPC();

        ///Updates the class.
        ///Adds time to the animation, and calls the main function in the current state.
        ///\param eventTime - refers to TimeSinceLastFrame.
        void UpdateEntity(Ogre::Real eventTime=0);

        ///Called when in the Patrol state.
        ///Moves to next patrol location.
        void Patrol();

        ///Called when in the Chase state.
        ///Move towards the target.
        void ChaseTarget();

        ///Called when in the Flee state.
        ///Move away from the target.
        void FleeFromTarget();

        ///Called when the NPC should be aware of threats.
        ///Checks if the target is within the fov.
        void Threatened();

        ///Called when the NPC is fleeing.
        ///Checks if the NPC is at a safe distance from the target.
        void Safe();

        ///Called when the NPC is chasing.
        ///Checks if the NPC is close enough to attack.
        void AttackTarget();

        ///Called when it's time to attack.
        ///If still in range, continue to attack, if not, return to chase state.
        void Combat();

        ///Called if hit.
        ///Removes health, calls function when dead.
        void Hit(Ogre::Real hitDamage);

        ///Changes the current state.
        ///And then deletes the old.
        ///\param newState - The state that replaces the current.
        void ChangeState(State* newState);

        ///Set the target.
        ///\param target - The target that replaces the current.
        void SetTarget(NPC* target);

        ///Returns the health.
        ///\return Real - This NPCs health.
        Ogre::Real GetHealth();
    protected:

        ///Sets the next location.
        ///And sets the destination, direction and distance for the entity.
        void NextLocation();

        // State Pointer
        State* mCurrentState;                   ///< The current state the NPC has.

        std::deque<Ogre::Vector3> mWalkList;    ///< The default walk list.

        Ogre::Real mDistanceTimeout;            ///< Timeout checking for the distance.
        Ogre::Real mAttackTimeout;              ///< Timeout between attacks.
        Ogre::Real mDistance;                   ///< Distance from the NPC, to his target point.

        Ogre::Vector3 mDestination;             ///< Destination coordinates.
        Ogre::Real mCurrentSpeed;               ///< Current walk speed.
        Ogre::Real mWalkSpeed;                  ///< Walk speed.
        Ogre::Real mRunSpeed;                   ///< Run speed.

        Ogre::uint mCurrentNode;                ///< The node that the NPC is heading towards.
        NPC* mTarget;                           ///< The target that the NPC will check for.
        bool mAggressive;                       ///< Chase if true, flee if false.

        Ogre::Real mHealth;                     ///< The NPC's health.
        Ogre::Real mAttackDamage;               ///< The NPC's attack damage.
        Ogre::Real mAttackSpeed;                ///< The NPC's attack speed.
        Ogre::Real mAttackRange;                ///< The NPC's attack range.
        Ogre::Real mDefence;                    ///< The NPC's defence.
};

#endif // NPC_H
