/*
 \file		findexit.c
 \author	MOHAMMAD HABIB SHAH ERSHAD BIN MOHD AZRUL SHAZRIL
 \date		2/7/2022
 \brief		Move 2 meter to find exit
*/

#include <ev3.h>

void init(){

	InitEV3(); //Declare library function
	setAllSensorMode(US_DIST_CM,NO_SEN, NO_SEN, NO_SEN); //set what input corresponds to what sensor
}

void moveforward(int total_rotation)
{
	OnFwdSync(OUT_BC, 50);
	total_rotation = MotorRotationCount(OUT_BC);
	Wait(MS_500);
}

void detect()
{
	Off(OUT_BC);
	PlaySound(SOUND_DOUBLE_BEEP);
	Wait(SEC_1);
}

void exit(int last_rotation)
{
	RotateMotorEx(OUT_BC, 50, 180, 200 , true, true);
	RotateMotorEx(OUT_BC, 50, last_rotation, 100 , true, true);
	RotateMotorEx(OUT_BC, 50, 90, 200 , true, true);
	RotateMotorEx(OUT_BC, 50, 3600, 100 , true, true);
	Off(OUT_BC);
}

int main(void)
{
	int rotation;
	int count = 0;
	int choice = 0;
	int array[20], choice1[20];

	while(1)
	{
		if (readSensor(IN_1) <= 35)
		{
			moveforward(rotation);
		}
		else if (readSensor(IN_1) > 35)
		{
			detect();
			count = count + 1;
			array[count] = rotation;
			while(readSensor(IN_1) > 35)
			{
				moveforward(rotation);
			}


		}

		if (rotation >= 16.67)
		{
			break;
		}

	}


	while(ButtonIsUp(BTNCENTER) == 0)
	{
		LcdClean();
		sprintf(choice1, "%d", choice);

		TermPrintln("Position x    : %s",choice1);
		if(ButtonIsUp(BTNUP) == 0)
		{


			choice++;
			while(ButtonIsUp(BTNUP) == 0)
			{
				choice = choice;
			}

		}
		if(ButtonIsUp(BTNUP) == 0)
		{
			choice--;
			while(ButtonIsUp(BTNDOWN) == 0)
			{
				choice = choice;
			}

		}
	}


	int lastrotation = 16.67 - array[choice];

	exit(lastrotation);

	return 0;
}
