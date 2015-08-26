#pragma config(Sensor, S1,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S2,     ,               sensorI2CCustom)
#pragma config(Motor,  motorA,          rightmotor,    tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          leftmotor,     tmotorNXT, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "joyStickDriver.c"
#include "hitechnic-irseeker-v2.h"
#include <hitechnic-gyro.h>

//le Mark, if you ever use French articles for naming functions/variables again I may explode.


int readir()
{
	int direction = HTIRS2readACDir(HTIRS2);
	return direction;
}

void followIR()
{
	if (readir()< 5 && readir()!=2 && readir()!=0)
	{
		motor[leftmotor]=50;
		motor[rightmotor]=50;

		nxtDisplayTextLine(3,"On the left");
	}
	else if (readir()> 5 && readir()!=8)
	{
		motor[leftmotor]=50;
		motor[rightmotor]=50;

		nxtDisplayTextLine(3,"On the right");
	}
	else if (readir()== 2)
	{
		motor[leftmotor]=-50;
		motor[rightmotor]=50;

		nxtDisplayTextLine(3,"Go to the left");
		wait10Msec(80);
	}
	else if (readir()==8)
	{
		motor[leftmotor]=50;
		motor[rightmotor]=-50;

		nxtDisplayCenteredTextLine(3, "Go to the right");
		wait10Msec(80);
	}
	else
	{
		motor[leftmotor]=0;
		motor[rightmotor]=0;

		nxtDisplayTextLine(3,"Stop");
	}
}


task main()
{
	waitForStart();
	while(true)
	{
		followIR();
		nxtDisplayTextLine(4, "%d", readir());
	}
}
