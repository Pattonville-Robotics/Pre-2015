#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     irseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     lineSensor,     sensorLightActive)
#pragma config(Sensor, S4,     touchSensor,    sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     Motorleft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Motorright,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include <JoystickDriver.c>
#include <hitechnic-irseeker-v2.h>

int readIR()
{
	int IRValue = HTIRS2readACDir(irseeker);
	return IRValue;
}

bool alignWithBeacon = false;

void followIR()
{
  if (readIR()< 5 && readIR()>0)
  {
   motor[Motorleft]=-50;
   motor[Motorright]=50;
   nxtDisplayTextLine(3,"Left");
  }
  else if (readIR()> 5)
  {
   motor[Motorleft]=50

   ;
   motor[Motorright]=-50;
   nxtDisplayTextLine(3,"Right");
  }
  else if (readIR()== 5)
  {
   motor[Motorleft]=25;
   motor[Motorright]=25;

   nxtDisplayTextLine(3,"Forward");
  }
  else
  {
   motor[Motorleft]=0;
   motor[Motorright]=0;

   nxtDisplayTextLine(3,"Stop");
  }

}

bool isOnLine()
{
	if(SensorValue[lineSensor] > 45)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool bumperIsPressed()
{
	return SensorValue(touchSensor);
}

bool inLineWithGoal()
{
	if(isOnLine() == true && SensorValue[irseeker] == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int alignWithBeaconPole()
{

}



task main()
{

	while(true)
	{
		//Drive Forward, while the IR receiver reads a value of 5
		//
		if(SensorValue(irseeker) == 5 && !bumperIsPressed())
		{
			motor[Motorright] = 50;
			motor[Motorleft] = 50;
		}
		else
		{
			motor[Motorright] = 0;
			motor[Motorleft] = 0;
		}
	}
}
