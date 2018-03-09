/*
 * Copyright (C) 2017 Jude Brauer
 */
#include "main.h"

Encoder leftDriveEncoder;
Encoder rightDriveEncoder;

int selectedAuto = 0;

void initializeIO() {
}

#define vexCompetitionState ( (isEnabled()?0:2) + (isAutonomous()?1:0) )

#define kButtonNone     0
#define kButtonLeft     LCD_BTN_LEFT
#define kButtonRight    LCD_BTN_RIGHT

char *autos[] = {"Auto goal left", "Auto goal right", "Auto hold", "Stack stationary", "Skills", "PID drive test", "PID turn test"};

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
			lcdSetText(uart1, 1, "Driver control");
		}

		lcdPrint(uart1, 2, "Main: %lf", powerLevelMain()/1000.0);

		taskDelay(50);
	}
}

void initialize() {

	lcdInit(uart1);
	taskCreate(lcdAutonomousSelection, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

	leftDriveEncoder = encoderInit(1, 2, false);
	rightDriveEncoder = encoderInit(3, 4, true);
}
