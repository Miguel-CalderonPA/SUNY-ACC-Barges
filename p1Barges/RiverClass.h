/*
Author: Miguel Calderon
Date: February 14 2019
Modifications:  never ending
Date Last Modified: Currently

Purpose: This specification contains the basis for a river object in RiverClass.
It currently contains details for one river map. It allows for map creation,
check collision and speed of river. It contains 10 public methods. 1 private methods and
5 private data members. A summary of the methods appears below.

Assumptions:
1) River Array is 12 X 200 X 4 (width X length x depth)
2) 6 Barges (Ships)


11

Summary of Methods
2 CONSTRUCTORS
RiverClass() -- initializes barge object
RiverClass(string inFile)-- a non - default contructor


2 RIVER METHODS (1 private and 1 public)
bool isCollision(short length,short width, short depth) -- check collision
fillRiver(short river[MAX_WIDTH][MAX_LENGTH][MAX_DEPTH],string inFile); -- fill river


2 PRINT METHODS (mainly testing )
printRiver(short river[MAX_WIDTH][MAX_LENGTH][MAX_DEPTH]) -- print river
void upDateHazard(BargeClass& Barge); -- update hazards

2 CURRENT METHODS
setCurrentSpeed() -- set speed
getCurrentSpeed() -- get speed

3 BARGE INFO METHODS
whichBarge(string name); -- match enum with name
gatherIDs(string IDs[MAX_BARGE]); -- store names
getSurfaceDamage(); -- collect surface hits
*/

#pragma once
#ifndef  RIVER
#define RIVER

//Libaries
#include<string>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<fstream>
#include "ItemType.h"
#include "BargeClass.h"
using namespace std;
enum hazardEnum { NO_HAZARD, VESSEL1, VESSEL2, VESSEL3, VESSEL4, VESSEL5, VESSEL6, ORIG_HAZARD, };
//start of class
class RiverClass
{
public:
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//CONSTRUCTORS (2)
	RiverClass();
	/*
	Pre: just to be instantiated, used for a static river
	Post: Default contructor (RiverClass had been instantiated)
	Purpose:  instantiates an instance of river class using default values
	*/
	RiverClass(string inFile,string IDs[MAX_BARGE]);
	/*
	Pre: needs a file to read in the river from and IDs of vessels on river
	Post: non-Default contructor (River had been instantiated)
	Purpose:  instantiates an object(river) using default values
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//RIVER METHODS (1)


	bool isCollision(BargeClass& barge);
	/*
	Pre: needs barge for name and coords
	Post: return if a hit or not
	Purpose: to let client know if there is a collision
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//CURRENT METHODS (2)

	void setCurrentSpeed();
	/*
	Pre: needs to be called
	Post: updates current speed
	Purpose:  to create new speed
	*/
	short getCurrentSpeed();
	/*
	Pre: needs to be called
	Post: returns current speed
	Purpose: gives number to client so they can calculate damage
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//PRINT METHODS (2)

	void printRiver(/*short river[MAX_WIDTH][MAX_LENGTH][MAX_DEPTH]*/);
	/*
	Pre: to be called
	Post:prints river to output file
	Purpose: show river hazards
	*/

	void upDateHazard(BargeClass& Barge);
	/*
	Pre: needs barge
	Post: updates on map where barge is
	Purpose: testing and printing at end
	*/

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//BARGE INFORMATION METHODS (3)

	hazardEnum whichBarge(string name);
	/*
	Pre: needs a name to compare
	Post: returns enum of matching barge
	Purpose: returns enum of matching vessel
	*/
	void gatherIDs(string IDs[MAX_BARGE]);
	/*
	Pre: needs array of IDs
	Post: stores them and uses them to update positions on river
	Purpose: organizing
	*/
	int getSurfaceDamage();
	/*
	Pre: to be called
	Post:returns number of hits to surface obstacles
	Purpose: give user # of above water damage hits
	*/

protected:






private:
	// PDMs
	short currentSpeed;
	// river array and barge information
	short river[MAX_WIDTH][MAX_LENGTH][MAX_DEPTH];
	string BargeIDs[MAX_BARGE];
	string winners[MAX_BARGE];
	int surfaceDamage; 


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//RIVER METHODS (1) (private)

	void fillRiver(string inFile);
	//string vessel1, vessel2, vessel3, vessel4, vessel5, vessel6;
	/*
	Pre: needs array to fill and a file to get data from
	Post: fills array
	Purpose: to clear board and set hazards
	*/

};

#endif RIVER