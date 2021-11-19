#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port1,           motorRIGHT,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port5,           motorARM,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           motorCLAW,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          motorLEFT,     tmotorVex393_HBridge, openLoop)

//------------------------------------------------------------------------------------------------//

task main()
{
	while(1==1)
	{
		if(SensorValue(sonarSensor) > 25 || SensorValue(sonarSensor) < 0)
		{
			motor[motorRIGHT] = motor[motorLEFT] = 60;
		}

		if(SensorValue(sonarSensor) < 25)
		{
			motor[motorRIGHT] = 60;
			motor[motorLEFT] = -60;
			wait1Msec(988);
		}
	}
}
