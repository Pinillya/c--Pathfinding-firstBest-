#include "AIApplication.h"
#include "Grid.h"

AIApplication::AIApplication(void){}

AIApplication::~AIApplication(void){}

void AIApplication::createScene(void){
    // Default lighting
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

    // Camera
    mCamera->setPosition(90.0f, 280.0f, 535.0f);
    mCamera->pitch(Ogre::Degree(-30.0f));
    mCamera->yaw(Ogre::Degree(-15.0f));


 //---------------------------------------------------------------

    //IllyPart - Making a grid
     Grid *grid = new Grid();

   /// The entety of the helping tools used to mapp the coordination system and making the wall ---Temp---
   Ogre::Entity *ent;
    /// The node the halping tools are attached to ---Temp---
   Ogre::SceneNode *node;
   /// We will use the node list to create all the nodes on the screen.
   std::deque<Ogre::Vector3> mNodeList;

    //Have to have a temp nr to get the size to work with the for loop.
    int tempNum = grid->mNodeList.size();
    for (int i=0; i<tempNum; i++)
    {
        //Here the nodelist of this script picks up the nodelist from the other script. This is just done cause
        //i havnt found an efficiant way of refering to the the other scripts mNodeList yet.
        mNodeList.push_back(grid->mNodeList[i]);

        //Stil have to make them damn fishes here. I want them....
        //Anywayz. They are now using the name generated in the "grid" script.
        ent = mSceneMgr->createEntity(grid->Knott[i], "fish.mesh");
        node = mSceneMgr->getRootSceneNode()->createChildSceneNode(grid->KnottNode[i],
                       mNodeList[i]);
        node->attachObject(ent);
        node->setScale(0.4f, 0.4f, 0.4f);
    }


    int NPCCount = 0; //Will make sure we use the right names for the wall
    std::deque<Ogre::Vector3> start;
    std::deque<Ogre::Vector3> stop;

    for (int i=0; i<tempNum; i++)
    {
       // walkable[i] = grid->walkable[i];
        if (grid->walkable[i] == 4){
            start.push_back(mNodeList[i]);
            //mNPCList.push_back(new Robot(mSceneMgr, NPCCount, mNodeList[i], mNodeList[36], mNodeList[50], 10));
            //makeRobot(i); //Calling the function while giving it the start location
        }
        if (grid->walkable[i] == 5){
            stop.push_back(mNodeList[i]);
            //mNPCList.push_back(new Ninja(mSceneMgr, 1, mNodeList[i]));
            //makeFinish(i); //Calling the function while giving it the end location
        }
        if (grid->walkable[i]== 2 ){
            //makeWall(i, wallcounter); //Calling the function while giving it the position of the wall and the number of walls that has been made.
            //wallcounter++; //One wall made, NEXT! :)
        }
    }
   for (int i= 0; i<=NPCCount; i++)
    {
       mNPCList.push_back(new NPC(mSceneMgr, NPCCount,start[NPCCount], stop[NPCCount]));
    }
   NPCCount ++;

    //Not Illy Part anymore
 //----------------------------------------------------------------




    //for(int i=0; i<1; i++){
   //     mNPCList.push_back(new NPC(mSceneMgr, i, Ogre::Vector3(0.0f, 0.0f, 25.0f + (100*i))));
    //}
    //mNPCList.push_back(new NPC(mSceneMgr, 1, Ogre::Vector3(0.0f, 0.0f, -225.0f)));

    //mNPCList[0]->SetTarget(mNPCList[1]);
    //mNPCList[1]->SetTarget(mNPCList[0]);
}

/*void AIApplication::createFrameListener(void){
    BaseApplication::createFrameListener();
}*/

bool AIApplication::frameRenderingQueued(const Ogre::FrameEvent& evt){
    for(Ogre::uint i=0; i<mNPCList.size(); i++){
        mNPCList[i]->UpdateEntity(evt.timeSinceLastFrame);
    }

    return BaseApplication::frameRenderingQueued(evt);
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        AIApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
