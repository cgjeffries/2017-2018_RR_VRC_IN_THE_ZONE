#include "main.h"

bool loaderStacking = false;


void setDriveLeft(int speed){
  motorSet(driveLeft, speed);
  motorSet(driveLeft2, -speed);
}
void setDriveRight(int speed){
  motorSet(driveRight, -speed);
  motorSet(driveRight2, -speed);
}
void setDriveAll(int speed){
  setDriveLeft(speed);
  setDriveRight(speed);
}
void setLiftLeft(int speed){
  motorSet(liftLeft, speed);
}
void setLiftRight(int speed){
  motorSet(liftRight, -speed);
}
void setChainLeft(int speed){
  motorSet(chainLeft, -speed);
}
void setChainRight(int speed){
  motorSet(chainRight, speed);
}


void setChain(int speed){
  setChainLeft(speed);
  if((T.target<500 && speed < 0) && true==false){
    setChainRight(speed);
  }
  else{
    setChainRight(speed);
  }
}
void setClaw(int speed){
  motorSet(claw, -speed);
}
void setBaseRight(int speed){
  motorSet(base, -speed);
}
void setBaseLeft(int speed){
  motorSet(base, -speed);
}
void setBase(int speed){
  if(baseLiftCounts > 700 && baseLiftCounts <= 1030){
    setBaseLeft(0);
    setBaseRight(0);
  }
    setBaseLeft(speed);
    setBaseRight(speed);
}

int brakingpower = 0;

void buttonLift(){
  if(joystickGetDigital(1, 5, JOY_UP)){
    setLiftLeft(127);
  }
  else if (joystickGetDigital(1, 5, JOY_DOWN)){
    setLiftLeft(-60);
  }
  else{
    setLiftLeft(15);
  }

  if(joystickGetDigital(1, 6, JOY_UP)){
    setLiftRight(127);
  }
  else if (joystickGetDigital(1, 6, JOY_DOWN)){
    setLiftRight(-60);
  }
  else{
    setLiftRight(15);
  }

  if(joystickGetDigital(1, 8, JOY_DOWN)){
    setChainLeft(-127);
    setChainRight(-127);
  }
  else if(joystickGetDigital(1, 8, JOY_UP)){
    setChainLeft(127);
    setChainRight(127);
  }
  else{
    setChainLeft(0);
    setChainRight(0);
  }

  if(joystickGetDigital(1, 8, JOY_LEFT)){
    setClaw(-127);
    brakingpower = -15;
  }
  else if(joystickGetDigital(1, 8, JOY_RIGHT)){
    setClaw(127);
    brakingpower = 0;
  }
  else{
    setClaw(brakingpower);
  }

  if(joystickGetDigital(1, 7, JOY_DOWN)){
    setBaseLeft(-127);
    setBaseRight(-127);
  }
  else if(joystickGetDigital(1, 7, JOY_UP)){
    setBaseLeft(127);
    setBaseRight(127);
  }
  else{
    setBaseLeft(0);
    setBaseRight(0);
  }
}

void joystickDrive(){
  if(abs(joystickGetAnalog(1, 2)) >= 10){
    setDriveRight(joystickGetAnalog(1, 2));
  }
  else{
    setDriveRight(0);
  }

  if(abs(joystickGetAnalog(1, 3)) >= 10){
    setDriveLeft(joystickGetAnalog(1, 3));
  }
  else{
    setDriveLeft(0);
  }
}

void manualControl(){
  joystickDrive();
  buttonLift();
}

void motorTest(){
  if(joystickGetDigital(1, 8, JOY_DOWN)){
    motorSet(1, 60);
  }
  else if(joystickGetDigital(1, 8, JOY_RIGHT)){
    motorSet(2, 60);
  }
  else if(joystickGetDigital(1, 8, JOY_UP)){
    motorSet(3, 60);
  }
  else if(joystickGetDigital(1, 8, JOY_LEFT)){
    motorSet(4, 60);
  }
  else if(joystickGetDigital(1, 7, JOY_DOWN)){
    motorSet(5, 60);
  }
  else if(joystickGetDigital(1, 7, JOY_RIGHT)){
    motorSet(6, 60);
  }
  else if(joystickGetDigital(1, 7, JOY_UP)){
    motorSet(7, 60);
  }
  else if(joystickGetDigital(1, 7, JOY_LEFT)){
    motorSet(8, 60);
  }
  else if(joystickGetDigital(1, 6, JOY_DOWN)){
    motorSet(9, 60);
  }
  else if(joystickGetDigital(1, 6, JOY_UP)){
    motorSet(10, 60);
  }
  else{
    motorSet(1, 0);
    motorSet(2, 0);
    motorSet(3, 0);
    motorSet(4, 0);
    motorSet(5, 0);
    motorSet(6, 0);
    motorSet(7, 0);
    motorSet(8, 0);
    motorSet(9, 0);
    motorSet(10, 0);
  }
}

bool eStop = false;

//BEGIN LIFT AUTOMATION
void liftTo(int pos){
  if(!eStop){
    BL.target = BR.target = pos;
    delay(20);
    while(((fabs(BL.error) > 100) || (fabs(BR.error) > 100)) && !eStop){
      delay(20);
    }
  }
}
void liftToPrecise(int pos){
  if(!eStop){
    BL.target = BR.target = pos;
    delay(20);
    if(pos < 1430){
      while(((BL.error < -50) || (BR.error < -50)) && !eStop){
        delay(20);
      }
    }
    else{
      while(((fabs(BL.error) > 75) || (fabs(BR.error) > 75)) && !eStop){
        delay(20);
      }
    }
  }
}



void chainTo(int pos){
  if(!eStop){
    T.target = pos;
    delay(40);
    if(pos == CB_HALF_POS){
      while((fabs(T.error) > 200) && !eStop){
        delay(20);
      }
    }
    else if(pos == CB_VERTICAL_POS || pos == CB_VERTICAL_POS2){
      while(T.error > 100){
        delay(20);
      }
    }
    else{
      while((fabs(T.error) > 100) && !eStop){
        delay(20);
      }
    }
  }
}
int baseBreak = 0;
void baseDown(){
  stuff = 1;
  setBase(-127);
  BL.target = BR.target = (BL.target + 100);
  delay(300);
  T.target = 2000;
  delay(300);
  BL.target = BR.target = (BL.target - 200);
  delay(300);
  setBase(0);
  baseBreak = 0;
  stuff = 0;
}
void holdCone(){
  stuff = 1;
  int height;
  if(coneCount >= 4){
    if(coneCount >= 10){
      height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT) - 90;
    }
    else{
      height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT) - 130;
    }
  }
  else{
    height = ONE_CONE_PYLON_STACK_HEIGHT + 240-130;
  }
  //setClaw(-127);
  //liftTo(1450);
  //liftTo(1500);
  //delay(CLAW_CLOSE_TIME);
  //setClaw(-10);
  BL.target = BR.target = height;
  delay(20);
  chainTo(CB_HALF_POS);
  liftTo(height);

  if(coneCount > 6){
    if(coneCount > 10){
      chainTo(CB_VERTICAL_POS2);
    }
    else{
      chainTo(CB_VERTICAL_POS2);
    }
  }
  else{
    chainTo(CB_VERTICAL_POS);
  }
  delay(400);
  if(coneCount > 6){
    liftTo(height-320);
  }
  else{
    if(coneCount > 1){
      //liftTo(height-150);
    }
  }
  while(joystickGetDigital(1, 5, JOY_UP)){
    delay(10);
  }
  stuff = 0;
}
bool held = false;
void stackCone(int delayReduction, int heightReduction){
  stuff = 1;
  int height;
  if(coneCount >= 4){
    if(coneCount >= 10){
      height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT) - 90;
    }
    else{
      height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT) - 130;
    }
  }
  else{
    if(coneCount == 3){
      height = ONE_CONE_STACK_HEIGHT+25;
    }
    else{
      height = ONE_CONE_STACK_HEIGHT; //+ (coneCount*CONE_HEIGHT);
    }
  }
  coneCount++;
  setClaw(-127);
  //liftTo(1450);
  liftToPrecise(1360-heightReduction);
  //if(!held){
  if(coneCount > 4){
    delay(CLAW_CLOSE_TIME-delayReduction);
  }
  else{
      delay(CLAW_CLOSE_TIME);
  }
    held = false;
  //}
  setClaw(-20);
  if(coneCount < 999){
    BL.target = BR.target = height;
  }
  else{
    BL.target = BR.target = height-175;
  }
  delay(20);
  //if(T.target < CB_HALF_POS){
    //chainTo(CB_HALF_POS);
  //}
  T.target = CB_HALF_POS;
  while(BL.error > 500){
    delay(20);
  }
  if(coneCount > 999){ //8
    T.target = CB_VERTICAL_POS2+130;
  }
  else{
    T.target = CB_VERTICAL_POS;
  }
  /*
  if(coneCount > 6){
    chainTo(CB_VERTICAL_POS2);
  }
  else{
    chainTo(CB_VERTICAL_POS);
  }
  */
  if(coneCount >= 4){
    liftTo(height);
  }
  /*
  if(coneCount > 6){
    T.target = CB_VERTICAL_POS2;
  }
  else{
    T.target = CB_VERTICAL_POS;
  }
  */
  while(T.error > 300){
    delay(20);
  }
/*
  if(coneCount > 1){
    BL.target = BR.target = height-LIFT_DROP +125;
  }
  */
  if(coneCount > 4){  //8
    //chainTo(CB_VERTICAL_POS2+130);
  }
  else{
    chainTo(CB_VERTICAL_POS2);
  }
  //delay(250);

  if(coneCount > 4){
    liftToPrecise(height-LIFT_DROP);
  }
  else{
    delay(200);
  }


  /*
  while(joystickGetDigital(1, 5, JOY_UP)){
    delay(10);
  }
  */
  stuff = 0;
}

void stackConePylon(int delayReduction){
  stuff = 1;
  int height = ONE_CONE_PYLON_STACK_HEIGHT + (coneCountPylon*CONE_HEIGHT);
  coneCountPylon++;
  setClaw(-127);
  //liftTo(1450);
  liftTo(1350);
  delay(CLAW_CLOSE_TIME-delayReduction);
  setClaw(-10);
  BL.target = BR.target = height;
  delay(20);
  chainTo(CB_HALF_POS);
  while(BL.error > 500){
    delay(20);
  }
  chainTo(CB_VERTICAL_PYLON-100);
  liftTo(height);
  delay(250);
  while(joystickGetDigital(1, 5, JOY_UP)){
    delay(10);
  }
  stuff = 0;
}
void resetLift(){
  stuff = 1;
  int height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT) - 100;
  setClaw(127);
  if(coneCount <= 1){
    delay(300);
  }
  else{
    delay(CLAW_OPEN_TIME);
  }
  if(coneCount>1){
    if(coneCount > 7){
      BL.target = BR.target  = (height);
    }
    else{
      BL.target = BR.target  = (height-50);
    }
  }
  delay(CLAW_OPEN_TIME/2);
  //setClaw(10);
  T.target = CB_STANDARD_POS;
  delay(40);
  while(fabs(T.error) > 2400){
    delay(20);
  }
  setClaw(10);
  BR.target = BL.target = LIFT_STANDARD_POS;
  chainTo(CB_STANDARD_POS);
  if(joystickGetDigital(1, 6, JOY_DOWN)){
    held = true;
    setClaw(-127);
    liftTo(1400);
  }
  else{
    liftTo(LIFT_STANDARD_POS);
  }
  chainTo(CB_STANDARD_POS);
  while(joystickGetDigital(1, 5, JOY_DOWN)){
    delay(10);
  }
  stuff = 0;
}
void resetLift2(){
  stuff = 1;
  int height;
  if(coneCount >= 4){
    height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT) -100;
  }
  else{
    height = 1450;
  }
  setClaw(127);
  delay(CLAW_OPEN_TIME);
  if(coneCount>1){
    BL.target = BR.target  = (height-50);
  }
  delay(CLAW_OPEN_TIME/2);
  setClaw(10);
  liftTo(height-50);
  T.target = 1400;
  delay(30);
  while(fabs(T.error) > 1500){
    delay(20);
  }
  setClaw(10);
  BR.target = BL.target = LIFT_STANDARD_POS;
  //liftTo(height-100);
  //chainTo(1200);
  if(joystickGetDigital(1, 6, JOY_UP)){
    held = true;
    setClaw(-127);
    liftTo(1429);
  }
  else{
    liftTo(LIFT_STANDARD_POS);
  }
  //chainTo(1400);
  while(T.error < -100 && !eStop){
    delay(20);
  }
  while(joystickGetDigital(1, 5, JOY_DOWN)){
    delay(10);
  }
  stuff = 0;
}
void resetLift3(){
  stuff = 1;
  int height = ONE_CONE_PYLON_STACK_HEIGHT + (coneCountPylon*CONE_HEIGHT);
  liftTo(height-LIFT_DROP);
  setClaw(127);
  delay(CLAW_OPEN_TIME+250);
  setClaw(10);
  liftTo(height-100);
  while(!digitalRead(PylonButton)){
    delay(20);
  }
  delay(1000);
  chainTo(CB_STANDARD_POS);
  liftTo(LIFT_STANDARD_POS);
  chainTo(CB_STANDARD_POS);
  while(joystickGetDigital(1, 5, JOY_DOWN)){
    delay(10);
  }
  stuff = 0;
}
bool manual = false;
void baseMode(){
  BR.target = BL.target = 1800;
  T.target = CB_VERTICAL_POS+1000;
}


void awesomeLoop(void *ignore){
  //baseMode();
  //delay(300);
  //setBase(-127);
  //delay(900);
  //setBase(-10);
  while(true){
    if(!boolAuton){
    if(!manual){
      stuff = 0;
      if(joystickGetDigital(1, 5, JOY_UP)){
        holdCone();
      }
      else if(joystickGetDigital(1, 6, JOY_DOWN)){
        stackCone(0, 0);
        resetLift();
      }
      else if(joystickGetDigital(1, 5, JOY_DOWN)){
        baseDown();
      }
      else if(joystickGetDigital(1, 7, JOY_RIGHT)){
        resetLift();
      }
      else if(joystickGetDigital(1, 6, JOY_UP)){
        stackCone(200, -80);
        resetLift2();
      }
      else if(joystickGetDigital(1, 8, JOY_RIGHT)){
        resetLift2();
      }
      else if(joystickGetDigital(2, 7, JOY_UP)){
        baseMode();
      }
      else if(joystickGetDigital(2, 8, JOY_UP)){
        coneCount = 0;
      }
      else if(joystickGetDigital(2, 5, JOY_UP)){
        stackConePylon(0);
        while(digitalRead(PylonButton)){
          delay(20);
          if(joystickGetDigital(2, 5, JOY_DOWN)){
            break;
          }
          if(joystickGetDigital(1, 7, JOY_RIGHT) || eStop){
            break;
          }
        }
        if(!joystickGetDigital(1, 7, JOY_RIGHT) && !eStop){
          delay(250);
          resetLift3();
        }
      }


      if(joystickGetDigital(1, 7, JOY_DOWN)){
        setBase(-127);
        baseBreak = -5;
      }
      else if(joystickGetDigital(1, 7, JOY_UP)){
        setBase(127);
        baseBreak = 10;
      }
      else{
        setBase(0 + baseBreak);
      }
    }
    else{
      stuff = 2;
      if(joystickGetDigital(1, 5, JOY_UP)){
        if(BL.target < LIFT_MAX){
          BL.target = BR.target = BR.target + 25;
        }
      }
      else if(joystickGetDigital(1, 5, JOY_DOWN)){
        if(BL.target > LIFT_MIN){
          BL.target = BR.target = BR.target - 25;
        }
      }

      if(joystickGetDigital(1, 6, JOY_UP)){
        if(T.target < CHAIN_MAX){
          T.target = T.target + 100;
        }
      }
      else if(joystickGetDigital(1, 6, JOY_DOWN)){
        if(T.target > CHAIN_MIN){
          T.target = T.target - 100;
        }
      }

      if(joystickGetDigital(1, 8, JOY_LEFT)){
        setClaw(-127);
        brakingpower = -15;
      }
      else if(joystickGetDigital(1, 8, JOY_RIGHT)){
        setClaw(127);
        brakingpower = 10;
      }
      else{
        setClaw(brakingpower);
      }

      if(joystickGetDigital(1, 7, JOY_DOWN)){
        setBaseLeft(-127);
        setBaseRight(-127);
      }
      else if(joystickGetDigital(1, 7, JOY_UP)){
        setBase(127);
      }
      else{
        setBase(0);
      }
    }
    delay(50);
  }
  }
}
