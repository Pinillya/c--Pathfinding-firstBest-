#ifndef AIAPPLICATION_H
#define AIAPPLICATION_H

#include "BaseApplication.h"
#include <deque>
#include "NPC.h"

///This is the main application class.
///Sets up the scene, and creates the objects that goes in it.

class AIApplication : public BaseApplication{
    public:
        ///Default constructor.
        AIApplication(void);
        ///Default destructor.
        virtual ~AIApplication(void);

    protected:
        ///Sets up the scene.
        ///Creates the camera, NPCs, and sets their target.
        virtual void createScene(void);

        /*///Calls the frame listener in base class.
        ///As well as setting default values.
        virtual void createFrameListener(void);*/

        ///From the base class.
        ///Called after all render targets have had their rendering commands issued.
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        std::deque<NPC*> mNPCList;  ///<List that holds pointers to all the NPCs.
};

#endif // #ifndef AIAPPLICATION_H
