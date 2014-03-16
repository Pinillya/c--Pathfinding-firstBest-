#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "BaseApplication.h"

///Here we will be able to find a way from A to B, HOWEVER we are still not able to backtrack.
class Pathfinding
{
public:
    ///We will call on this in our "updateNextLocation" inside "Scene" to run when we want the Robot to get a new path. (this can be done at any time, just have to clear the mWalkList variable. end is the end location where the robot will end up.
    Pathfinding(Ogre::Vector3 end, int boardSize);
    ~Pathfinding(void);
    /// The list of points we are walking to
    std::deque<Ogre::Vector3> mWalkList;
protected:
    ///The function we will use to check for a new path.
     void  nextPath();

     /// The distance the object has left to travel
     Ogre::Real mDistance;
     /// The direction the object is moving
    Ogre::Vector3 mDirection;
    /// The destination the object is moving towards
    Ogre::Vector3 mDestination;

    ///"canWalk"=1 "cantWalk"=2 "enemie"=3 "start"=4 "end"=5 "tested"=6
    int walkable[100];
    /// We will use the node coordinants created in the "grid" class and add them to this list over open nodes.
    std::deque<Ogre::Vector3> mOpenList;
    ///We make a list over all the nodes we have checked up until now.
    std::deque<Ogre::Vector3> mClosedList;
    ///The current meashured distance
    Ogre::Real mCurrentDistance;
     ///Tests that will lett us find the shortest path to the target location
    Ogre::Real tempDistanceTest[8];
    ///This bool is used to stop the script from continuing to run the pathfinding when the path has been found.
    bool testPathBool;
    /// boardSize is a variable that you will see thruought the classes. It will tell us how big the board is. The size is sett based on the variable value given in "Pathfinding(end,boardSize)"
    int boardSize;
     ///We want to see if a node has been found, if it has, we want to make sure the script does not continue to run.
    bool found;

};

#endif // PATHFINDING_H
