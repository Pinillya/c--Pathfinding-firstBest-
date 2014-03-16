#include "pathfinding.h"
#include "Grid.h"
#include "BaseApplication.h"

using namespace std;

Pathfinding::Pathfinding(Ogre::Vector3 end, int tempboardSize)
{
    //Getting variables ready for use.
    boardSize = tempboardSize;
    Grid *grid = new Grid;              //We need a grid to see what is where.
    testPathBool = true;

    //We want all the walkables needed to fill the board. This is sett from the grids walkable variable. We also want all of the node positions from mNodeList in the grid class.
    for (int i=0; i<boardSize*boardSize; i++){
        walkable[i] = grid->walkable[i];
        mOpenList.push_back(grid->mNodeList[i]);
    }

    mDestination = end;  //Setts the destination ever path will check towards.
    nextPath();                 //Aaaaaaand.... ACTION!
}
Pathfinding::~Pathfinding(void)
{
}

void Pathfinding::nextPath()
{
    //--------------------------------------------------------Current working position!----------------------------------------------------------------
    //So now we have the robot checking in all 8 directions and finding a propper path to the target location. Now, we want to work on a code that makes it able to backtrack
    //to a privious node if it goes into a blocked location. I have a plan!
    //When we are done with that, we want to work on making the grid by hit testing. I think the first thing I will do is merge it with one of the others code.

    found = false; //When the script has found a node it thinks its the shortest path, it will turn this to true. This way it will stop checking for more nodes.

    //Two variables that will make sure the robot doesnt check accross the board.
     bool dontGoUp = false;
     bool dontGoDown = false;
     int noRoomChecker =0;
     int savedBacktrackNode =0;

    for (int i=0; i<boardSize; i++)
    {
        for (int j=0; j<boardSize; j++)
        {
            int currentNode = j+(i*boardSize);
            //Stopping the robot from going outside the boards boarders.
            //BottomLine
            if (currentNode  == boardSize*i){
                 dontGoDown = true;
            }else {
               dontGoDown = false;
            }
            //TopLine (the k variable helps us check the last i option. Ill look into this to make it better later... strange things is happening here due to lack of math knowledge)
            for (int k=0; k<boardSize; k++){
                if (currentNode  == boardSize*k-1){
                     dontGoUp = true;
                     k = boardSize+1;
                }else {
                    dontGoUp = false;
               }
            }

            //Here we find the node we are standing on. (the node will then be named 4"
            //Dont mind the cout's, there will be a few of them right here to show whats going on while I test.
            if (walkable[currentNode] == 4 && testPathBool)
            {
                //Finds the current distance to the end node.
                mDirection = mDestination - mOpenList[currentNode];
                mCurrentDistance = mDirection.normalise();

                //Sets the location as fare away as posible. This way if they dont get a new value
                //they wont be mistaken as the shortest one.
                for (int l=0; l<8;l++){
                    tempDistanceTest[l] = mCurrentDistance *2;
                }

                //Cout before chang. the cout after will be AS they change.
                cout << " " <<  tempDistanceTest[0] << " **BeforeChange** " << "\n";

                //We use a temp to hold the total number for easier use. This variable should be renamed if I come up with a better name....
                //UpDown sideSide
                int temp[8];
                temp[0] = currentNode +1;
                temp[1] = currentNode -1;
                temp[2] = currentNode +boardSize;
                temp[3] = currentNode -boardSize;
                //Corners
                temp[4] = currentNode +boardSize +1;
                temp[5] = currentNode -boardSize +1;
                temp[6] = currentNode +boardSize - 1;
                temp[7] = currentNode -boardSize - 1;
//---------------------------------------------------------********Checking nodes********---------------------------------------------------------
                //Sidenote to meeeee:
                //Hi Illy, try to put walkable[temp[n]] == 1 || walkable[temp[n]] == 5) && (temp[0] >= 0 && temp[n] < boardSize* boardSize) as the standar check, then add   if (n == 0 || n== 4 || n == 5){

                //Here we will check witch distance is the shortest.
                if (!found)
                {
                    cout << " \n            BEGIN chacking nodes              \n";  //This cout makes the whole thing so much easier to see. :)
                   //int  noRoomChecker = 0; //Will check if there is actually any nodes that the robot can walk to.
                    for (int n=0; n< 8; n++){ //There are 8 temps we need to check. Lets do eeeeet!
                        if (n == 0 || n== 4 || n == 5){ //First we need to make sure that if the robot wants to check UP, but is at the top of the board, it -cant- check that way
                            //     1: is the robot looking at a node it can walk on?                    2: is it within the boards boarders?                 //Is the robot trying to go up while being at the top?
                            if((walkable[temp[n]] == 1 || walkable[temp[n]] == 5) && (temp[0] >= 0 && temp[n] < boardSize* boardSize) && !dontGoUp)
                            {
                                mDirection = mDestination - mOpenList[temp[n]];  //Checks the distance for the node we are checking
                                 tempDistanceTest[n] = mDirection.normalise();  //Adds the distance to the  tempDistanceTest variable that will be used later to check witch node has the shortest traveling distance.
                                cout << " " <<  tempDistanceTest[n] << " *** tempDistanceTest "<< n << "*** " << "\n";
                            } else {
                                noRoomChecker++;
                            }
                        }
                        else if (n == 1 || n== 6 || n == 7){ //As above we need to make sure that if the robot wants to check DOWN, and its at the bottom of the board, it cant do it.
                            if((walkable[temp[n]] == 1 || walkable[temp[n]] == 5) && (temp[0] >= 0 && temp[n] < boardSize* boardSize) && !dontGoDown)
                            {
                                mDirection = mDestination - mOpenList[temp[n]];
                                 tempDistanceTest[n] = mDirection.normalise();
                                cout << " " <<  tempDistanceTest[n] << " *** tempDistanceTest "<< n << "*** " << "\n";
                            }else {
                                noRoomChecker++;
                            }
                        }
                       else if((walkable[temp[n]] == 1 || walkable[temp[n]] == 5) && (temp[0] >= 0 && temp[n] < boardSize* boardSize))
                            {
                                mDirection = mDestination - mOpenList[temp[n]];
                                 tempDistanceTest[n] = mDirection.normalise();
                                cout << " " <<  tempDistanceTest[n] << " *** tempDistanceTest "<< n << "*** " << "\n";
                            } else {
                                noRoomChecker++;
                            }

                        //If there is none of the above that will work, we are stuck! Lets try to backtrack
                        if (noRoomChecker == 8)
                        {
                            //mWalkList.clear();
                            //mOpenList.clear();
                            cout << " Size" << mClosedList.size() << "\n";
                            /*
                            for (int p=0; p<mClosedList.size(); p++)
                            {
                                mOpenList[p] = mClosedList[p];
                            }
                            currentNode = savedBacktrackNode;
                            mDirection = mDestination - mOpenList[currentNode];
                            mCurrentDistance = mDirection.normalise();

                            for (int l=0; l<8;l++){
                                tempDistanceTest[l] = mCurrentDistance *2;
                            }
                            mDirection = mDestination - mOpenList[temp[currentNode]];
                            tempDistanceTest[1] = mDirection.normalise();
                           // i = 0;
                            //j = 0;
                            //mDirection = mDestination - mOpenList[currentNode];
                            //tempDistanceTest[currentNode] = mDirection.normalise();*/
                            cout << "*************NO ROOM******************";
                            testPathBool = false;
                            found = true;
                            break;
                        }
                    }
                }

//---------------------------------------------------------********Making the path********---------------------------------------------------------
               if (!found){
                    Ogre::Real lowestNumber =  tempDistanceTest[0];                //Makes a temp variable that will save our currently lowest number
                    int savedMnumber = 0;                                               //Saves a number so that we dont have to make yet another for loop. We also dont want to puch mWalklist without being sure now do we?
                    int forLoopNumber = 0;

                    for (int m=0; m<8; m++)
                    {
                        if (lowestNumber >=  tempDistanceTest[m])
                        {
                                lowestNumber =  tempDistanceTest[m];
                                savedMnumber = temp[m];
                                forLoopNumber = m;
                        }
                    }

                   //Saving the last place the robot could walk another way in case it gets traped
                    for (int n=0; n<8; n++){
                        if (lowestNumber == tempDistanceTest[n])
                        {
                            cout << n << " " << forLoopNumber << "\n";
                            if (n != forLoopNumber)
                            {
                                savedBacktrackNode = currentNode;
                                int tempForSize = mOpenList.size();
                                cout << tempForSize << "TempSize" << "\n" ;
                                /*
                                for (int o=0; o<tempForSize; o++){
                                    mClosedList[o] = mOpenList[o];
                                }*/
                                /*
                                mClosedList.push_back(mOpenList[currentNode]);
                                cout << mClosedList[0] << "ClosedList  \n";
                                cout << mOpenList[currentNode] << "OpenList \n";
                                cout << currentNode << "CurrentNode! \n";*/
                            }
                        }
                    }


                    mCurrentDistance  = lowestNumber;                                //this sets the new distance to the temp one.
                    mWalkList.push_back(mOpenList[savedMnumber]);     //We start plotting a path for the robot to walk

                    if (walkable[savedMnumber] == 5){                                 //Are we at the goal line? Well lest stopp checking then!!
                        cout << "********Finishing*******";
                        testPathBool = false;
                        break;
                    }
                    walkable[savedMnumber] = 4;                                       //The node its going to becomes the new currentNode
                    walkable[currentNode]  = 6;                                         //The node the robot was standing on becomes a 6. aka a used node.

                    cout << savedMnumber  <<" is the shortest one" << "\n\n";
                    found = true;                                                                 //This makes sure the script stops testing this round.
                     nextPath();                                                                   //We runn the whole shabang again and again until we get to node = 5 / the end location

                }
            }
        }
    }
}
