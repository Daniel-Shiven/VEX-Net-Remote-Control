#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port1,           motorRIGHT,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port5,           motorARM,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           motorCLAW,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          motorLEFT,     tmotorVex393_HBridge, openLoop)
/*----------------------------------------------------------------------------------------------------*\
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Tilting the controller DOWN, or FORWARD, gives a NEGATIVE reading on Y.                     *|
|*    2)  Tilting the controller UP, or BACK, gives a POSITIVE reading on Y.                          *|
|*    3)  Tilting the controller LEFT gives a NEGATIVE reading on X.                                  *|
|*    4)  Holding the controller RIGHT gives a POSITIVE reading on X.                                 *|
|*                                                                                                    *|
\*----------------------------------------------------------------------------------------------------*/

//---------------------------------------------------------------------------------------------//

void armControl()															//Claw ARM Control
{
	if(vexRT[Btn8U] == 1)
	{
		motor[port5] = -40;
	}
	else if(vexRT[Btn8D] == 1)
	{
		motor[port5] = 40;
	}
	else
	{
		motor[port5] = 0;
	}
}

//---------------------------------------------------------------------------------------------//

void clawControl()														//Claw Control
{
	if(vexRT[Btn8L] == 1)
	{
		motor[port6] = -30;
	}
	else if(vexRT[Btn8R] == 1)
	{
		motor[port6] = 30;
	}
	else
	{
		motor[port6] = 0;
	}
}

//---------------------------------------------------------------------------------------------//


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	int accel_x   = 0;      // Will hold the controller-accelerometer X reading.
	int accel_y   = 0;      // Will hold the controller-accelerometer Y reading.

	int prev_x    = 0;      // Will hold the previous accelerometer X reading (for comparison).
	int prev_y    = 0;      // Will hold the previous accelerometer Y reading (for comparison).

	int threshold = 10;     /* Used to cancel 'noise' of low values as well as */
	/* ignore spikes in accelerometer sensor readings. */

	while(1 == 1)
	{
		prev_x = accel_x;           // update previous x reading to 'accel_x'
		prev_y = accel_y;           // update previous y reading to 'accel_y'
		accel_x = vexRT[AccelX];    // update 'accel_x' to new current reading
		accel_y = vexRT[AccelY];    // update 'accel_y' to new current reading

		// is abs(current - prev) < threshold?
		if( (abs(accel_x - prev_x) < threshold) || (abs(accel_y - prev_y) > threshold) )
		{
			// YES.
			// Are either of them over the 'noise' threshold?
			if( (abs(accel_x) > threshold) || (abs(accel_y) > threshold) )
			{
				// YES.
				if(accel_y > 0) // going backwards?
				{
					motor[motorLEFT]  = ((-1 * accel_y) - accel_x)*2;
					motor[motorRIGHT] = ((-1 * accel_y) + accel_x)*2;
				}
				else  // going forward, or point turn:
				{
					motor[motorLEFT]  = ((-1 * accel_y) + accel_x)*2;
					motor[motorRIGHT] = ((-1 * accel_y) - accel_x)*2;
				}
			}
			// NO - give no power to motors, joystick is in center position (or near enough to it)
			else
			{
				motor[motorLEFT]  = 0;
				motor[motorRIGHT] = 0;
			}
			// NO - make no changes.
		}

		armControl();
		clawControl();
	}
}
