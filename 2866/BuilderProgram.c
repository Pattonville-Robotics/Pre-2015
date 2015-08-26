#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  mtr_S1_C1_1,     rightArmMotor, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightMotor,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     leftMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     leftArmMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    lockServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

#include "JoystickDriver.c"

int motorpower = 50;

task main()
{
	motor[leftArmMotor] = 0;
	motor[rightArmMotor] = 0;

	while(true)
	{
		while(nNxtButtonPressed == 1)
		{
				motor[leftArmMotor]  = motorpower;
				motor[rightArmMotor] = motorpower;
		}
		while(nNxtButtonPressed == 3)
		{
				motor[leftArmMotor]  = -motorpower;
				motor[rightArmMotor] = -motorpower;
		}
		motor[leftArmMotor] = 0;
		motor[rightArmMotor] = 0;
	}
}
