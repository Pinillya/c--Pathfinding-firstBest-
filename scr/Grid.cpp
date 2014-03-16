#include "Grid.h"
#include <sstream>
#include "BaseApplication.h"

using namespace std;

Grid::Grid(void)
{
    //How big does the world look to you?
    worldSize = 10;


    int worldSizeCalcualted = worldSize*worldSize;
    for (int i=0; i < worldSizeCalcualted; i++)
    {
        walkable[i] = 1;
    }

    int makeScene[] = {
             1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,4 ,1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,1, 1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,2,2 ,2 ,2, 2, 1, 1, 1,
             1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,1 ,1 ,1 ,5, 1, 1, 1, 1,
             1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1,
             1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1
            };

    for (int i=0; i <  worldSizeCalcualted ; i++)
    {
        if (makeScene[i])
        {
             walkable[i] = makeScene[i];
        }
    }

//---------------------------------------

    for (int i=0; i<worldSize; i++)
    {
        for (int j=0; j< worldSize; j++)
        {
            //Here we will change the i int value to a char. This will let us scale the grid as big or small as we want.
            //Though strictly speaking, we dont need this section, we can all agree that its much more fun to see the grid we are walking on!

            string iChar;
            string jChar;
            ostringstream convert;
            convert << i;
            iChar = convert.str();
            convert << j;
            jChar = convert.str();


            //Here we make the nodes we are walking on. First we make the flexible name.
            Knott[j+(i*worldSize)]= "Knot" + iChar + "," + jChar;
            KnottNode[j+(i*worldSize)]="KnotNode"+ iChar + "," + jChar;

            //This part is the only thing we really need. But I want to see where Im going so Im adding all of the above.

            mNodeList.push_back(Ogre::Vector3(1.0f*(j*40), -10.0f,  1.0f*(i*40)));
        }
    }
}
Grid::~Grid(void)
{
}
