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

 void turnTest(){
   BL.target = BR.target = 0;
   LD.target = RD.target = 0;
   encoderReset(quadLeftDrive);
   encoderReset(quadRightDrive);
   TaskHandle blaTH = taskRunLoop(mainLoopAuto, 20);
   LD.target = 550;
   RD.target =-550;
   delay(20);

   while(LD.error > 50 || RD.error < -50){
     delay(20);
     //

   //
   }
 }
 bool autoPIDDisable = false;

void autonomousBC20B(){
  BL.target = BR.target = 0;
  LD.target = RD.target = 0;
  delay(20);
  setClaw(-20);
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  T.target = CB_VERTICAL_POS;
  BL.target = BR.target = 2100;
  RD.Kp = LD.Kp = 0.15;
  delay(50);
  setDriveAll(30);
  delay(100);
  TaskHandle blaTH = taskRunLoop(mainLoopAuto, 20);
  delay(600);

  setBase(-127);
  delay(500);
  RD.target = 1550;
  LD.target = 1550;
  delay(20);
  // TaskHandle blaTH = taskRunLoop(mainLoopAuto, 20);
  delay(1000);
  setBase(-10);
  while(RD.error > 100){
    delay(20);
  }
  delay(500);
  setBase(127);
  delay(1750);
  setBase(10);
  BL.target = BR.target = 1400;
    delay(25);
  while(fabs(BL.error) > 60){
    delay(20);
  }
  delay(1000);
  setClaw(127);
  delay(250);
  setClaw(10);

  delay(200);
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
    RD.Kp = LD.Kp = 0.3;
  LD.target = -1450;
  RD.target = -1450;
  delay(25);

  while(LD.error < -50 || RD.error < -50){
    delay(20);
  }

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = 190;
  RD.target = -190;
  delay(25);

  while(LD.error > 50 || RD.error < -50){
    delay(20);
    //
  //
  }
  delay(250);

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  RD.target = -500;
  LD.target = -500;
  BL.target = BR.target = 1900;
  delay(25);
  while(LD.error > 50 || RD.error < -50){
    delay(20);
    //
  //
  }

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = 330;
  RD.target = -330;
  delay(25);
  while(LD.error > 50 || RD.error < -50){
    delay(20);
    //
  //
  }
  autoPIDDisable = true;
  delay(25);
  setDriveAll(127);
  delay(500);
  setBase(-127);
  delay(250);
  setBase(0);
  delay(1250);
  setBase(0);
  setDriveAll(-127);
  delay(1000);
  setDriveAll(0);
  delay(300);
  if(false){
    setDriveAll(40);
    delay(1500);
    setDriveAll(0);

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    LD.target = -330;
    RD.target = 330;
    delay(25);
    autoPIDDisable = false;
    delay(30);
    while(RD.error > 50 || LD.error < -50){
      delay(20);
    }
    delay(20);
    setBase(-127);
    delay(1200);
    setBase(-10);
    delay(20);

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    RD.target = 100;
    LD.target = 100;
    BL.target = BR.target = 1900;
    delay(25);
    while(LD.error > 50 || RD.error > 50){
      delay(20);
    }
    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    LD.target = -350;
    RD.target = 350;
    delay(25);
    autoPIDDisable = false;
    delay(30);
    while(RD.error > 50 || LD.error < -50){
      delay(20);
    }

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    RD.target = 600;
    LD.target = 600;
    BL.target = BR.target = 1900;
    delay(25);
    while(LD.error > 50 || RD.error > 50){
      delay(20);
    }

    delay(500);
    setBase(127);
    delay(1300);
    setBase(0);

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    RD.target = -600;
    LD.target = -600;
    BL.target = BR.target = 1900;
    delay(25);
    while(LD.error < -50 || RD.error < -50){
      delay(20);
    }

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    LD.target = -330;
    RD.target = 330;
    delay(25);
    autoPIDDisable = false;
    delay(30);
    while(RD.error > 50 || LD.error < -50){
      delay(20);
    }

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    RD.target = 200;
    LD.target = 200;
    BL.target = BR.target = 1900;
    delay(25);
    while(LD.error > 50 || RD.error > 50){
      delay(20);
    }

    encoderReset(quadLeftDrive);
    encoderReset(quadRightDrive);
    LD.target = -330;
    RD.target = 330;
    delay(25);
    autoPIDDisable = false;
    delay(30);
    while(RD.error > 50 || LD.error < -50){
      delay(20);
    }
    autoPIDDisable = true;
    delay(30);
    setDriveAll(30);
    delay(500);
    setBase(-127);
    delay(1300);
    setBase(0);
    setDriveAll(-127);
    delay(500);
    setDriveAll(0);

  }

}

void autonomousBC20R(){
  BL.target = BR.target = 0;
  LD.target = RD.target = 0;
  delay(20);
  setClaw(-20);
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  T.target = CB_VERTICAL_POS;
  BL.target = BR.target = 2100;
  RD.Kp = LD.Kp = 0.15;
  delay(50);
  setDriveAll(30);
  delay(100);
  TaskHandle blaTH = taskRunLoop(mainLoopAuto, 20);
  delay(600);


  setBase(-127);
  delay(500);
  RD.target = 1550;
  LD.target = 1550;
  delay(1000);
  setBase(-10);
  while(RD.error > 100){
    delay(20);
  }
  setBase(127);
  delay(1750);
  setBase(0);
  BL.target = BR.target = 1400;
    delay(25);
  while(fabs(BL.error) > 60){
    delay(20);
  }
  delay(500);
  setClaw(127);
  delay(250);
  setClaw(10);

  delay(160);
  autoPIDDisable = true;
  delay(40);
  setDriveLeft(-30);
  delay(100);
  setDriveLeft(0);
  autoPIDDisable = false;
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = -1450;
  RD.target = -1450;
  RD.Kp = LD.Kp = 0.3;
  delay(25);

  while(LD.error < -50 || RD.error < -50){
    delay(20);
  }

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = -190;
  RD.target = 190;
  delay(25);

  while(LD.error < -50 || RD.error > 50){
    delay(20);
    //
  //
  }
  delay(250);

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  RD.target = -600;
  LD.target = -600;
  BL.target = BR.target = 1900;
  delay(25);
  while(LD.error < -50 || RD.error < -50){
    delay(20);
    //
  //
  }

  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  LD.target = -330;
  RD.target = 330;
  delay(25);
  while(LD.error < -50 || RD.error > 50){
    delay(20);
    //
  //
  }
  autoPIDDisable = true;
  delay(25);
  setDriveAll(127);
  delay(500);
  setBase(-127);
  delay(250);
  setBase(0);
  delay(1250);
  setBase(0);
  setDriveAll(-127);
  delay(1000);
  setDriveAll(0);
  delay(300);

}

void autonomousPC(){
  setClaw(-15);
  BL.target = BR.target = 0;
  LD.target = RD.target = 0;
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);

  TaskHandle blaTH = taskRunLoop(mainLoopAuto, 20);
  delay(20);
  BL.target = BR.target = ONE_CONE_PYLON_STACK_HEIGHT+ 100;
  T.target = CB_VERTICAL_PYLON-50;
  delay(1500);
  LD.target = RD.target = 700;
  delay(3000);
  BL.target = BR.target = ONE_CONE_PYLON_STACK_HEIGHT-LIFT_DROP;
  delay(500);
  setClaw(127);
  delay(500);

  BL.target = BR.target = ONE_CONE_PYLON_STACK_HEIGHT+100;
  delay(1000);
  setClaw(10);
  autoPIDDisable = true;
  delay(50);
  setDriveAll(-127);
  delay(500);
  setDriveAll(0);

}
void none(){
  delay(20);
  lcdSetText(uart1, 1, "      :(      ");
  lcdSetText(uart1, 2, " Robot is sad.");
  delay(20);
}

void ram(){
    autoPIDDisable = true;
    setDriveAll(127);
    delay(5000);
    setDriveAll(0);
}

void runAway(){
  autoPIDDisable = true;
  setDriveAll(127);
  delay(1000);
  setDriveAll(0);
}

bool boolAuton = false;

void autonomous() {
  boolAuton = true;
  taskDelete(secondTH); //For some reason this is necessary. PROS plz fix.
  if(firstTHstuff == 0){

  }
  else{
    //taskSuspend(firstTHstuff);
  }
  //taskSuspend(firstTH);
  delay(20);
  //TaskHandle haTH = taskRunLoop(debug, 500);
  BL.target = BR.target = LIFT_STANDARD_POS;
  LD.target = RD.target = 0;
  encoderReset(quadLeftDrive);
  encoderReset(quadRightDrive);
  //autonomousBC20B();

  if(analogRead(5) < 1333){
    autonomousBC20R();
    //runAway();
  }
  else if(analogRead(5) >=1333 && analogRead(5) <= 2666){
    autonomousPC();
    //ram();
  }
  else if(analogRead(5) > 2666){
    autonomousBC20B();
  }



  //autonomousPC();


  /*
  switch (selectedAuto){
    case BASE_CONE_20_BLUE:
      autonomousBC20B();
      break;
    case BASE_CONE_20_RED:
      autonomousBC20R();
      break;
    case PYLON_CONE:
      autonomousPC();
      break;
    case NOTHING:
      none();
      break;
    default:
      none();
      break;
  }
  //turnTest();
  //setBase(-127);
  */


}
