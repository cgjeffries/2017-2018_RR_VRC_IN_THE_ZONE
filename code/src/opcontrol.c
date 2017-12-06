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
bool basePresent = false;
bool isStacking  = false;

//Global Arrays
int liftTarget[16]={
  1500,//0
  1500,//1
  1500,//2
  1500,//3
  1500,//4
  1500,//5
  1500,//6
  1500,//7
  1500,//8
  1500,//9
  1500,//10
  1500,//11
  1500,//12
  1500,//13
  1500,//14
  1500 //15
};
int chainTarget[16]={
  1500,//0
  1500,//1
  1500,//2
  1500,//3
  1500,//4
  1500,//5
  1500,//6
  1500,//7
  1500,//8
  1500,//9
  1500,//10
  1500,//11
  1500,//12
  1500,//13
  1500,//14
  1500 //15
};


/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
 void old(){
	BL.target = BR.target = 1700;

 	BL.Kp = 0.2;
 	BL.Ki = 0.01;
 	BL.Kd = 0.4;

 	BR.Kp = 0.2;
 	BR.Ki = 0.01;
 	BR.Kd = 0.4;

 	T.Kp = 0.0;
 	T.Ki = 0.0;
 	T.Kd = 0.0;

 	TaskHandle firstTH = taskRunLoop(mainLoopOp, 20);
 	//TaskHandle secondTH = taskRunLoop(debug, 200);

 	while (true) {
 		if(1==1){
 			if(digitalRead(button1) == LOW){
 				BL.target = BR.target = 1500;
 			}
 			else if(digitalRead(button2) == LOW){
 				BR.target = BL.target = 2500;
 			}
 		}
 		else if(2==1){
 			if(encoderGet(mainQuad) >= 1000){
 				if(encoderGet(mainQuad) <= 3000){
 					BL.target = BR.target = encoderGet(mainQuad);
 				}
 				else{
 					BL.target = BR.target = 3000;
 				}
 			}
 			else{
 				BL.target = BR.target = 1000;
 			}
 		}
 		else{
 			if(joystickGetDigital(1, 8, JOY_UP)){
 				if(!(BL.target >= 2000)){
 					BL.target += 10;
 					BR.target += 10;
 				}
 			}
 			else if(joystickGetDigital(1, 8, JOY_DOWN)){
 				if(!(BL.target <= 0)){
 					BL.target -= 10;
 					BR.target -= 10;
 				}
 			}

 			if(joystickGetDigital(1, 7, JOY_UP)){
 				if(!(T.target >= 3900)){
 					T.target += 10;
 				}
 			}
 			else if(joystickGetDigital(1, 7, JOY_DOWN)){
 				if(!(T.target <= 0)){
 					T.target -= 10;
 				}
 			}
 			delay(20);
 		}
 	}
 	taskDelete(firstTH); //just to remove the stupid "unused variable" thing from above
 	//taskDelete(secondTH);
 }
 bool liftDisabled = false;
void operatorControl() {
  if(!digitalRead(10)){
    while(!joystickGetDigital(1, 8, JOY_DOWN)){
      delay(20);
    }
    autonomousAlt();
    while(true){
      delay(20);
    }
  }
  /*
	BL.target = BR.target = 1500;

	BL.Kp = 0.2;
	BL.Ki = 0.01;
	BL.Kd = 0.4;

	BR.Kp = 0.2;
	BR.Ki = 0.01;
	BR.Kd = 0.4;

	T.Kp = 0.0;
	T.Ki = 0.0;
	T.Kd = 0.0;
  */
  TaskHandle firstTH = taskRunLoop(mainLoopOp, 20);
  TaskHandle secondTH = taskCreate(awesomeLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  bool temporary = false;
  bool temporary2 = false;
  bool temporary3 = false;
  bool temporary4 = false;
	while(true){
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
