
/*
Author: Miguel Calderon
Date: February 14 2019
Modifications:  many
Date Last Modified: 2/14/19

Purpose: This specification contains the basis for a Barge (ship) in BargeClass.
It currently contains details for one barge and for an array of barges. It allows for movemenet
damage, and position. It contains 26 public methods, 4 Private members, 12 private data members
and 1 public static. A summary of the  methods appears below.

Assumptions:
1) River Array is 12 X 200 X 4 (width X length x depth)
2) 6 Barges (Ships)


30

Summary of Methods
3 CONSTRUCTORS
BargeClass() -- initializes barge object
BargeClass(short y,short x,short h,string n) -- a non - default contructor
BargeClass(BargeClass& orig) - creates a deep copy of orig

9 COORDINATE METHODS
getWidthCoord()const  -- returns width coord
getLengthCoord() const -- returns length coord
getDepthCoord() const --  returns depth coord
getPrevWidthCoord();
getPrevLengthCoord();
getPrevDepthCoord();
setPrevWidthCoord(short newPrevWidth);
setPrevLengthCoord(short newPrevLength);
setPrevDepthCoord(short newPrevDepth);

2 LOCATION METHODS
isInRiver(); -- is out of river
isDone(); -- is out of river or sunk


2 PRINT METHODS 
printCoords() const -- print current coords
printStatus() const -- print overall status

7 MOVEMENT METHODS (3 public)
moveForward(short current,short turn) -- move forward using current
doDirection(short current); -- combined movement function
noTurns(); -- allows class to know whether to take damage

(4 Private)
moveLeft() -- move left 1
moveRight() -- move right 1
setDepthCoord(short newDep) -- sets new depth (for sinking)
GenDirections() -- determines whether to go left/right or nowhere

4 DAMAGE METHODS
isSunk() --  reports if ship is sunk
isHalfHealth() -- report if ship is below 50%
damageTaken(short current) -- substracts damage based on current
totalDamage() -- returns damage occured

1 LONE METHOD
getName()-- return name

1 STATIC METHOD
storeBarges(ifstream& din, BargeClass BargeArr[MAX_BARGE], string BargeIDs[MAX_BARGE]) -- create array of classes
*/

#pragma once
#ifndef BARGE
#define BARGE

//Libaries
#include "ItemType.h"
#include<string>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<fstream>
using namespace std;
// direction enum
enum directionEnum { LEFT, STOP, RIGHT };
// start of class
class BargeClass
{
public:
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//CONSTRUCTORS (3)

	BargeClass();
	/*
	Pre: to be instantiated
	Post: Default contructor (Barge had been instantiated)
	Purpose:  instantiates an object(barge) using default values
	*/

	BargeClass(/*in*/short y,/*in*/ short x,/*in*/ short h,/*in*/ string n); // test
	/*
	Pre: Needs input values to be placed in to contruct
	Post: Non-Default constructor (Barge had been instantiated with input values)
	Purpose: instantiates an object(barge) using input values
	*/

	BargeClass(/*in*/const BargeClass& orig); // test
	/*
	Pre: another object (barge) to copy
	Post: Copy Constructor ( old barge has been saved to new barge
	Purpose: To copy one barge to another
	*/


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//COORDINATES METHODS (10)

	short getWidthCoord();
	/*
	Pre: to be called
	Post: return width coordinate of barge
	Purpose: to allow information to be accessible
	*/

	short getLengthCoord();
	/*
	Pre: to be called
	Post: return length coordinate of barge
	Purpose: to allow information to be accessible
	*/

	short getDepthCoord();
	/*
	Pre: to be called
	Post: return depth coordinate of barge
	Purpose: to allow information to be accessible
	*/



	short getPrevWidthCoord();
	/*
	Pre: to be called
	Post: return prev width coordinate of barge
	Purpose: to allow information to be accessible
	*/

	short getPrevLengthCoord();
	/*
	Pre: to be called
	Post: return prev length coordinate of barge
	Purpose: to allow information to be accessible
	*/

	short getPrevDepthCoord();
	/*
	Pre: to be called
	Post: return prev depth coordinate of barge
	Purpose: to allow information to be accessible
	*/


	void setPrevWidthCoord(short newPrevWidth);
	/*
	Pre: to be called
	Post: set prev width coordinate of barge
	Purpose: to allow information to be accessible
	*/

	void setPrevLengthCoord(short newPrevLength);
	/*
	Pre: to be called
	Post: set prev length coordinate of barge
	Purpose: to allow information to be accessible
	*/

	void setPrevDepthCoord(short newPrevDepth);
	/*
	Pre: to be called
	Post: set prev depth coordinate of barge
	Purpose: to allow information to be accessible
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// LOCATION METHOD (2)

	bool isInRiver();
	/*
	Pre: to be called
	Post: reports if done with death run
	Purpose: allow client to know if barge is out of the river
	*/

	bool isDone();
	/*
	Pre: to be called
	Post: reports if done with death run or died from the death run
	Purpose: allow client to know if barge is done
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// LONE METHOD (1)

	string getName();
	/*
	Pre: to be called
	Post: returns name
	Purpose: give access to the name
	*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// PRINTING METHODS (public) (2)

	
	void printStatus();
	/*
	Pre: to be called
	Post: prints status of barge
	Purpose: to print status of barge
	*/
	
	void printStatus(ofstream& dout);
	/*
	Pre: to be called
	Post: prints status of barge
	Purpose: to print status of barge to output file
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// MOVEMENT METHODS (public) (3)
	void doDirection(short current);
	/*
	Pre: needs current
	Post: combines movement functions 
	Purpose: to turn or not to turn
	*/

	bool noTurns();
	/*
	Pre: to be called
	Post: if no turns don't take damage off for stopped unless movement is 1
	Purpose: not take unnecessarily damage
	*/
	void moveForward();
	/*
	Pre: to be called
	Post: sets new length coord to old + new
	Purpose: to allow information to be accessible
	*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//DAMAGE METHODS (4)

	bool isHalfHealth();
	/*
	Pre: to be called
	Post: lets what's calling know if barge is sinking and changes depth
	Purpose: to see if health is lower than 50%, if lower then sinking
	*/
	

	void damageTaken(/*in*/short current);
	/*
	Pre: damage to be deducted
	Post: new hull health
	Purpose: To substract barge's health when obstacles are hit
	*/

	bool isSunk();
	/*
	Pre: to be called
	Post: lets what's calling know if barge is sunk
	Purpose: to compare health with zero, if lower then sunk
	*/


	int totalDamage();
	/*
	Pre: to be called
	Post: returns HP thats been lost
	Purpose: calculate monetary cost
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//STATIC METHODS (1)


	static void storeBarges(ifstream& din, BargeClass BargeArr[MAX_BARGE], string BargeIDs[MAX_BARGE]);
	/*
	Pre: to be called
	Post: returns stored barge array
	Purpose: easier transfer of data
	*/



protected:






private:

	// Private Data Members
	// coords
	short widthCoord;
	short lengthCoord;
	short depthCoord;
	//clearing river markers
	short prevWidthCoord;
	short prevLengthCoord;
	short prevDepthCoord; 
	//health/names
	short health;
	short maxHealth; // for damage report
	string name;
	// flags
	bool isHazard; //isSunk, but changed name due to ambiguity
	bool isSinking;//isHalfHealth, but changed name due to ambiguity
	bool noLeftOrRight; // so damage isn't unnecessarily taken when stopped after GenDirections

	// MOVEMENT METHODS (private) (4)

	directionEnum GenDirections();
	/*
	Pre: to be called
	Post: returns direction or if not to move left or right
	Purpose: to allow information to be accessible
	*/

	void moveLeft();
	/*
	Pre: to be called
	Post: set coords one to the left
	Purpose: moves barge one to the left
	*/
	void moveRight();
	/*
	Pre: to be called
	Post: set coords one to the right
	Purpose: moves barge one to the right
	*/



	void setDepthCoord(/*in*/short newDep);
	/*
	Pre: to be called
	Post: return depth coordinate of barge
	Purpose: to allow information to be accessible
	*/


};

#endif // !BARGE
