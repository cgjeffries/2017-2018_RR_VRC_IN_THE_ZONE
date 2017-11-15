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

  quadLeftDrive = encoderInit(QuadLeft1, QuadLeft2, false);
  quadRightDrive = encoderInit(QuadRight1, QuadRight2, true);
  mainQuad = encoderInit(mainQuad1, mainQuad2, false);

  TaskHandle secondTH = taskRunLoop(debug, 200);
  BL.Kp = 0.075;
  BL.Ki = 0.0;
  BL.Kd = 0.0;

  BR.Kp = 0.075;
  BR.Ki = 0.0;
  BR.Kd = 0.0;

  T.Kp = 0.0;
  T.Ki = 0.0;
  T.Kd = 0.0;

  RD.Kp = 0.0;
  RD.Ki = 0.0;
  RD.Kd = 0.0;

  LD.Kp = 0.0;
  LD.Ki = 0.0;
  LD.Kd = 0.0;
}
