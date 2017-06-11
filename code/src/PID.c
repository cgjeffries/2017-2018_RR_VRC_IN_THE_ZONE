#include "main.h"

void setTop(int speed){
  motorSet(chainLeft, speed);
  motorSet(chainRight, speed);
}

void updateSensors(PID *thing){
  thing->sensor = 0; //fix this
}

double PIDdo(PID *thing){
  updateSensors(thing);
  thing->error  = thing->target - thing->sensor;
  thing->integral += thing->error;
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
