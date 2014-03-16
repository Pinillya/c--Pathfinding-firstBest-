#include "NPC.h"
//
#include <iostream>
#include "Pathfinding.h"

NPC::NPC(Ogre::SceneManager* SceneMgr, Ogre::Real index, Ogre::Vector3 position, Ogre::Vector3 stop):GameObject(SceneMgr, index, position, stop){
    // State pointer
    mCurrentState = new StatePatrol();

    // Help objects
    Ogre::Entity* ent;
    Ogre::SceneNode* node;

    // Walk nodes
    ent = mSceneMgr->createEntity("1Knot" + Ogre::StringConverter::toString(index), "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot1Node" + Ogre::StringConverter::toString(index), position);
    //mWalkList.push_back(node->getPosition());
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);
    node->translate(Ogre::Vector3(0.0f, -10.0f, 0.0f));

    position = stop;

    ent = mSceneMgr->createEntity("2Knot" + Ogre::StringConverter::toString(index), "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node" + Ogre::StringConverter::toString(index), position);
    //mWalkList.push_back(node->getPosition());
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);
    node->translate(Ogre::Vector3(0.0f, -10.0f, 0.0f));
/*
    ent = mSceneMgr->createEntity("3Knot" + Ogre::StringConverter::toString(index), "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node" + Ogre::StringConverter::toString(index), Ogre::Vector3(position.x - 100.0f, position.y, position.z - 225.0f));
    mWalkList.push_back(node->getPosition());
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);;
    node->translate(Ogre::Vector3(0.0f, -10.0f, 0.0f));
  */



    //-----------------------Pathfinding------------------

    //IllyStart
    Pathfinding *pathfinding = new Pathfinding (stop, 10);
    //Using a temp number to avoid a small warning when using the size in the for loop.
    int tempNumber = pathfinding->mWalkList.size();
    for (int i=0; i<tempNumber; i++)
    {
        mWalkList.push_back(pathfinding->mWalkList[i]);
    }
   //Illy End

    //------------------------------------------------------

    // Animation
    mIdleAnimation = "Idle";
    mAttackAnimation = "Shoot";

    // Default values
    mDistanceTimeout = 0;
    mAttackTimeout = 0;

    mWalkSpeed = 40.0f;
    mRunSpeed = 45.0f;
    mCurrentSpeed = mWalkSpeed;
    mCurrentNode = 0;
    mTarget = NULL;
    mAggressive = false;

    mHealth = 100.0f;
    mAttackDamage = 10.0f;
    mAttackSpeed = 1.0f;
    mAttackRange = 40.0f;
    mDefence = 10.0f;
    //
    //Animation
    mAnimationState = mEntity->getAnimationState(mIdleAnimation);
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);

//    // Default values
//    mDirectionTimeout = 0;
//    mDirection = Ogre::Vector3(1.0f, 0.0f, 0.0f);
}

NPC::~NPC(void){}

void NPC::NextLocation(){
    // Cycle the walk list
    if(mCurrentNode < mWalkList.size()-1){
        mCurrentNode++;
    }else{
        mCurrentNode = 0;
    }

    std::cout << "NEXTLOCATION" << std::endl;
    mDestination = mWalkList[mCurrentNode];

    // Set direction
    mDirection = mDestination - mNode->getPosition();
    mDistance = mDirection.normalise();
}

void NPC::UpdateEntity(Ogre::Real eventTime){
    GameObject::UpdateEntity(eventTime);

    //If the health is under zero, don't update.
    if(mHealth < 0.0f){
        return;
    }

    //Call the current state
   // if(mTarget != NULL){
        mCurrentState->Execute(this);
    //}
}

void NPC::Patrol(){
    if(mAnimationState != mEntity->getAnimationState("Walk")){
        NextLocation();

        mAnimationState = mEntity->getAnimationState("Walk");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);
    }

    Ogre::Real move = mCurrentSpeed * mEventTime;
    mDistance -= move;

    if(mDistance <= 0.0f){
        mNode->setPosition(mDestination);
        NextLocation();

        // Rotation
        Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
        if((1.0f + src.dotProduct(mDirection)) < 0.0001f){
            mNode->yaw(Ogre::Degree(180));
        }else{
            Ogre::Quaternion quat = src.getRotationTo(mDirection);
            mNode->rotate(quat);
        }
    }else{
        mNode->translate(mDirection * move);
    }
}

void NPC::ChaseTarget(){
    Ogre::Real move = 0;
    move = mCurrentSpeed * mEventTime;

    if(mDirectionTimeout > 0.2f){
        mDirection = mTarget->GetNode()->getPosition() - mNode->getPosition();
        mDirection.normalise();

        // Rotation
        Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
        if((1.0f + src.dotProduct(mDirection)) < 0.0001f){
            mNode->yaw(Ogre::Degree(180));
        }else{
            Ogre::Quaternion quat = src.getRotationTo(mDirection);
            mNode->rotate(quat);
        }
        mDirectionTimeout = 0;
    }
    mNode->translate(mDirection * move);
    mDirectionTimeout += mEventTime;
}

void NPC::FleeFromTarget(){
    Ogre::Real move = 0;
    move = mCurrentSpeed * mEventTime;

    if(mDirectionTimeout > 0.2f){
        mDirection = mNode->getPosition() - mTarget->GetNode()->getPosition();
        mDirection.normalise();

        // Rotation
        Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
        if((1.0f + src.dotProduct(mDirection)) < 0.0001f){
            mNode->yaw(Ogre::Degree(180));
        }else{
            Ogre::Quaternion quat = src.getRotationTo(mDirection);
            mNode->rotate(quat);
        }
        mDirectionTimeout = 0;
    }
    mNode->translate(mDirection * move);
    mDirectionTimeout += mEventTime;
}

void NPC::Threatened(){
    if(mTarget->GetHealth() < 0.0f)
        return;

    if(mDistanceTimeout > 0.2f){
        Ogre::Real distance = mNode->getPosition().distance(mTarget->GetNode()->getPosition());
        Ogre::Vector3 directionVector = mTarget->GetNode()->getPosition() - mNode->getPosition();

        mDirection.normalise();
        directionVector.normalise();

        Ogre::Real dot = mDirection.dotProduct(directionVector);
        Ogre::Radian angle = Ogre::Math::ACos(dot);

        if(Ogre::Math::Abs(angle.valueRadians()) <= Ogre::Degree(60).valueRadians() && distance < 500){
            if(mAggressive){
                std::cout << "CHASE" << std::endl;
                ChangeState(new StateChase());

                mAnimationState = mEntity->getAnimationState("Walk");
                mAnimationState->setLoop(true);
                mAnimationState->setEnabled(true);
            }else{
                std::cout << "FLEE" << std::endl;
                ChangeState(new StateFlee());

                mAnimationState = mEntity->getAnimationState("Walk");
                mAnimationState->setLoop(true);
                mAnimationState->setEnabled(true);
            }
            mCurrentSpeed = mRunSpeed;
        }
        mDistanceTimeout = 0;
    }
    mDistanceTimeout += mEventTime;
}

void NPC::Safe(){
    if(mDistanceTimeout > 0.2f){
        Ogre::Real distance = mNode->getPosition().distance(mTarget->GetNode()->getPosition());

        if(distance > 800){
            ChangeState(new StateIdle());

            mAnimationState = mEntity->getAnimationState(mIdleAnimation);
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);

            mCurrentSpeed = mWalkSpeed;
        }
        mDistanceTimeout = 0;
    }
    mDistanceTimeout += mEventTime;
}

void NPC::AttackTarget(){
    if(mDistanceTimeout > 0.2f){
        Ogre::Real distance = mNode->getPosition().distance(mTarget->mNode->getPosition());

        if(distance < mAttackRange){
            ChangeState(new StateCombat());
        }
        mDistanceTimeout = 0;
    }
    mDistanceTimeout += mEventTime;
}

void NPC::Combat(){
    if(mAttackTimeout > mAttackSpeed){
        Ogre::Real distance = mNode->getPosition().distance(mTarget->GetNode()->getPosition());
        if(distance < mAttackRange){
            std::cout << "ATTACK" << std::endl;
            mAnimationState = mEntity->getAnimationState(mAttackAnimation);
            mAnimationState->setLoop(false);
            mAnimationState->setEnabled(true);
            mAnimationState->setTimePosition(0.0f);

            mTarget->Hit(mAttackDamage);
        }else{
            ChangeState(new StateChase());

            mAnimationState = mEntity->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);

            mAttackTimeout = 0;
        }
        mAttackTimeout = 0;
    }
    mAttackTimeout += mEventTime;
}

void NPC::Hit(Ogre::Real hitDamage){
    mHealth -= (hitDamage/100.0f)*(100.0f - mDefence);
    std::cout << "HIT" << std::endl;
    if(mHealth < 0.0f){
        mNode->pitch(Ogre::Degree(90));
        mTarget->SetTarget(NULL);
    }
}

void NPC::ChangeState(State* newState){
    delete mCurrentState;
    mCurrentState = newState;
}

void NPC::SetTarget(NPC* target){
    if(target == NULL){
        mAnimationState = mEntity->getAnimationState("Walk");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);

        mDistance = -0.1f;
        mDestination = mNode->getPosition();

        mCurrentSpeed = mWalkSpeed;
        if(mCurrentNode > 0){
            mCurrentNode--;
        }else{
            mCurrentNode = mWalkList.size()-1;
        }
        ChangeState(new StatePatrol());
    }else{
        mTarget = target;
    }
}

Ogre::Real NPC::GetHealth(){
    return mHealth;
}

