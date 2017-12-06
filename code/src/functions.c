#include "main.h"

void setDriveLeft(int speed){
  motorSet(driveLeft, speed);
}
void setDriveRight(int speed){
  motorSet(driveRight, -speed);
}
void setLiftLeft(int speed){
  motorSet(liftLeft, -speed);
}
void setLiftRight(int speed){
  motorSet(liftRight, speed);
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
  motorSet(baseRight, -speed);
}
void setBaseLeft(int speed){
  motorSet(baseLeft, -speed);
}
void setBase(int speed){
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
void chainTo(int pos){
  if(!eStop){
    T.target = pos;
    delay(20);
    if(pos == CB_HALF_POS){
      while((fabs(T.error) > 300) && !eStop){
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
void baseDown(){
  setBase(-127);
  BL.target = BR.target = (BL.target + 100);
  delay(200);
  T.target = 2400;
  delay(300);
  BL.target = BR.target = (BL.target - 300);
  delay(500);
  setBase(0);
}
void holdCone(){
  int height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT);
  //setClaw(-127);
  //liftTo(1450);
  //liftTo(1500);
  //delay(CLAW_CLOSE_TIME);
  //setClaw(-10);
  BL.target = BR.target = height;
  chainTo(CB_HALF_POS);
  liftTo(height);
  if(coneCount > 6){
    chainTo(CB_VERTICAL_POS2);
  }
  else{
    chainTo(CB_VERTICAL_POS);
  }
  delay(250);
  if(coneCount > 1){
    liftTo(height-300);
  }
  else{
    if(coneCount > 1){
      liftTo(height-150);
    }
  }
  while(joystickGetDigital(1, 5, JOY_UP)){
    delay(10);
  }
}
void stackCone(int delayReduction = 0){
  int height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT);
  coneCount++;
  setClaw(-127);
  //liftTo(1450);
  liftTo(1475);
  delay(CLAW_CLOSE_TIME-delayReduction);
  setClaw(-10);
  BL.target = BR.target = height;
  chainTo(CB_HALF_POS);
  while(BL.error > 500){
    delay(20);
  }
  if(coneCount > 6){
    chainTo(CB_VERTICAL_POS2);
  }
  else{
    chainTo(CB_VERTICAL_POS);
  }
  liftTo(height);
  if(coneCount > 6){
    chainTo(CB_VERTICAL_POS2);
  }
  else{
    chainTo(CB_VERTICAL_POS);
  }
  delay(250);
  if(coneCount > 1){
    liftTo(height-LIFT_DROP);
  }
  else{
    if(coneCount > 1){
      liftTo(height-100);
    }
  }
  while(joystickGetDigital(1, 5, JOY_UP)){
    delay(10);
  }
}
void resetLift(){
  int height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT);
  setClaw(127);
  delay(CLAW_OPEN_TIME);
  setClaw(10);
  liftTo(height-100);
  chainTo(CB_STANDARD_POS);
  liftTo(LIFT_STANDARD_POS);
  chainTo(CB_STANDARD_POS);
  while(joystickGetDigital(1, 5, JOY_DOWN)){
    delay(10);
  }
}
void resetLift2(){
  int height = ONE_CONE_STACK_HEIGHT + (coneCount*CONE_HEIGHT);
  setClaw(127);
  delay(CLAW_OPEN_TIME);
  setClaw(10);
  liftTo(height-100);
  chainTo(1200);
  liftTo(LIFT_STANDARD_POS);
  chainTo(1200);
  while(joystickGetDigital(1, 5, JOY_DOWN)){
    delay(10);
  }
}
bool manual = false;

void awesomeLoop(void *ignore){
  while(true){
    if(!manual){
      if(joystickGetDigital(1, 5, JOY_UP)){
        holdCone();
      }
      else if(joystickGetDigital(1, 6, JOY_DOWN)){
        stackCone();
        resetLift();
      }
      else if(joystickGetDigital(1, 5, JOY_DOWN)){
        baseDown();
      }
      else if(joystickGetDigital(1, 7, JOY_RIGHT)){
        resetLift();
      }
      else if(joystickGetDigital(1, 6, JOY_UP)){
        stackCone(250);
        resetLift2();
      }
      else if(joystickGetDigital(1, 8, JOY_RIGHT)){
        resetLift2();
      }
      if(joystickGetDigital(1, 8, JOY_LEFT)){
        eStop = true;
      }
      else{
        eStop = false;
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
    else{
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
        setBaseLeft(127);
        setBaseRight(127);
      }
      else{
        setBaseLeft(0);
        setBaseRight(0);
      }
    }
    delay(50);
  }
}
