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
    if(thing->target < 1000){//may need to be updated to reflect current pot values
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
        if(BL.target < 1450){
          setLiftLeft((int) PIDdo(&BL) + 0);
          setLiftRight((int) PIDdo(&BR) + 0);
        }
        else{
          setLiftLeft((int) PIDdo(&BL) + 8);
          setLiftRight((int) PIDdo(&BR) + 8);
        }
      }
      if(joystickGetDigital(1, 8, JOY_UP) && manual){
        setChain(0);
      }
      else{
        if(T.target < 2500){
          if(T.target < 400){
            setChain((int) PIDdo(&T));
          }
          else{
            setChain((int) PIDdo(&T) + 5);
          }
        }
        else if(T.target > 2500 && T.target < 2900){
          if(T.error < 700 && T.error > 0){
            int value = PIDdo(&T);
            if (value > 50) {
              setChain(50);
            }else{
              setChain(value);
            }
          }
          else if(T.error < 0){
            setChain(PIDdo(&T) - 15);
          }
          else{
            setChain((int) PIDdo(&T)-5);
          }
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
  if(!autoPIDDisable){
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
}
