#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl12, shaftEncoder,   sensorRotation)
#pragma config(Motor,  port1,           motorRIGHT,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port5,           motorARM,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           motorCLAW,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           motorSONIC,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          motorLEFT,     tmotorVex393_HBridge, openLoop)


//Notes:
//
//Setup: Define Variables, Position Sonic Sensor to Left Side
//Detect Left: If object is within 50 centimeters, clock distance, otherwise make it 51. Turn to the right.
//Detect Middle: If object is within 50 centimeters, clock distance, otherwise make it 51. Turn to the right
//Detect Right: If object is within 50 centimeters, clock distance, otherwise make it 51.
//Interpret Readings: Take the smallest reading and go in that direction
//Reset to Left: Turn left times 2.
//
//What does it do? Takes 100 ms to read data from 3 directions, interprets data, moves for 10 - 100 ms depending on distance of object,
//and takes 200 ms to reset and reread data from 3 directions.


//------------------------------------------------------------------------------------------------//

task main()
{

//------------------------------Set up-----------------------------------//
	int Right;
	int Middle;
	int Left;
	int Time;

	motor[motorSONIC] = -30;
	wait1Msec(50);

	while(1==1)
	{

//------------------------------Detect Left-----------------------------------//

		if(SensorValue(sonarSensor) < 50)
		Left = SensorValue(sonarSensor);
		else
		Left = 51;

		motor[motorSONIC] = 30;
		wait1Msec(50);

//------------------------------Detect Middle-----------------------------------//

		if(SensorValue(sonarSensor) < 50)
		Middle = SensorValue(sonarSensor);
		else
		Middle = 51;

		motor[motorSONIC] = 30;
		wait1Msec(50);

//------------------------------Detect Right-----------------------------------//

		if(SensorValue(sonarSensor) < 50)
		Right = SensorValue(sonarSensor);
		else
		Right = 51;

//------------------------------Interpret Readings-----------------------------------//

		if(Left > Right)
		{
			if(Middle > Right)
			{
				Time = (Right)*2;

				motor[motorLEFT] = 60;
				motor[motorRIGHT] = 60;
				wait1Msec(Time);
			}
		}
		else if(Right > Left)
		{
			if(Middle > Left)
			{
				Time = (Left)*2;

				motor[motorLEFT] = 60;
				motor[motorRIGHT] = 60;
				wait1Msec(Time);
			}
		}
		else if(Left > Middle)
		{
			if(Right > Middle)
			{
				Time = (Right)*2;

				motor[motorLEFT] = 60;
				motor[motorRIGHT] = 60;
				wait1Msec(Time);
			}
		}

//------------------------------Reset to Left-----------------------------------//

		motor[motorSONIC] = -30;
		wait1Msec(100);

	}
}
