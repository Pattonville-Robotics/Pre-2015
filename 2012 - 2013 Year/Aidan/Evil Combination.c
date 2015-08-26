
task main()
{
  while(SensorValue(touchSensor) == 0)    // While the Touch Sensor is inactive (hasn't been pressed):
  {
    //motor[motorD] = 100;                        /* Run motors B and C forward */
    //motor[motorE] = 100;                        /* with a power level of 100. */
 		nxtDisplayCenteredTextLine(3,"Not Pressed");
  }
                                          // Otherwise (the touch sensor has been activated [pressed] ):
  //motor[motorD] = -75;                    /* Run motors B and C backwards */
  //motor[motorE] = -75;                    /* with a power level of -75.   */
	nxtDisplayCenteredTextLine(3, "Pressed");
  wait1Msec(1000);                        // Wait 1000 milliseconds (1 second) before moving to further code.
}
