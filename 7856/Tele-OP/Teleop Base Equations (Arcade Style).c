#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftMotor,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rightMotor,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
        __________________________________________________________________________________
        ||                                                                              ||
        ||                        Program created by FTC Teams 7856*                    ||
        ||                                                                              ||
        ||             *This Teleop Program was created in collaboration with           ||
        ||             a programmer from the FTC Team 2866: Ethan O'Dell                ||
        ||                                                                              ||
        ||             Through Gracious Professionalism our team was able to            ||
        ||             work with another programmer and create an extremely             ||
        ||             elegant teleop program that makes use of the polar               ||
        ||             coordinates system and trigonometry in a simple manner.          ||
        ||                                                                              ||
        ||______________________________________________________________________________||

*/


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot() //Set the motors to zero incase of leftover values
{
  motor[leftMotor] = 0;
  motor[rightMotor] = 0;
}

void setMotors()   //Converting joystick values into polar coordinates, rotating 45 degrees(PI/4 radians) counterclockwise
{                  //Then converting the coordinates into raw motor values
  /*
    float x = joystick.joy1_x1;             //Take in joystick values
    float y = joystick.joy1_y1;

    float r = sqrt( pow(x, 2) + pow(y, 2)); //Get the radius of the polar coordinates.
    float theta = atan2(y,x);                //Get the theta of the polar coordinates.
    float theta2 = theta + PI/4;            //We add 45 degrees to theta to make the x and y values distinct when moving forward
                                            //Just think about the four graph quadrants and their signs to understand.

    float x1 = -r*cos(theta2);              //This converts the polar coordinates back into cartesian points
    float y1 = r*sin(theta2);

    motor[rightMotor] = ((100*x1)/127);     //Set the 2 motors to scaled motor values using the new cartesian points
    motor[leftMotor] = ((100*y1)/127);
  */

  //This is simplified form resulting in an efficient computation time:
  motor[rightMotor] = -(((float)(100)) / 127) * sqrt(pow(joystick.joy1_x2, 2) + pow(joystick.joy1_y2, 2))
                                              * cos(atan2(joystick.joy1_y2, joystick.joy1_x2) + (PI / 4));

  motor[leftMotor] = (((float)(100)) / 127) * sqrt(pow(joystick.joy1_x2, 2) + pow(joystick.joy1_y2, 2))
                                            * sin(atan2(joystick.joy1_y2, joystick.joy1_x2) + (PI / 4));
}

task main()
{
  initializeRobot();
  //waitForStart();

  while (true)
  {
    if(abs(joystick.joy1_x2) > 3 || abs(joystick.joy1_y2) > 3) //Account for dead zones on the controller
    {
      setMotors();
    }
    else   //If there is a dead zone then just stop the motors
    {
      motor[leftMotor] = 0;
      motor[rightMotor] = 0;
    }
  }
}
