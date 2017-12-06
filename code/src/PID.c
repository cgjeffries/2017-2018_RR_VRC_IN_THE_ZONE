#include "main.h"

void setTop(int speed){
  motorSet(chainLeft, speed);
  motorSet(chainRight, speed);
}

void updateSensors(){
  BL.sensor = analogRead(BLPot);
  BR.sensor = analogRead(BRPot)+15;
  T.sensor = analogRead(CBPot);
  LD.sensor = encoderGet(quadLeftDrive);
  RD.sensor = encoderGet(quadRightDrive);
}

double PIDdo(PID *thing){
  updateSensors();
  thing->error  = thing->target - thing->sensor;
  if(fabs(thing->error) < 200){
    if(fabs(thing->error) < thing->MAX_ERROR){
      thing->integral = 0;
    }
    else{
      thing->integral += thing->error;
    }
  }
  else{
    thing->integral = 0;
  }
  //may need integral = 0 stuff
  thing->derivative = thing->error - thing->previous_error;
  thing->previous_error = thing->error;
  if(fabs(thing->error) < 20){
    if(thing->target < 1000){
      return 8;
    }
    return 13;
  }
  else{
    int output = (thing->Kp*thing->error + thing->Ki*thing->integral + thing->Kd*thing->derivative);
    if(output > 127){
      return 127;
    }
    else if(output < -127){
      return -127;
    }
    return output;
  }
}

void mainLoopOp(){
  if(true){
    if(!liftDisabled){
      if(joystickGetDigital(1, 8, JOY_DOWN) && manual){
        setLiftLeft(0);
        setLiftRight(0);
      }
      else{
        setLiftLeft((int) PIDdo(&BL) + 12);
        setLiftRight((int) PIDdo(&BR) + 12);
      }
      if(joystickGetDigital(1, 8, JOY_UP) && manual){
        setChain(0);
      }
      else{
        if(T.target < 1500){
          setChain((int) PIDdo(&T) + 15);
        }
        else{
          setChain((int) PIDdo(&T) - 20);
        }
      }
    }
  }
}
void mainLoopAuto(){
  setLiftLeft((int) PIDdo(&BL));
  setLiftRight((int)PIDdo(&BR));
  setChain((int) PIDdo(&T));
  if((LD.sensor>RD.sensor && LD.error > 500) && !(LD.target > 0 && RD.target < 0)){
    setDriveLeft((int) (PIDdo(&LD) * 0.4));
    setDriveRight((int) PIDdo(&RD));
  }
  else if((LD.sensor<RD.sensor && LD.error > 500) && !(LD.target < 0 && RD.target > 0)){
    setDriveRight((int) (PIDdo(&RD) * 0.4));
    setDriveLeft((int) PIDdo(&LD));
  }
  else{
    setDriveLeft((int) PIDdo(&LD));
    setDriveRight((int) PIDdo(&RD));
  }

}
