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
void setClaw(int speed){
  motorSet(claw, speed);
}
void setBaseRight(int speed){
  motorSet(baseRight, -speed);
}
void setBaseLeft(int speed){
  motorSet(baseLeft, -speed);
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

void awesomeLoop(){
  while(true){
    if(isStacking){
      BR.target = BL.target = liftTarget[coneCount];
      T.target = chainTarget[coneCount];
    }
    else{
      BR.target = BL.target = LIFT_STANDARD_POS;
      T.target = CB_STANDARD_POS;
    }
    delay(50);
  }
}
