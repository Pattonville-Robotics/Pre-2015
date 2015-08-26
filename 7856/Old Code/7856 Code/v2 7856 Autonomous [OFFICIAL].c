#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CCustom)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     IRSensor2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     MotorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     MotorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     TopArm,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     BotArm,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Bucket,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)

//////////////////////////////////////////////////////////////////////////////////////
//																																									//
//	Green Army Robotics Team 7856 (Tactical Division) 2013-14 Season "Block Party"	//
//	Purpose: To have the robot move on its own for the Autonomous Period						//
//	Contributors: Daniel Herzberg, Aidan O., Warren Li, 														//
//		Mitchell Skaggs, Nathan Skelton, Alex Tariah																	//
//	Last Edited: 10/26/2013																													//
//																																									//
//////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"
#include <hitechnic-gyro.h>

const int IRPORT = 8;
const int forward = 0;
const int backward = 1;
const int left = 0;
const int right = 1;
const int up = 0;
const int down = 1;
const int basketTimer = T1;
int basketTimeValue = 0;
int IRValue = 0;
float happy_angle= 0;
int IRLocation = 0; //The distance that the robot has gone before it finds the IR bacon.


int update_IRsensor()
{
	IRValue = SensorValue[IRSensor2];
	nxtDisplayTextLine(6,"IRValue: %d",IRValue);
	return IRValue;
}

task update_gyroSensor()
{
	HTGYROstartCal(gyroSensor);
	while(true)
	{
		float angle = HTGYROreadRot(gyroSensor) / 100.0;
		happy_angle = happy_angle + angle;
		wait10Msec(1);
	}
}

void stop_drive()
{
	nxtDisplayTextLine(1,"Stoping");
	motor[MotorL] = 0;
	motor[MotorR] = 0;
}

void moveCm(int direction, int distance, int power)
{
	int motorEncoderTarget = distance / 0.028;
	nMotorEncoder[MotorL] = 0;
	nMotorEncoder[MotorR] = 0;
	bool encoderAcheived = false;
	if (direction == forward)
	{
		while(encoderAcheived == false)
		{
			if ((nMotorEncoder[MotorL] < motorEncoderTarget) && (nMotorEncoder[MotorR] < motorEncoderTarget))
			{
				motor[MotorR] = power;
				motor[MotorL] = power;
			}
			else
			{
				encoderAcheived = true;
			}
		}
	}
	else if (direction == backward)
	{
		while(encoderAcheived == false)
		{
			if ((nMotorEncoder[MotorL] > motorEncoderTarget) && (nMotorEncoder[MotorR] > motorEncoderTarget))
			{
				motor[MotorR] = power;
				motor[MotorL] = power;
			}
			else
			{
				encoderAcheived = true;
			}
		}
	}
	stop_drive();
	wait10Msec(10);
}

void rotate(int direction, int powerLevel, int stopAngle)
{
	happy_angle = 0;
	if (direction == left)
	{
		nxtDisplayTextLine(1,"Rotating Left");
		while (happy_angle > stopAngle)
		{
			motor[MotorL] = - powerLevel+15;
			motor[MotorR] = powerLevel;
		}
	}
	else if (direction == right)
	{
		nxtDisplayTextLine(1,"Rotating Right");
		while (happy_angle < stopAngle)
		{
			motor[MotorL] = powerLevel;
			motor[MotorR] = - powerLevel+15;
		}
	}
	writeDebugStream("No longer rotating\n");
	stop_drive();
}

void move(int direction, int motorspeed, int time)
{
	if (direction == backward)
	{
		motor[MotorL] = motorspeed - 8;
		motor[MotorR] = motorspeed;
		nxtDisplayTextLine(1,"Moving Backward");
		wait10Msec(time);
		stop_drive();
	}
	else if (direction == forward)
	{
		motor[MotorL] = motorspeed + 8;
		motor[MotorR] = motorspeed;
		nxtDisplayTextLine(1,"Moving Forward");
		wait10Msec(time);
		stop_drive();
	}
	else
	{
		stop_drive();
	}
}

void find_ir_basket(int motorspeed, int rotatemotorspeed, int angle)
{
	time1[basketTimer]=0;

	while (update_IRsensor() != IRPORT)
	{
		move(forward, motorspeed, 5);
	}
	basketTimeValue = time1[basketTimer];
	IRLocation = ((nMotorEncoder[MotorR] + nMotorEncoder[MotorL]) / 2); //This finds the average of the two encoder values (for accuracy)
	wait10Msec(5);

	motor[MotorL] = -20;
	motor[MotorR] = -20;
	wait10Msec(120);
	motor[MotorL] = 0;
	motor[MotorR] = 0;
}

void arm(int direction)
{
	if (direction == up)
	{
		motor[TopArm] = 50;
		motor[BotArm] = 50;
		wait10Msec(240);
		motor[TopArm] = 0;
		motor[BotArm] = 0;
	}
	else if (direction == down)
	{
		motor[TopArm] = -50;
		motor[BotArm] = -50;
		wait10Msec(210);
		motor[TopArm] = 0;
		motor[BotArm] = 0;
	}
}

void move_bucket(int direction, int time)
{
	if (direction == up)
	{
		motor[Bucket] = -40;
		wait10Msec(time);
		motor[Bucket] = 0;
	}
	else if (direction == down)
	{
		motor[Bucket] = 20;
		wait10Msec(time);
		motor[Bucket] = 0;
	}
}

void score_in_basket(int motorspeed, int distance, int buckettime)
{
	arm(up);
	rotate(right, 40, 90);
	moveCm(forward, distance, motorspeed);
	move_bucket(down, buckettime);
	wait10Msec(30);
}

int innerCircleArcCircumference = 0;
int outerCircleArcCircumference = 0;

void arcDrive(int radius, int angle, int completionTime, bool leftOrRight)
{
	if(leftOrRight == true) //Left turn
	{
		innerCircleArcCircumference = 0;
	}
	else if(leftOrRight == false) //Right turn
	{

	}
}

void returnToStart(int motorpower, int distance)
{
	moveCm(backward, distance, motorpower);
	rotate(right, 45, 90);
	arm(down);
	time1[basketTimer] = 0;
	while (time1[basketTimer]<basketTimeValue)
	{
		move(forward, 35, 5);
	}
	moveCm(forward, 2, 35);
}

void ramp()
{
	rotate(left, 50, -85);
	moveCm(forward, 50, 75);
	rotate(left, 45, -85);
	moveCm(forward, 80, 75);
}

task main()
{

	waitForStart();

	StartTask(update_gyroSensor);
	wait10Msec(10);
	find_ir_basket(35, 30, 90);
	score_in_basket(50, 12, 50);
	move_bucket(up, 50);
	returnToStart(-40, -20);
	ramp();
}
