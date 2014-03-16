#include "GameObject.h"

GameObject::GameObject(Ogre::SceneManager* SceneMgr, Ogre::Real index, Ogre::Vector3 position, Ogre::Vector3 stop){
    // Scene Manager
    mSceneMgr = SceneMgr;

    // Entity
    mEntity = mSceneMgr->createEntity("GameObject" + Ogre::StringConverter::toString(index), "robot.mesh");

    // Scene node
    mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Node"  + Ogre::StringConverter::toString(index), position);
    mNode->attachObject(mEntity);

    // Default values
    mDirectionTimeout = 0;
    mDirection = Ogre::Vector3(1.0f, 0.0f, 0.0f);
}

GameObject::~GameObject(){

}

void GameObject::UpdateEntity(Ogre::Real eventTime){
    mEventTime = eventTime;
    mAnimationState->addTime(mEventTime);
}

Ogre::SceneNode* GameObject::GetNode(){
    return mNode;
}
