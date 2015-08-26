void driveForwardWithGyro(int angle, int motorspeed, float time)
{
    clearTimer(T1);

    time = convertSeconds(time); //What if this is done in the function call?

    if(time1[T1] > time)
    {
        motor[leftMotor] = 0;
        motor[rightMotor] = 0;
        return;
    }

    if (angle > gyroValue)
    {
        motor[leftMotor] = motorspeed + 5;
        motor[rightMotor] = motorspeed;
    }
    else if (angle < gyroValue)
    {
        motor[leftMotor] = motorspeed;
        motor[rightMotor] = motorspeed + 5;
    }
    else
    {
        motor[leftMotor] = motorspeed;
        motor[rightMotor] = motorspeed;
    }

    (float)time /= 1000;

    return(driveForwardWithGyro(angle, motorspeed, time));


}


int convertSeconds(float seconds)
{
    return ((int)seconds *= 1000);
}
