#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     MotorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     MotorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     TopArm,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     MidArm,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     BotArm,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     BucketMotor,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    Bucket,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Green Army Robotics Team 7856 (Tactical Division) 2013-14 Season "Block Party"
Purpose: To provide control of the Robot during the Tele-Op period
Contributors: Daniel Herzberg VCIII	, Aidan O., Warren Li, Mitchell Skaggs, Nathan Skelton, Alex Tariah
Last Edited: 10/1/2013
*/

#include "JoystickDriver.c"
//#include "\\GAR-SERVER\2866 Software\rdpartyrobotcdr-3.1\drivers\hitechnic-gyro.h"

int exp_scale_motor(int joyVal)				// Function to convert the value of the joystick to a motor value
{																	// Takes in the value of the joystick, puts out the speed of the motor
	const int  deadzone = 10; 									// Size of the joystick dead zone
	/*const float max_joy_range = 127.0; 					// Maximum value of the joystick
	const int   max_motor_range = 100;					// Maximum value of the motor
	const float ratio =  max_motor_range / max_joy_range;*/		// The ratio for converting the joystick value (-128 to 127) to the motor value (-100 to 100)
	const long motorVal = ((pow(joyVal, 3) * 100) / 4096766); // The ratio for converting the joystick value into the motor speed
	if (abs(joyVal) < deadzone)	  		// If the value of the joystick is within the dead zone...
	{
		return 0;  											// ...return 0
	}
	return motorVal;
}

int scale_motor(int joyVal)				// Function to convert the value of the joystick to a motor value
{																	// Takes in the value of the joystick, puts out the speed of the motor
	const int  deadzone = 10; 									//  of the joystick dead zone
	const float max_joy_range = 127.0; 					// MaxSizeimum value of the joystick
	const int   max_motor_range = 100;					// Maximum value of the motor
	const float ratio =  max_motor_range / max_joy_range;		// The ratio for converting the joystick value (-128 to 127) to the motor value (-100 to 100)

	if (abs(joyVal) < deadzone)	  		// If the value of the joystick is within the dead zone...
	{
		return 0;  											// ...return 0
	}
	else
		return ratio * joyVal;						// Otherwise return the joystick value multiplied by the ratio
}

void raiseArm()	// Function to raise or lower the arm at a speed determined by the joystick value
{
	if((joy2Btn(5) == true) && (abs(joystick.joy2_y1) > 20) && (joy2Btn(8) == false) && (joy2Btn(7) == false)) //If the joystick is moved, the safety button is pressed, and the Turbo Button� is _not_ pressed
	{
		motor[TopArm] = exp_scale_motor(joystick.joy2_y1);
		motor[MidArm] = exp_scale_motor(joystick.joy2_y1);
	}
	//IF ANY ISSUE ARISE DUE TO THE TURBO BUTTON, ALL BLAME SHALL BE DIRECTED TO JED.
	//ELECTRONIC SIGNATURE (10/15/2013): Jed Menard
	else if((joy2Btn(8) == true) && (joy2Btn(5) == false) && (joy2Btn(7) == false)) //If the forwards Turbo Button� is pressed
	{
		motor[TopArm] = -100;
		motor[MidArm] = -100;
		motor[BotArm] = -100;
	}
	else if((joy2Btn(8) == false) && (joy2Btn(5) == false) && (joy2Btn(7) == true)) //If the backwards Turbo Button� is pressed
	{
		motor[TopArm] = 100;
		motor[MidArm] = 100;
		motor[BotArm] = 100;
	}
	else //If nothing is pressed
	{
		motor[TopArm] = 0;
		motor[MidArm] = 0;
		motor[BotArm] = 0;
	}
}

void joyDrive()
{
	motor[MotorL] = scale_motor(joystick.joy1_y2 + (joystick.joy1_x2 * 2 / 3)); //This scales the right motor based on both the Y and the X values of the controller
	motor[MotorR] = scale_motor(joystick.joy1_y2 - (joystick.joy1_x2 * 2 / 3)); //This does the same to the left motor
}

void bucketM()
{
	if(abs(joystick.joy2_y2) > 20)
	{
		motor[BucketMotor] = -scale_motor(joystick.joy2_y2) / 4;
	}
	else if (joy2Btn(4) == true)
	{
		motor[BucketMotor] = -100;
	}
	else if (joy2Btn(2) == true)
	{
		motor[BucketMotor] = 100;
	}
	else
	{
		motor[BucketMotor] = 0;
	}
}

task main()
{
	waitForStart();						// Wait for the tele-op period to begin
	while(true)								// Infinite loop:
	{
		joyDrive();
		raiseArm();
		bucketM();
	}
}
