//Libraries
#include "BargeClass.h"
#include "ItemType.h"
//CONSTANTS
const short WATERLEVEL =(short)0;
const short TITANTIC = (short)1;
const short SUNK = (short)2;
const char SPC = ' ';
const float FLT_TWO= 2.0f;
const short DEFAULT_HEALTH=(short)10;
const short DEFAULT_X = (short)5;
const short DEFAULT_Y = (short)5;
const short FINAL_REST = (short)0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//DEFAULT CONTRUCTOR
BargeClass::BargeClass()
{
	// set default pdms bound to fail 
	lengthCoord = DEFAULT_Y; //rand() % 49; the changes values for entire program
	widthCoord = DEFAULT_X;//rand() % 12; the changes values for entire program
	depthCoord = WATERLEVEL;
	maxHealth = DEFAULT_HEALTH;
	health = DEFAULT_HEALTH;
	name = "Spanish Armada";
	isHazard = false;
	isSinking = false;
}

// NON-DEFAULT CONTRUCTOR
BargeClass::BargeClass(short y, short x, short h, string n)
{
	// sets most pdms to input values
	lengthCoord = y;
	widthCoord = x;
	depthCoord = WATERLEVEL;
	prevDepthCoord = WATERLEVEL;
	prevLengthCoord = y;
	prevWidthCoord = x;
	health = h;
	maxHealth = h;
	name = n;
	isHazard = false;
	isSinking = false;

}

// COPY CONTRUCTOR
BargeClass::BargeClass(const BargeClass& orig)
{
	// copies all pdms to new barge
	lengthCoord = orig.lengthCoord;
	widthCoord = orig.widthCoord;
	depthCoord = orig.depthCoord;
	prevLengthCoord = orig.prevDepthCoord;
	prevWidthCoord = orig.widthCoord;
	prevDepthCoord = orig.depthCoord;
	health = orig.health;
	maxHealth = orig.maxHealth;
	name = orig.name;
	isHazard = orig.isHazard;
	isSinking = orig.isSinking;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//COORDINATE METHODS 

short BargeClass::getWidthCoord()
{
	return widthCoord;
}// end getWidth

short BargeClass::getLengthCoord()
{
	return lengthCoord;
}// end getLength

short BargeClass::getDepthCoord()
{
	return depthCoord;
} // end getDepth


// GET LAST POSITIONS


short BargeClass::getPrevWidthCoord()
{
	return prevWidthCoord;
}// end getWidth

short BargeClass::getPrevLengthCoord()
{
	return prevLengthCoord;
}// end getLength

short BargeClass::getPrevDepthCoord()
{
	return prevDepthCoord;
} // end getDepth


// SET LAST POSITIONS


void BargeClass::setPrevWidthCoord(short newPrevWidth)
{
	prevWidthCoord = newPrevWidth;
}// end setWidth

void BargeClass::setPrevLengthCoord(short newPrevLength)
{
	prevLengthCoord = newPrevLength;
}// end setLength

void BargeClass::setPrevDepthCoord(short newPrevDepth)
{
	prevDepthCoord = newPrevDepth;
} // end getDepth

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END METHODS

bool BargeClass::isInRiver()
{
	return (lengthCoord < MAX_LENGTH);
}// end isInRiver

bool BargeClass::isDone()
{
	return ((!this->isInRiver()) || (this->isSunk()));
}

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 //PRINT METHODS


void BargeClass::printStatus()
{
	cout << endl;
	cout << name << " Status " << endl;

	cout << " Functional: ";
	if (isHazard)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;

	cout << " Sinking:    ";
	if (isSinking)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	cout << " Hull Points:" << health << endl;
	cout << " Starting HP:" << maxHealth << endl;

	cout << endl;
	cout << " Coordinates: " << endl;
	cout<< " (Y)" <<setw(4) << right << this->getLengthCoord() <<": Down river" << endl;
	cout<< " (X)" << setw(4) << right << this->getWidthCoord() << ": Across river" << endl;
	cout<< " (Z)" << setw(4) << right << this->getDepthCoord() << ": in the river" << endl;

}


void BargeClass::printStatus(ofstream& dout)
{
	dout << endl;
	dout << name << " Status " << endl;

	dout << " Functional: ";
	if (isHazard)
		dout << "No" << endl;
	else
		dout << "Yes" << endl;

	dout << " Sinking:    ";
	if (isSinking)
		dout << "Yes" << endl;
	else
		dout << "No" << endl;

	dout << " Hull Points:" << health << endl;
	dout << " Starting HP:" << maxHealth << endl;

	dout << endl;
	dout << " Coordinates: " << endl;
	dout << " (Y)" << setw(4) << right << this->getLengthCoord() << ": Down river" << endl;
	dout << " (X)" << setw(4) << right << this->getWidthCoord() << ": Across river" << endl;
	dout << " (Z)" << setw(4) << right << this->getDepthCoord() << ": in the river" << endl;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//LONE RANGER METHOD

string BargeClass::getName()
{
	return name;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MOVEMENT METHODS (private)

directionEnum BargeClass::GenDirections()
{
	switch (rand() % 3)
	{// num to directionEnum
	case 0: return LEFT; break;
	case 1: return STOP; break;
	case 2: return RIGHT; break;
	};

} // end GenDirections()


void BargeClass::moveLeft()
{
	widthCoord = widthCoord - (short)1;
} // end moveleft


void BargeClass::moveRight()
{
	widthCoord = widthCoord + (short)1;
} // end move right


void BargeClass::setDepthCoord(short newDep)
{
	depthCoord = newDep;
} // end setDepth


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // MOVEMENT METHODS (public)

void BargeClass::moveForward()
{
	if(lengthCoord < MAX_LENGTH)
		lengthCoord = lengthCoord + (short)1;

}// end move forward

void BargeClass::doDirection(short current)
{
	directionEnum direction;
	noLeftOrRight = false;
	
	if ((isSinking) && (current == TITANTIC))
	{
		//cout << "No Movement" << endl;
	}
	else
	{
		direction = GenDirections();
		if (direction == LEFT)
		{
			if (widthCoord > MIN_WIDTH)
			{
				moveLeft();
				//cout << "moved left" << endl;
			}
			else // hit bank of river
			{
				//cout << "hit left bank" << endl;
				damageTaken(current);
			}

		} // end left

		else if (direction == RIGHT)
		{
			if (widthCoord < MAX_WIDTH - (short)1)
			{
				moveRight();
				//cout << "Moved Right" << endl;
			}
			else // hits bank of river
			{
				//cout << "hit right bank" << endl;
				damageTaken(current);
			}
		}// end else right
		else
			noLeftOrRight = true;

	} // end else for moving

} // end doDirection

bool BargeClass::noTurns()
{
	return noLeftOrRight; // so damage isn't taken when it not supposed too
}

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // DAMAGE METHODS


bool BargeClass::isSunk()
{
	if (!isHazard)
	{
		if (health <= FINAL_REST)
		{
			isHazard = true;
			this->setDepthCoord(SUNK); // ship is sunk
		}
	}
	return (isHazard);
} // end isSunk


bool BargeClass::isHalfHealth()
{
	if (!isSinking) // skips math if already completed
	{
		if ((float)health < ((float)maxHealth / FLT_TWO)) // below 50%
		{
			isSinking = true;
			setDepthCoord(TITANTIC); // sink down 1
		}
	}
	return isSinking;

}// end IsHalfHealth


void BargeClass::damageTaken(short current)
{// updates health and flags related to healt
		health = health - current;
		if (health < FINAL_REST)
			health = FINAL_REST;
		isHalfHealth();
		isSunk();
		noLeftOrRight = false;
} // end damageTaken


int BargeClass::totalDamage()
{
	return (int)(maxHealth - health); 
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STATIC METHOD

void BargeClass::storeBarges(ifstream& din, BargeClass BargeArr[MAX_BARGE], string BargeIDs[MAX_BARGE])
{
	string name;
	short length, width, health;
	// store barges
	for (short i = 0; i < MAX_BARGE; i++)
	{
		din >> length >> width >> health;
		getline(din, name);
		BargeIDs[i] = name;
		BargeArr[i] = BargeClass(length, width, health, name);
	}
	
}
