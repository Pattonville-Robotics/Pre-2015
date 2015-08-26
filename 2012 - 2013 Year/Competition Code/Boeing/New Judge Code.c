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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool isLifted = false;

void lift()
{
	if(isLifted == true)
	{
		motor[leftslidemotor] = -50;
		motor[rightslidemotor] = -50;
		wait10Msec(450);
		motor[leftslidemotor]=0;
		motor[rightslidemotor]=0;
		isLifted = false;
	}
	else if(isLifted == false)
	{
		motor[leftslidemotor] = 50;
		motor[rightslidemotor]= 50;
		wait10Msec(450);
		motor[leftslidemotor]=0;
		motor[rightslidemotor]=0;
		isLifted = true;
	}
}

void moveBucket(bool goLeft, bool setCenter)
{
	if(goLeft == true && setCenter == false)
	{
		servo[bucketservo]=140;
	}
	else if(goLeft == false && setCenter == false)
	{
		servo[bucketservo]=90;
	}
	else if(setCenter == true)
	{
		servo[bucketservo]=128;
	}
}

task main()
{
	while (true)
	{
		if(nNxtButtonPressed == kEnterButton)
		{
			lift();
		}
		else if(nNxtButtonPressed == kLeftButton)
		{
			moveBucket(true, false);
		}
		else if(nNxtButtonPressed == kRightButton)
		{
			moveBucket(false, false);
		}
		else
		{
			moveBucket(false, true);
		}
	}


}