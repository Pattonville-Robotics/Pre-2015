#warning "Motors and Sensors Setup for GodCode driver: "MotorL" - Reversed, encoder; "MotorR"; "gyroSensor"; "frontTouch"."

//////////////////////////////////////////////////////////////////////////////////////////
//
//		Green Army Robotics "GodCode" Driver
//		Use: To allow a standard of movement in units.
//		Contributors: Nathan Skelton
//
//////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"
#include <hitechnic-gyro.h>

float happy_angle = 0; // The variable updated by the update_gyroSensor task.

// Left and Right variables let turn direction be readable.
const int left = 0;
const int right = 1;

// Compass directions to allow understandable rotation targets, and to clarify the robots
// direction.
const int north = 0;
const int east = 90;
const int south = 180;
const int west = 270;

// travelDirection is the variable changed by the rotation code to update the direction
// being faced. This allows the determineLocation function to correctly determine
// location.
int travelDirection = north;

// x-coord and y-coord are the variables that the current location is being recorded on
// to. If you wish to start on a different point, this is where you change it accordingly
int Xcoord = 0;
int Ycoord = 0;

// yes and no variables exist to clarify if the functions should calculate the robots
// location.
const int yes = 1;
const int no = 0;

// For most of this to make since, here is a diagram to explain relationships between
// the cardinal directions and the y axis and x axis.
//									North / 0 degrees
//											y-axis
//											//
//											//
//		West / 270 degrees	x-axis	///////////////////	x-axis	East / 90 degrees
//											//
//											//
//											y-axis
//									South / 180 degrees

// This is where you determine the size of a unit. This is the number that will translate
// units to encoder ticks in the move code. To determine:
//	 Take "the size of the unit wanted in Inches" * 360 /
//		"Circumference of drive wheels in Inches"
// Currently, this is a 1:1 inch unit size with a 4 inch diameter wheel.
float unitScale = 28.64788975654117;

// This task adds to happy_angle to keep the robots current heading in degrees.
// The if statement is so that the value does not pass 360, in the case you make a 360.
task update_gyroSensor()
{
	HTGYROstartCal(gyroSensor);
	while(true)
	{
		float angle = HTGYROreadRot(gyroSensor) / 100.0;
		happy_angle = happy_angle + angle;
		if (happy_angle == 360)
		{
			happy_angle = 0;
		}
		wait1Msec(1);
	}
}


// Simple function to stop the drive.
void stop_drive(int time)
{
	motor[MotorL] = 0;
	motor[MotorR] = 0;
	wait10Msec(time);
}

// The rotation code allows you to put in a direction to turn, the power level of the
// turn, and the degree/heading you wish to turn to. If it is a cardinal heading,
// it will update the travelDirection variable.
void rotate(int direction, int powerlevel, int degree)
{
	if (direction == left)
	{
		motor[MotorL] = -powerlevel;
		motor[MotorR] = powerlevel;
		while (happy_angle != degree)
		{
			wait1Msec(1);
		}
	}
	else if (direction == right)
	{
		motor[MotorL] = powerlevel;
		motor[MotorR] = -powerlevel;
		while (happy_angle != degree)
		{
			wait1Msec(1);
		}
	}
	stop_drive(0);
	if (degree == north || degree == east || degree == south || degree == west)
	{
		travelDirection = degree;
	}
}

// This function is used in the move code, updating the x-coord and y-coord variables,
// and in turn updating the location of the robot.
void determineLocation(int direction, int unitsTraveled)
{
	if (travelDirection == north || travelDirection == south)
	{
		if (direction > 0)
		{
			Ycoord = Ycoord + unitsTraveled;
		}
		else if (direction < 0)
		{
			Ycoord = Ycoord - unitsTraveled;
		}
	}
	else if (travelDirection == east || travelDirection == west)
	{
		if (direction > 0)
		{
			Xcoord = Xcoord + unitsTraveled;
		}
		else if (direction < 0)
		{
			Xcoord = Xcoord - unitsTraveled;
		}
	}
}

// This drive code is a simple function that drives until a certain amount of encoder
// ticks are achieved. It then determine's your new location if you want to.
void drive(int powerlevel, int units, int determine)
{
	nMotorEncoder[MotorL] = 0;
	float encoderTarget = units * unitScale;
	motor[MotorL] = powerlevel;
	motor[MotorR] = powerlevel;
	while (nMotorEncoder[MotorL] < encoderTarget)
	{
		if (SensorValue(frontTouch) == 1)
		{
			stop_drive(0);
			int encoderProgress = nMotorEncoder[MotorL];
			while (nMotorEncoder[MotorL] < encoderProgress + 360)
			{
				motor[MotorL] = - (powerlevel);
				motor[MotorR] = - (powerlevel);
			}
			wait10Msec(100);
			nMotorEncoder[MotorL] = 0;
			while (nMotorEncoder[MotorL] < 360)
			{
				motor[MotorL] = powerlevel;
				motor[MotorR] = powerlevel;
			}
			nMotorEncoder[MotorL] = encoderProgress;
		}
	}
	stop_drive(0);
	if (determine == yes)
	{
		determineLocation(powerlevel, units);
	}
}

// This function allows us to call a point to "go to". You put in a power level for
// turns and the drive, the turn direction, and your target x and y coordinates.
// IMPORTANT: This function does not allow a negative power level.
void goToForward(int powerlevel, int turnDirection, int XcoordWanted, int YcoordWanted)
{
	// Through subtracting, the robot can figure out how much on each axis it has to
	// move.
	float Xdifference = XcoordWanted - Xcoord;
	float Ydifference = YcoordWanted - Ycoord;

	// These two lines of code are using the calculate function of tan to the -1,
	// allowing calculation of the angle needed to turn to, to make a straight line to
	// the point.
	float tanValue = Xdifference/Ydifference;
	float turnDifference = atan(tanValue);

	// Because the angle just calculated is from the triangle, and not the true heading
	// needed to turn to, this determines the true heading number to turn to.
	int turnAngle = 0;
	if (Ydifference > 0)
	{
		if (Xdifference > 0)
		{
			turnAngle = 0 + turnDifference;
		}
		else if (Xdifference < 0)
		{
			turnAngle = 360 - turnDifference;
		}
	}
	else if (Ydifference < 0)
	{
		if (Xdifference > 0)
		{
			turnAngle = 180 - turnDifference;
		}
		else if (Xdifference < 0)
		{
			turnAngle = 180 + turnDifference;
		}
	}

	// A^2 + B^2 = C^2 formula to determine the distance needed to travel to point.
	float a = Xdifference * Xdifference + Ydifference * Ydifference;
	float travelDistance = sqrt(a);

	// Rotate and drive according to calculations.
	rotate(turnDirection, powerlevel, turnAngle);
	drive(abs(powerlevel), travelDistance, no);

	// Set the new location.
	Xcoord = XcoordWanted;
	Ycoord = XcoordWanted;
}
