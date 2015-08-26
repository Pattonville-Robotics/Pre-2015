#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rightmotor,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     leftmotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     slidemotor1,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     slidemotor2,   tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"


int joystick_to_motor (int joystick_value)
{
	float motor_value;
	motor_value=(joystick_value*joystick_value/163.84);
	if (joystick_value<0)
	{
		motor_value=motor_value*-1.0;
	}
	return(motor_value);
}

const int Left = 0;
const int Right = 1;

int read_joystick(int side)
{
	int joystick_value;


	// if side is Left
	if (side == Left)
	{
		// read left joystick Y
		joystick_value = joystick.joy1_y1;
	}
	// else
	else if (side == Right)
	{

		// read right joystick Y
		joystick_value = joystick.joy1_y2;

	}
	if (abs(joystick_value)<15)
	{
		joystick_value=0;
	}
	return (joystick_value);
}

bool runCode = true;


task main ()
{
	while (true)
	{
		getJoystickSettings(joystick);

		if (runCode == true)
		{
			nxtDisplayTextLine (1, "%d",read_joystick (Left));
			nxtDisplayTextLine (2, "%d",read_joystick (Left));
			motor[leftmotor]=(joystick_to_motor (read_joystick (Left)));
			motor[rightmotor]=(joystick_to_motor (read_joystick (Right)));
		}
		else
		{
			motor[leftmotor]=0;
			motor[rightmotor]=0;
		}

		if (joy1Btn (8))
		{
			runCode = false;
			motor[leftmotor]=0;
			motor[rightmotor]=0;
		}
		else if (joy1Btn(7))
		{
			runCode = true;
		}
	}
}
