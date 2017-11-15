#include "main.h"
#include "math.h"

void setTop(int speed){
  motorSet(chainLeft, speed);
  motorSet(chainRight, speed);
}

void updateSensors(){
  BL.sensor = analogRead(BLPot);
  BR.sensor = analogRead(BRPot);
  T.sensor = analogRead(CBPot);
  LD.sensor = encoderGet(quadLeftDrive);
  RD.sensor = encoderGet(quadRightDrive);
}

double PIDdo(PID *thing){
  updateSensors();
  thing->error  = thing->target - thing->sensor;
  if(fabs(thing->error) < 200){
    if(fabs(thing->error) < 8){
      //thing->integral = 0;
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
  return (thing->Kp*thing->error + thing->Ki*thing->integral + thing->Kd*thing->derivative);
}

void mainLoopOp(){
  if(!(digitalRead(12) || digitalRead(11))){
    motorSet(liftLeft, ((int) PIDdo(&BL)));
    motorSet(liftRight, ((int) PIDdo(&BR)));
    setTop((int) PIDdo(&T));
  }
}
void mainLoopAuto(){
  motorSet(liftLeft, ((int) PIDdo(&BL)));
  motorSet(liftRight, ((int) PIDdo(&BR)));
  setTop((int) PIDdo(&T));
  setDriveLeft((int) PIDdo(&LD));
  setDriveRight((int) PIDdo(&RD));

}
