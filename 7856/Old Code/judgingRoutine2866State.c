#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     irSensor1,      sensorI2CCustom)
#pragma config(Sensor, S3,     irSensor2,      sensorI2CCustom)
#pragma config(Sensor, S4,     gyroSensor,     sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorFL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorBR,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorBL,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorLift1,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    clawL,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    clawR,                tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////
// Green Army Robotics Team 2866 (Covert Division) 2012-13 Season "Ring It Up" //
// Purpose: TO show the judges how the arm operates.									         //
// Contributors: Kyle Hall, Grant Matthews, Warren Li, Tom Sarsfield           //
// Last Edited: 2/22/13																												 //
/////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"
// These are the drivers required to run the program

task main()
{
	nMotorEncoderTarget[motorLift1] = 6200; 			// Set the motor encoder target for the maximum height
	motor[motorLift1] = 35;                       // Raise the arm at the designated speed

	servoTarget[clawL] = 115;											// Open the Claw
	servoTarget[clawR] = 100;
	wait1Msec(100);

	servoTarget[clawL] = 55;											// Close the Claw
	servoTarget[clawR] = 170;
	wait1Msec(100);

	nMotorEncoderTarget[motorLift1] = 0; 					// Set the motor encoder target for the lowest height
	motor[motorLift1] = -35;											// Lower the arm at the designated speed
}
