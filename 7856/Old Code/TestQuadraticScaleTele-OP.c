#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CCustom)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     IRSensor2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     MotorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     MotorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     TopArm,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     BotArm,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Bucket,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)

//////////////////////////////////////////////////////////////////////////////////////////
//	Green Army Robotics Team 7856 (Tactical Division) 2013-14 Season "Block Party"		//
//	Purpose: To provide control of the Robot during the Tele-Op period					//
//	Contributors: Daniel Herzberg, Aidan O., Warren Li, Mitchell Skaggs, 				//
//		Nathan Skelton, Alex Tariah														//
//	Last Edited: 12/8/2013																//
//////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"

int scale(int input)
{
	int power = ((25 * exp(input))/(4096));
	if (input < 0)
	{
		power = -(power);
	}
	return power;
}

void joyDrive()
{
	motor[MotorL] = scale(joystick.joy1_y2 + (joystick.joy1_x2 /2));
	motor[MotorR] = scale(joystick.joy1_y2 - (joystick.joy1_x2 /2));
}

void arm()
{
	if (joy2Btn(5) == true)
	{
		motor[TopArm] = scale(joystick.joy2_y1);
		motor[BotArm] = scale(joystick.joy2_y1);
	}
	else
	{
		motor[TopArm] = 0;
		motor[BotArm] = 0;
	}
}

void moveBucket()
{
	if (joy2Btn(6) == true)
	{
		motor[Bucket] = scale(joystick.joy2_y2)/4;
	}
	else
	{
		motor[Bucket] = 0;
	}
}

task main()
{
	waitForStart();
	while(true)
	{
		joyDrive();
		arm();
		moveBucket();
	}
}
