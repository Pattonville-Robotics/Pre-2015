
typedef enum
{
	stateInit,
	stateForward,
	stateLeft
} TStates;

TStates nCurrState;

task main()
{
	nCurrState = stateInit;
	while(true)
	{
		switch(nCurrState)
		{
			case stateInit:

			break;
			case stateForward:

			break;
		}
	}
}
