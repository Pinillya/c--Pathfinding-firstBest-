#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "BaseApplication.h"

class GameObject{
    public:
        GameObject(Ogre::SceneManager* SceneMgr, Ogre::Real index, Ogre::Vector3 position, Ogre::Vector3 stop);
        virtual ~GameObject();

        ///Updates the class.
        ///Adds time to the animation, and calls the main function in the current state.
        ///\param eventTime - refers to TimeSinceLastFrame.
        virtual void UpdateEntity(Ogre::Real eventTime=0);

        ///Returns the scene node.
        ///\return SceneNode* - The scene node that represents the class.
        Ogre::SceneNode* GetNode();

   protected:
        // Scene Manager
        Ogre::SceneManager* mSceneMgr;          ///< Holds the scene manager from the ogre app.

        // Entity & Scene Node
        Ogre::Entity* mEntity;                  ///< Entity that holds the mesh.
        Ogre::SceneNode* mNode;                 ///< Scene Node that holds the entity.

        // Animation
        Ogre::AnimationState* mAnimationState;  ///< Animation state.
        Ogre::String mIdleAnimation;            ///< The idle animation.
        Ogre::String mAttackAnimation;          ///< The attack animation.

        Ogre::Real mEventTime;                  ///< Holds the time since the last frame.

        Ogre::Real mDirectionTimeout;           ///< Timeout checking for the direction.
        Ogre::Vector3 mDirection;               ///< Direction the NPC will move in.
};

#endif // GAMEOBJECT_H
