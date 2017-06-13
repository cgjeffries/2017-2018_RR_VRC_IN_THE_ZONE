#include "main.h"

void setTop(int speed){
  motorSet(chainLeft, speed);
  motorSet(chainRight, speed);
}

void updateSensors(){
  BL.sensor = analogRead(BLPot); //fix this
  BR.sensor = analogRead(BRPot);
}

double PIDdo(PID *thing){
  updateSensors();
  thing->error  = thing->target - thing->sensor;
  if(abs(thing->error) < 200){
    if(abs(thing->error < 8)){
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

void mainLoop(){
  motorSet(liftLeft, ((int) PIDdo(&BL)));
  motorSet(liftRight, ((int) PIDdo(&BR)));
  setTop((int) PIDdo(&T));
}
