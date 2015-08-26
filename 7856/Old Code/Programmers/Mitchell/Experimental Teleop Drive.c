#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor,       sensorI2CCustom)
#pragma config(Sensor, S3,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     gyroSensorLevel, sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     MotorB,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Sweeper,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Arm,           tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     MotorL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     MotorR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     Arm2,          tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    Bucket,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

#include "JoystickDriver.c"
/*
const int liftTarget1 = 0;
const int liftTarget2 = 0;
const int liftTarget3 = 0;
const int liftTarget4 = 0;

void liftTarget(int buttonPressed)
{
while(nMotorEncoder[Arm]
}
*/
int scale_motor(int joyVal)				// Function to convert the value of the joystick to a motor value
{																	// Takes in the value of the joystick, puts out the speed of the motor
	const int   deadzone = 10; 									// Size of the joystick dead zone
	const float max_joy_range = 127.0; 					// Maximum value of the joystick
	const int   max_motor_range = 100;					// Maximum value of the motor
	const float ratio =  max_motor_range / max_joy_range;		// The ratio for converting the joystick value (-128 to 127) to the motor value (-100 to 100)

	if (abs(joyVal) < deadzone)	  		// If the value of the joystick is within the dead zone...
	{
		return 0;  											// ...return 0
	}

	return ratio * joyVal;						// Otherwise return the joystick value multiplied by the ratio
}




task main()
{
	while(true)
	{
		if(((abs(joystick.joy1_x1) > 10) || (abs(joystick.joy1_y1) > 10)) && (abs(joystick.joy1_y1) <= 20)) //This is a deadzone
		{
			motor[MotorL] = scale_motor(-(joystick.joy1_y1)) - (scale_motor(joystick.joy1_x1)/2);//These set the motor speeds proportionaly to the values of the joystick
			motor[MotorR] = scale_motor(-(joystick.joy1_y1)) + (scale_motor(joystick.joy1_x1)/2);
			motor[MotorB] = scale_motor(-(joystick.joy1_y1));
		}
		else if(((abs(joystick.joy1_x1) > 10) || (abs(joystick.joy1_y1) > 10)) && (abs(joystick.joy1_y1) > 20)) //This is another deadzone
		{
			motor[MotorL] = scale_motor(-(joystick.joy1_y1)) - (scale_motor(joystick.joy1_x1)/2);//These set the motor speeds proportionaly to the values of the joystick
			motor[MotorR] = scale_motor(-(joystick.joy1_y1)) + (scale_motor(joystick.joy1_x1)/2);
		}
		else
		{
			motor[MotorL] = 0; //This resets the motors
			motor[MotorR] = 0;
			motor[MotorB] = 0;
		}
	}
}
