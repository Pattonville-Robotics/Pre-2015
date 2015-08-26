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


const int up = 0;
const int down = 1;
const int bucket = 2;
int state;

task main()
{
	eraseDisplay();
	motor[TopArm] = 50;
	motor[BotArm] = 50;
	motor[MidArm] = 50;
	wait10Msec(100);
	motor[TopArm] = 0;
	motor[BotArm] = 0;
	motor[MidArm] = 0;
	wait10Msec(30);
	motor[TopArm] = -30;
	motor[BotArm] = -30;
	motor[MidArm] = -30;
	wait10Msec(85);
	motor[TopArm] = 0;
	motor[BotArm] = 0;
	motor[MidArm] = 0;
	if(state == 0)
	{
		nxtDisplayTextLine(1, "Move Arm Up");
	}
	else if (state == 1)
	{
		nxtDisplayTextLine(1, "Move Arm Down");
	}
	else if()
	{
		nxtDisplayTextLine(1, "Move Bucket");
	}
}
