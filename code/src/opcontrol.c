/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

//Global Variables
int coneCount = 0;
int coneCountPylon = 0;
bool basePresent = false;
bool isStacking  = false;
TaskHandle secondTH;
TaskHandle firstTHstuff;

//Global Arrays
int baseLiftCounts = 0;

void updateI2C(){
  unsigned long now = millis();
  taskDelayUntil(&now, 50);
  imeGet(0, &baseLiftCounts);
  if(joystickGetDigital(2, 7, JOY_DOWN)){
    imeReset(0);
  }
}



 bool liftDisabled = false;
void operatorControl(){
  boolAuton = false;

  firstTHstuff = taskRunLoop(mainLoopOp, 20);
  secondTH = taskCreate(awesomeLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  //sTaskHandle thirdTH = taskCreate(playSpeaker, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  bool temporary = false;
  bool temporary2 = false;
  bool temporary3 = false;
  bool temporary4 = false;
  bool temporary5 = false;
  bool temporary6 = false;
	while(true){
    unsigned long now = millis();

    updateI2C();

    if(joystickGetDigital(1, 7, JOY_LEFT) && !temporary){
      manual = !manual;
      temporary = true;
    }
    else if(!joystickGetDigital(1, 7, JOY_LEFT) && temporary){
      temporary = false;
    }
    /*
    if(joystickGetDigital(1, 7, JOY_RIGHT) && !temporary2){
      liftDisabled = !liftDisabled;
      temporary2 = true;
    }
    else if(!joystickGetDigital(1, 7, JOY_RIGHT) && temporary2){
      temporary2 = false;
    }
    */

    if(joystickGetDigital(1, 8, JOY_UP) && !temporary3){
      if(!manual){
        coneCount++;
      }
      temporary3 = true;
    }
    else if(!joystickGetDigital(1, 8, JOY_UP) && temporary3){
      temporary3 = false;
    }

    if(joystickGetDigital(1, 8, JOY_DOWN) && !temporary4){
      if(coneCount > 0 && !manual){
        coneCount--;
      }
      temporary4 = true;
    }
    else if(!joystickGetDigital(1, 8, JOY_DOWN) && temporary4){
      temporary4 = false;
    }

    if(joystickGetDigital(2, 6, JOY_UP) && !temporary5){
      if(!manual){
        coneCountPylon++;
      }
      temporary5 = true;
    }
    else if(!joystickGetDigital(2, 6, JOY_UP) && temporary5){
      temporary5 = false;
    }

    if(joystickGetDigital(2, 6, JOY_DOWN) && !temporary6){
      if(coneCountPylon > 0 && !manual){
        coneCountPylon--;
      }
      temporary6 = true;
    }
    else if(!joystickGetDigital(2, 6, JOY_DOWN) && temporary6){
      temporary6 = false;
    }
    if(joystickGetDigital(1, 8, JOY_LEFT)){
      eStop = true;
      T.target = T.sensor;
      BR.target = BR.sensor;
      BL.target = BL.sensor;
    }
    else{
      eStop = false;
    }




    if(!digitalRead(11)){
      motorTest();
      delay(20);
    }
    else{
  		if(!digitalRead(12)){
  			manualControl();
  			delay(20);
  		}
  		else{
  			joystickDrive();

  		}
    }
	}
}
