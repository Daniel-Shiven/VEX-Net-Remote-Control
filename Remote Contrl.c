#pragma config(Motor, port1,						motorRIGHT,		tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor, port5,						motorARM,		tmotorVex393_MC29, openLoop)
#pragma config(Motor, port6,						motorCLAW,		tmotorVex393_MC29, openLoop)
#pragma config(Motor, port10,						motorLEFT,		tmotorVex393_HBridge, openLoop)
#pragma config(Sensor, dgtl8,  sonarSensor,         sensorSONAR_cm)

/*----------------------------------------------------------------------------------------------*/
void joystickControl()													//Joystick Control
{

	motor[motorLEFT] = vexRT[Ch3];
	motor[motorRIGHT] = vexRT[Ch2];
}

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

//---------------------------------------------------------------------------------------------//


{

		while(1==1)
		{
				joystickControl();
				armControl();
				clawControl();
		}
