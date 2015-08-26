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

#include "JoystickDriver.c"

const int a=.0069407991;
const int b=-.0940799067;
int exp_scale_motor(int joyValue)
{
	if (joyValue > 0)
	{
		int motorpower=(a*joyValue*joyValue)+(b*joyValue);
		return motorpower;
	}
	else if (joyValue < 0)
	{
		int motorpower=(a*joyValue*joyValue)+(b*joyValue);
		motorpower= -(motorpower);
		return motorpower;
	}
	else
	{
		int motorpower=0;
		return motorpower;
	}

}

void joyDrive()
{

	motor[MotorL] = exp_scale_motor(joystick.joy1_y2 + (joystick.joy1_x2)* 2/3);
	motor[MotorR] = exp_scale_motor(joystick.joy1_y2 - (joystick.joy1_x2)* 2/3);
}

void arm()
{
	if (joy2Btn(5) == true)
	{
		motor[TopArm] = exp_scale_motor(joystick.joy2_y1);
		motor[BotArm] = exp_scale_motor(joystick.joy2_y1);
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
		motor[Bucket] = exp_scale_motor(joystick.joy2_y2)/4;
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
