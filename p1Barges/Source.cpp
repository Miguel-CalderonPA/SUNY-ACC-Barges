//Libraries
#include<iostream>
#include<string>
#include<fstream>
#include"BargeClass.h"
#include"RiverClass.h"
#include "ItemType.h"

using namespace std;
// CONSTANTS
const string SHIPFILE = "ships.txt";
const string RIVERFILE = "river.txt";
const string OUTFILE = "Result.txt";
const short TEST_BARGE = (short)1;
const short TEST_CURR = (short)1;
const short SLOW = (short)1;
const int HULL_COST = 1000;
const int SURFACE_COST = 50000;


int main()
{
	ifstream din;
	ofstream dout;
	string name;
	int totalBargeCost=0, surfaceCost, hullCost;
	bool done=false;
	short ctDone=0, ctTurns = 0;
	srand(/*time(0)*/SEED);

	BargeClass BargeArr[MAX_BARGE];	
	RiverClass river;
	string BargeIDs[MAX_BARGE];

	short current, slowed;

	din.open(SHIPFILE.c_str());
	
	if (!din) // asks for file
	{
		cout << "File not found" << endl;
		dout << "No file found, no data processed" << endl;

	} // ends main if
	else
	{
		cout << "file found" << endl;

		// store barges to bargeclass and names to river class
		BargeClass::storeBarges(din, BargeArr, BargeIDs);
		river = RiverClass(RIVERFILE, BargeIDs);

		//close input file
		din.close();

		current = TEST_CURR;
		// test to see if beginning position is a hazard
		for (short i = 0; i < MAX_BARGE; i++)
		{
			if ((river.isCollision(BargeArr[i])) && (!BargeArr[i].noTurns()))
			{
				BargeArr[i].damageTaken(current);
			}
		}
		while (ctDone!=MAX_BARGE) // while all 6 are still active
		{
			// changes per turn
			ctTurns++;
			ctDone = 0;
			river.setCurrentSpeed();
			current = river.getCurrentSpeed();
			slowed = current - SLOW;

			//all either drift left right or stay in line
			for (short i = 0; i < MAX_BARGE; i++)
			{
				if (!(BargeArr[i].isDone()))
				{
					BargeArr[i].doDirection(current);

					// if colllision after that take damage
					if ((river.isCollision(BargeArr[i])) && (!BargeArr[i].noTurns()))
					{
						BargeArr[i].damageTaken(current);
					
					}
				} // end if barge done
			} // end turning

			// forwards
			for (short i = 0; i < MAX_BARGE; i++)
			{
				if (!(BargeArr[i].isDone()))
				{
					// if half health one less
					if (BargeArr[i].isHalfHealth())
					{
						for (short j = 0; j < slowed; j++)
						{
							BargeArr[i].moveForward();
							if (river.isCollision(BargeArr[i]))
							{
								BargeArr[i].damageTaken(current);
								
							}

						}// end for half health
					} // end if half healh

					else
					{

						// if !half health move normally
						for (short j = 0; j < current; j++)
						{
							BargeArr[i].moveForward();
							if (river.isCollision(BargeArr[i]))
							{
								BargeArr[i].damageTaken(current);
								
							}
						} // end for !half health
					} // end else  half health

				}// end if for barge done
			} // end for moving forwards
			for (short i = 0; i < MAX_BARGE; i++)
			{// updates final position
				if (BargeArr[i].isSunk())
					river.upDateHazard(BargeArr[i]);
			}


			for (short i = 0; i < MAX_BARGE; i++)
			{// check to see if al barges have completed the river or sunk
				if (BargeArr[i].isDone())
					ctDone++;
				else
					i = MAX_BARGE;

			}
			
		} // end while for if barges done


		// lets user know
		cout << "SIMULATION COMPLETE" << endl;

		// print outs of river and barge information
		river.printRiver();

		dout.open(OUTFILE.c_str());

		for (short i = 0; i < MAX_BARGE; i++)
		{
			dout << "Final Status and Coords" << endl;
			BargeArr[i].printStatus(dout);

			hullCost = (BargeArr[i].totalDamage()*HULL_COST);

			dout << endl << " Damage Cost:" << endl;
			dout << " Barge Damage:       $" << setw(7) << right << hullCost << endl<<endl;
			totalBargeCost = totalBargeCost + hullCost;
			dout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		}

		dout << " Total Barge Damage: $" << setw(7) << right << totalBargeCost << endl;
		surfaceCost = (river.getSurfaceDamage()*SURFACE_COST);
		dout << " Suface Damage:      $"  << setw(7) << right << surfaceCost << endl;
		dout << " Total Cost:         $" << setw(7) << right << totalBargeCost + surfaceCost << endl;
		
		river.printRiver();

		dout.close(); 
	} // end if file found

	system("Pause");

	return -1; 

}// end main
//should create functions down here !!!