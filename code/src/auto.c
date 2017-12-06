/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

void autonomousAlt(){
  setClaw(-15);
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  T.target = CB_VERTICAL_POS;
  TaskHandle firstTH = taskRunLoop(mainLoopAuto, 20);

  BL.target = BR.target = 1100;

  delay(500);
  setBase(-127);
  delay(750);
  RD.target = 1800;
  LD.target = 1800;
  delay(1000);
  setBase(-5);
  while(RD.error > 100){
    delay(20);
  }
  setBase(127);
  delay(1750);
  setBase(0);
  BL.target = BR.target = ONE_CONE_STACK_HEIGHT;
  while(BL.error > 30){
    delay(20);
  }
  setClaw(127);
  delay(250);
  setClaw(10);

  delay(200);
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = -200;
  RD.target = -200;
  /*
  while(LD.error < -50 || RD.error < -50){
    delay(20);
  }

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = 700;
  RD.target =-700;
  delay(20);

  while(LD.error > 50 || RD.error < -50){
    delay(20);
    //
    if(LD.error <= 210){
      LD.target = 700;
    }
    if(RD.error >= -210){
      RD.target = -700;
    }
  //
  }
  delay(250);

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  RD.target = 2500;
  LD.target = 2500;
  BL.target = BR.target = 1100;

  delay(3000);

  setBase(-127);
  delay(1300);
  setBase(-5);
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = -500;
  RD.target = -500;
  */

  /*
  delay(500);
  setBase(-127);
  delay(2000);
  setBase(0);
  T.target = CB_VERTICAL_POS;
  BL.target = BR.target = LIFT_MIN;
  RD.target = -700;
  LD.target = 700;
  */


}

void autonomous() {



}
