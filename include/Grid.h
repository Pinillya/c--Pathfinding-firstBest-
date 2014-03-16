#ifndef GRID_H
#define GRID_H

#include "BaseApplication.h"
#include <deque>
using namespace std;

///Grid will make the nodes that will be used to chek if a path is clear. Right now it also helps sett the positions of the items in scene.
class Grid
{
public:
    Grid(void);
    ~Grid(void);

      ///This variable will be used by "Scene" and "Pathfinding" to make the node lists.
    std::deque<Ogre::Vector3> mNodeList;

    ///This is the array of names we will use when making our knots.
   //This is inaficient I know, however the knots are there for my amusement! So this wont be in the final code.
    string Knott[100];
    string KnottNode[100];
     ///"canWalk"=1 "cantWalk"=2 "enemie"=3 "start"=4 "end"=5 "tested"=6, We will use this in "Scene" and in "Pathfinding"
    int walkable[100];
    int worldSize;

};

#endif // GRID_H
