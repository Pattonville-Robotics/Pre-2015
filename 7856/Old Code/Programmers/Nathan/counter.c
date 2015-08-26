
void left_side_ramp()
{
	
}

void right_side_ramp()
{

}

void move_for_ramp()
{
	if (left_side == 1)
	{
		left_side_ramp();
	}
	else if (right_side == 1)
	{
		right_side_ramp();
	}
	else
	{
		if (rotations > 10000)
		{
			left_side_ramp();
		}
		else if (rotations < 10000)
		{
			right_side_ramp();
		}
	}
}

task main()
{
	int left_side = 0;
	int right_side = 0;
	move_for_ramp();
}