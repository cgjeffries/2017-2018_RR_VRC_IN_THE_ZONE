/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
 const unsigned int leftButton = 1;
 const unsigned int centerButton = 2;
 const unsigned int rightButton = 4;
 const unsigned int all = 5;
 int auton = 0;
 char *autonName[4] = {"None", "BlueConeBase", "RedConeBase", "ConePylon"};

 void waitForRelease(unsigned int button)
 {
 	unsigned int number;
 	if(button != all)
 	{
 		number = button;

 		while(lcdReadButtons(uart1) == number)
 			delay(50);
 	}
 	else
 	{
 		while(lcdReadButtons(uart1) != 0)
 		 delay(50);
 	}
 }

#define NUMBER_OF_AUTONS 4
void setAuton(void *params)
{
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);
  lcdSetText(uart1, 1, "   Loading...   ");
  lcdSetText(uart1, 2, "  Please Wait.  ");
  delay(4000);
	int autonTemp = 1;
	while((lcdReadButtons(uart1) != centerButton) && !isEnabled())
	{
		lcdClear(uart1);
    lcdSetText(uart1, 1, autonName[auton]);
    if(autonTemp == 1){
      lcdSetText(uart1, 2, "     Select    >");
    }
    else if(autonTemp == NUMBER_OF_AUTONS){
      lcdSetText(uart1, 2, "<    Select     ");
    }
    else{
      lcdSetText(uart1, 2, "<    Select    >");
    }
		if(lcdReadButtons(uart1) == leftButton)
		{
			if(autonTemp != 1)
			{
				autonTemp --;
			}
			waitForRelease(leftButton);
			//waitForRelease();
		}
		if(lcdReadButtons(uart1) == rightButton)
		{
			if(autonTemp != NUMBER_OF_AUTONS)
			{
				autonTemp ++;
			}
			waitForRelease(rightButton);
		}
		if(autonTemp == 1)
		{
			auton = NOTHING;
		}
		else if(autonTemp == 2)
		{
			auton = BASE_CONE_20_BLUE;
		}
		else if(autonTemp == 3)
		{
			auton = BASE_CONE_20_RED;
		}
    else if(autonTemp == 4){
      auton = PYLON_CONE;
    }
		//displayLCDString(0, 0, auton);

		delay(20);
	}
	waitForRelease(centerButton);
  lcdSetText(uart1, 2, "has been chosen.");
}


int selectedAuto = 0;
#define vexCompetitionState ( (isEnabled()?0:2) + (isAutonomous()?1:0) )
#define kButtonNone     0
#define kButtonLeft     LCD_BTN_LEFT
#define kButtonRight    LCD_BTN_RIGHT

char *autos[] = {"None", "BlueConeBase", "RedConeBase", "ConePylon"};

int getLcdButtons() {
	int competitionState = vexCompetitionState;
	int buttons;
	while (lcdReadButtons(uart1) != kButtonNone) {
		if (vexCompetitionState != competitionState)
			return (kButtonNone);
		taskDelay(10);
	}

	do {
		buttons = lcdReadButtons(uart1);

		if (vexCompetitionState != competitionState)
			return (kButtonNone);

		taskDelay(10);
	} while (buttons == kButtonNone);

	return (buttons);
}

void lcdSetAutonomous(int value) {
	lcdSetText(uart1, 1, autos[value]);

	selectedAuto = value;
}

void lcdAutonomousSelection(void *params) {
	int button;

	lcdClear(uart1);
	lcdSetBacklight(uart1, true);

	lcdSetAutonomous(0);
	taskDelay(2000);

	while (true) {
		if (!isEnabled()) {
			lcdSetAutonomous(selectedAuto);

			button = getLcdButtons();

			if (button == kButtonLeft && selectedAuto > 0) {
				lcdSetAutonomous(selectedAuto - 1);
			} else if (button == kButtonRight && selectedAuto < ARRAY_SIZE(autos) - 1) {
				lcdSetAutonomous(selectedAuto + 1);
			}
		} else {
      if(!isAutonomous()){
			     lcdSetText(uart1, 1, "Driver control");
      }
		}
    if(!isAutonomous()){
		    lcdPrint(uart1, 2, "Main: %lf", powerLevelMain()/1000.0);
    }

		taskDelay(50);
	}
}




void initialize(){




  /*

  PID BL = {
    .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 1500, .sensor = 0
  };
  PID BR = {
    .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 1500, .sensor = 0
  };
  PID T = {
    .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 1500, .sensor = 0
  };
  PID RD = {
    .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0
  };
  PID LD = {
    .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0
  };
  */

  quadLeftDrive = encoderInit(QuadLeft1, QuadLeft2, true);
  quadRightDrive = encoderInit(QuadRight1, QuadRight2, false);
  mainQuad = encoderInit(mainQuad1, mainQuad2, false);

  TaskHandle jkjkjkjTH = taskRunLoop(debug, 500);
  BL.target = BR.target = LIFT_STANDARD_POS;
  BL.Kp = 0.3;
  BL.Ki = 0.01;
  BL.Kd = 0.0;
  BL.MAX_ERROR = 35;

  BR.Kp = 0.3;
  BR.Ki = 0.01;
  BR.Kd = 0.0;
  BR.MAX_ERROR = 35;

  T.target = CB_STANDARD_POS;
  T.Kp = 0.11;
  T.Ki = 0.004;
  T.Kd = 0.0;
  T.MAX_ERROR = 30;

  RD.Kp = 0.3;
  RD.Ki = 0.03;
  RD.Kd = 0.0;
  RD.MAX_ERROR = 50;

  LD.Kp = 0.3;
  LD.Ki = 0.03;
  LD.Kd = 0.0;
  LD.MAX_ERROR  = 50;
  //lcdInit(uart1);
  //taskCreate(lcdAutonomousSelection, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);


}
