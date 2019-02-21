//Libraries
#include "RiverClass.h"
#include "ItemType.h"
//CONSTANTS
const short NUM_SPEEDS = 5;
const short WATERLEVEL = 0;
const short DEPTH1 = 1;
const short DEPTH2 = 2;
const short DEPTH3 = 3;
const short DEFAULT_CURR = (short)1;
const short DEFAULT_SURFACE_DAMAGE = (short)0;
const string BOARD = "Board.txt";
static BargeClass BargeArr[MAX_BARGE];

RiverClass::RiverClass()
{
	currentSpeed = DEFAULT_CURR;
	string IDs[MAX_BARGE] = { "VESSEL1", "VESSEL2", "VESSEL3", "VESSEL4", "VESSEL5", "VESSEL6" };

	for (short i = 0; i < MAX_BARGE; i++)
	{
		winners[i].clear();
		winners[i] = "MIA";
	}
	gatherIDs(IDs);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

RiverClass::RiverClass(string inFile, string IDs[MAX_BARGE])
{
	currentSpeed = DEFAULT_CURR;
	surfaceDamage = DEFAULT_SURFACE_DAMAGE;
	fillRiver(inFile);
	
	for (short i = 0; i < MAX_BARGE; i++)
	{
		winners[i].clear();
		winners[i] = "MIA";
	}

	gatherIDs(IDs); // gather ship IDs

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool RiverClass::isCollision(BargeClass& barge)//short length, short width, short depth)
{
	short width, length, depth, position, position2, position3;
	// gets coords
	width = barge.getWidthCoord();
	length = barge.getLengthCoord();
	depth = barge.getDepthCoord();
	// gets coords to check
	position = river[width][length][WATERLEVEL];
	position2 = river[width][length][DEPTH1];
	position3 = river[width][length][DEPTH2]; 
	// if itself
	if (position == whichBarge(barge.getName()))
	{
		if (barge.getLengthCoord() == MAX_LENGTH)
			winners[whichBarge(barge.getName()) - 1] = barge.getName();

		//cout << "same position" << endl;
		return false;

	} 
	// if a hazard on waterlevel
	else if (position != NO_HAZARD)
	{
		//cout << "Hit waterlevel" << endl;
		if (position == ORIG_HAZARD)
			surfaceDamage++;
		if (barge.getLengthCoord() == MAX_LENGTH)
			winners[whichBarge(barge.getName()) - 1] = barge.getName();
		return true;
	}
	// if a hazard on depth 1
	else if (position2 != NO_HAZARD)
	{
		//cout << "Hit depth 1 " << endl;
		if (barge.getLengthCoord() == MAX_LENGTH)
			winners[whichBarge(barge.getName()) - 1] = barge.getName();
		return true;
	} 
	// if a hazard on depth2
	else if ((position3 != NO_HAZARD) && (barge.isHalfHealth()))
	{
		//cout << "Sinking & Hit depth 2 " << endl;
		
		if (barge.getLengthCoord() == MAX_LENGTH)
			winners[whichBarge(barge.getName()) - 1] = barge.getName();
		return true;
	}
	else // if no hazard simply update and delete old position
	{

		if (barge.getLengthCoord() < MAX_LENGTH)
			upDateHazard(barge); // only updates position if not hit
		else
			winners[whichBarge(barge.getName())-1]=barge.getName();
		return false;
	}

} // end isCollision

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RiverClass::upDateHazard(BargeClass& Barge)
{
	
	if (Barge.isSunk()) // if sunk mark hazard on river
	{  // get last coords
		river[Barge.getPrevWidthCoord()][Barge.getPrevLengthCoord()][WATERLEVEL] = NO_HAZARD;
		switch (whichBarge(Barge.getName()))
		{
		case VESSEL1: river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH2] = VESSEL1;
			river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH3]=VESSEL1; break;
		case VESSEL2: river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH2] = VESSEL2;
			river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH3] = VESSEL2; break;
		case VESSEL3: river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH2] = VESSEL3;
			river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH3] = VESSEL3; break;
		case VESSEL4: river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH2] = VESSEL4;
			river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH3] = VESSEL4; break;
		case VESSEL5: river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH2] = VESSEL5;
			river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH3] = VESSEL5; break;
		case VESSEL6: river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH2] = VESSEL6;
			river[Barge.getWidthCoord()][Barge.getLengthCoord()][DEPTH3] = VESSEL6; break;
		};
		// set active
		Barge.setPrevWidthCoord(Barge.getWidthCoord());
		Barge.setPrevLengthCoord(Barge.getLengthCoord());
	}
	// either way update top level for printout
		river[Barge.getPrevWidthCoord()][Barge.getPrevLengthCoord()][WATERLEVEL] = NO_HAZARD;
		switch (whichBarge(Barge.getName()))
		{
		case VESSEL1: river[Barge.getWidthCoord()][Barge.getLengthCoord()][WATERLEVEL] = VESSEL1; break;
		case VESSEL2: river[Barge.getWidthCoord()][Barge.getLengthCoord()][WATERLEVEL] = VESSEL2; break;
		case VESSEL3: river[Barge.getWidthCoord()][Barge.getLengthCoord()][WATERLEVEL] = VESSEL3; break;
		case VESSEL4: river[Barge.getWidthCoord()][Barge.getLengthCoord()][WATERLEVEL] = VESSEL4; break;
		case VESSEL5: river[Barge.getWidthCoord()][Barge.getLengthCoord()][WATERLEVEL] = VESSEL5; break;
		case VESSEL6: river[Barge.getWidthCoord()][Barge.getLengthCoord()][WATERLEVEL] = VESSEL6; break;
		};
		// remembers last coords
		Barge.setPrevWidthCoord(Barge.getWidthCoord()); 
		Barge.setPrevLengthCoord(Barge.getLengthCoord());
	

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


hazardEnum RiverClass::whichBarge(string name)
{// swa IDs for which vessel
	if (name == BargeIDs[0])
		return VESSEL1;
	else if (name == BargeIDs[1])
		return VESSEL2;
	else if (name == BargeIDs[2])
		return VESSEL3;
	else if (name == BargeIDs[3])
		return VESSEL4;
	else if (name == BargeIDs[4])
		return VESSEL5;
	else if (name == BargeIDs[5])
		return VESSEL6;

} // end whichBarge

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void RiverClass::setCurrentSpeed()
{
	currentSpeed = rand() % NUM_SPEEDS + (short)1; //speeds are 1-5, this gives 0-4 then adds 1
} // end setSpeed

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


short RiverClass::getCurrentSpeed()
{
	return currentSpeed;
}//end getSpeed

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void RiverClass::gatherIDs(string IDs[MAX_BARGE])
{
	for (short i = 0; i < MAX_BARGE; i++)
	{
		BargeIDs[i] = IDs[i];
	}

} // end ids

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int RiverClass::getSurfaceDamage()
{
	return surfaceDamage;
} // end surface damage


void RiverClass::fillRiver(string inFile)
{
	ifstream din;
	short width, length, depth;
	din.open(inFile.c_str());
	if (!din) // asks for file
	{
		cout << "File not found" << endl;
		cout << "No file found, no data processed" << endl;

	} // ends main if
	else
	{

		for (short i = 0; i < MAX_WIDTH; i++)
		{
			for (short j = 0; j < MAX_LENGTH; j++)
			{
				for (short k = 0; k < MAX_DEPTH; k++)
				{
					river[i][j][k] = NO_HAZARD; // create map
				}
			}
		}


		din >> width >> length >> depth;
		while (din)
		{// create hazards
			river[width][length][depth] = ORIG_HAZARD;
			din >> width >> length >> depth;
		}
		din.close();
		printRiver();
	}
}// end fil river

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void RiverClass::printRiver()
{
	ofstream dout;
	dout.open(BOARD.c_str());
	for (short i = 0; i < MAX_DEPTH; i++)
	{
		dout << endl << "Depth:" << i << endl << endl;
		for (short j = 0; j < MAX_LENGTH; j++)
		{
			dout << "Row:" << setw(3) << j << ' ';
			for (short k = 0; k < MAX_WIDTH; k++)
			{
				if (river[k][j][i] == NO_HAZARD) 
					dout << ' ';
				else if (river[k][j][i] == ORIG_HAZARD)
					dout << '-';
				else
						dout << river[k][j][i]; // put actual hazard
			} // end for width
			dout << endl;
		} // end for length
		dout << endl << endl;
		dout << "WINNERS: " << endl;
		for (short i = 0; i < MAX_BARGE; i++)
		{
			dout << winners[i] << ' ' << '(' << i + 1 << ')' << endl;
		} // end for winners

	} // end for river (depth)
	dout.close();
} // end print river




/*void RiverClass::printRiver()
{
	ofstream dout;
	dout.open(BOARD.c_str());
	for (short i = 0; i < MAX_DEPTH; i++)
	{
		dout << endl << "Depth:" << i << endl << endl;
		for (short j = 0; j < MAX_LENGTH; j++)
		{
			dout << "Row:" << setw(3) << j << ' ';
			for (short k = 0; k < MAX_WIDTH; k++)
			{
				dout << river[k][j][i];
			}

			dout << endl;
		
			
		}
		dout << endl << endl;
		dout << "WINNERS: " << endl;
		for (short i = 0; i < MAX_BARGE; i++)
			{
			dout << winners[i]<< ' ' << '(' << i+1 << ')'  << endl;
			}
		
	}



	dout.close();
}*/



