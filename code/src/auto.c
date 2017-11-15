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
void autonomous() {
  //Lift safety
  BL.target = BR.target = 1500; //FIND THIS VALUE!!!
  //Chain Bar safety:
  T.target = 1500; //FIND THIS VALUE!!!

  //DR4B Left constants
	BL.Kp = 0.2;
	BL.Ki = 0.01;
	BL.Kd = 0.4;

  //DR4B Right constants
	BR.Kp = 0.2;
	BR.Ki = 0.01;
	BR.Kd = 0.4;

  //Chain Bar constants
	T.Kp = 0.0;
	T.Ki = 0.0;
	T.Kd = 0.0;

  //Left Drive constants
  LD.Kp = 0.2;
  LD.Ki = 0.0;
  LD.Kd = 0.0;

  //Right Drive constants
  RD.Kp = 0.2;
  RD.Ki = 0.0;
  RD.Kd = 0.0;



}
