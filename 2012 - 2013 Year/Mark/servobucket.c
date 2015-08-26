#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#pragma config(Sensor, S4,     gyroSensor,     sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     rightmotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftmotor,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     rightslidemotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     leftslidemotor, tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    bucketservo,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

void moveBucket(int distance)
{
	if (distance < 0)
	{
		servo[bucketservo] = 166;
	}
	else
	{
		servo[bucketservo] = 90;
	}
	wait1Msec(abs(distance) * 6);
	servo[bucketservo] = 128;
}

task main()
{

	moveBucket(-50);

}
