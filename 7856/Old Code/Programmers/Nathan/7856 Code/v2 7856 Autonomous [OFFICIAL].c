#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyroSensor,     sensorI2CCustom)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     IRSensor2,      sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     MotorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     MotorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     TopArm,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BotArm,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     MidArm,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     Bucket,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//////////////////////////////////////////////////////////////////////////////////////
//																																									//
//	Green Army Robotics Team 7856 (Tactical Division) 2013-14 Season "Block Party"	//
//	Purpose: To have the robot move on its own for the Autonomous Period						//
//	Contributors: Daniel Herzberg, Aidan O., Warren Li, 														//
//		Mitchell Skaggs, Nathan Skelton, Alex Tariah																	//
//	Last Edited: 11/22/2013																													//
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
const int gyro_on_ramp = 0;
int find_basket_distance = 0;
int distance_traveled = 0;
int IRValue = 0;
bool leftSide = false;
bool rightSide = false;
float happy_angle= 0;
int IRLocation = 0; //The distance that the robot has gone before it finds the IR bacon.
int HalfwayPoint = 1000;

int update_IRsensor()
{
	IRValue = SensorValue[IRSensor2];
	return IRValue;
}

task update_gyroSensor()
{
	HTGYROstartCal(gyroSensor);
	while(true)
	{
		float angle = HTGYROreadRot(gyroSensor) / 100.0;
		happy_angle = happy_angle + angle;
		nxtDisplayTextLine(7,"GyroFromStart: %d", happy_angle);
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
	if (direction == left)
	{
		nxtDisplayTextLine(1,"Rotating Left");
		while (happy_angle > -stopAngle)
		{
			motor[MotorL] = - powerLevel;
			motor[MotorR] = powerLevel+10;
		}
	}
	else if (direction == right)
	{
		nxtDisplayTextLine(1,"Rotating Right");
		while (happy_angle < stopAngle)
		{
			motor[MotorL] = powerLevel+10;
			motor[MotorR] = - powerLevel;
		}
	}
	writeDebugStream("No longer rotating\n");
	stop_drive();
}

void move(int direction, int motorspeed, int time)
{
	if (direction == backward)
	{
		motor[MotorL] = - motorspeed;
		motor[MotorR] = - motorspeed;
		nxtDisplayTextLine(1,"Moving Backward");
		wait10Msec(time);
	}
	else if (direction == forward)
	{
		motor[MotorL] = motorspeed;
		motor[MotorR] = motorspeed;
		nxtDisplayTextLine(1,"Moving Forward");
		wait10Msec(time);
	}
	stop_drive();
}

void drive_on_ramp(int motorspeed)
{
	nxtDisplayTextLine(2,"Finding Ramp");
	while (happy_angle < gyro_on_ramp)
	{
		move(forward, motorspeed, 0);
	}
	nxtDisplayTextLine(2,"Stopped On Ramp");
	stop_drive();
}

void find_ir_basket(int motorspeed, int rotatemotorspeed, int angle)
{
	while (update_IRsensor() != IRPORT)
	{
		move(forward, motorspeed, 5);
		wait10Msec(1);
	}
	IRLocation = ((nMotorEncoder[MotorR] + nMotorEncoder[MotorL]) / 2); //This finds the average of the two encoder values (for accuracy)
	wait10Msec(5);
	move(backward, 20, 60);
}

void arm(int direction)
{
	if (direction == up)
	{
		motor[TopArm] = 50;
		motor[BotArm] = 50;
		motor[MidArm] = 50;
		wait10Msec(165);
		motor[TopArm] = 0;
		motor[BotArm] = 0;
		motor[MidArm] = 0;
	}
	else if (direction == down)
	{
		motor[TopArm] = -50;
		motor[BotArm] = -50;
		motor[MidArm] = -50;
		wait10Msec(165);
		motor[TopArm] = 0;
		motor[BotArm] = 0;
		motor[MidArm] = 0;
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
	moveCm(forward, distance, motorspeed);
	move_bucket(down, buckettime);
	wait10Msec(25);
	move_bucket(up, buckettime);
}

void left_side_ramp(int distance, int motorpower)
{
	moveCm(backward, distance, motorpower);
	rotate(left, 30, 0);
}

void right_side_ramp(int distance, int motorpower)
{
	moveCm(backward, distance, motorpower);
	rotate(right, 30, 180);
}

void decide_side(int distance, int motorpower)
{
	if (leftSide == true && rightSide == false)
	{
		left_side_ramp(distance, motorpower);
	}
	else if (leftSide == false && rightSide == true)
	{
		right_side_ramp(distance, motorpower);
	}
	else
	{
		if (IRLocation >= HalfwayPoint)
		{
			left_side_ramp(distance, motorpower);
		}
		else if (IRLocation <= HalfwayPoint)
		{
			right_side_ramp(distance, motorpower);
		}
	}
}

task main()
{
	StartTask(update_gyroSensor);
	find_ir_basket(25, 30, 90);
	rotate(right, 30, 90);
	score_in_basket(50, 40, 30);
	decide_side(-40, -50);
}
