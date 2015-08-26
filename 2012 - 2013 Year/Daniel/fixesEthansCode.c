#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           motorB,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,           motorA,             tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

//changed motor pragma*//
//bool scale;
int motorAmovement = 0;
int motorBmovement = 0;

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

	joystick_value = joystick_value / 2;
	return (joystick_value);
}

void setInfo()
{
	if(joy1Btn(5))
	{
		motor[motorA] = 25;
	}
	if(joy1Btn(6))
	{
		motor[motorB] = 25;
	}
	if(joy1Btn(8))
	{
		motor[motorB] = -25;
	}
	if(joy1Btn(7))
	{
		motor[motorA] = -25;
	}

	motor[motorA] =  read_joystick(Left);

	motor[motorB] =  read_joystick(Right);

	/*if(joy1Btn(1))
	{
		motorAmovement = motorAmovement*.75;
		motorBmovement = motorBmovement*.75;
	}*/
};

task main ()
{
	while (true)
	{
		setInfo();
	}
}
