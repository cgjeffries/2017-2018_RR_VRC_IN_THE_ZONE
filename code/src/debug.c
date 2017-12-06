#include "main.h"
void debug(){
  printf("\n\n\n\n\n\n\n\n\n\n\n\n");
  printf("Estop? %d\n", eStop);
  printf("manual? %d\n", manual);
  printf("Cones: %d\n", coneCount);
  printf("Auto: LD: %d LDError: %f RD: %d RDError %f\n", (int)LD.sensor, LD.error, (int)RD.sensor, RD.error);
  printf("Sensors: LPot:%d RPot:%d CBPot:%d\n", analogRead(BLPot), analogRead(BRPot), analogRead(CBPot));
  printf("Lift Target: %f\n", BL.target);
  printf("BL: Error:%f Deriv:%f Integral:%f Result:%f KP:%f\n", BL.error, BL.derivative, BL.integral,((BL.Kp*BL.error + BL.Ki*BL.integral + BL.Kd*BL.derivative)), BL.Kp);
  printf("BR: Error:%f Deriv:%f Integral:%f\n", BR.error, BR.derivative, BR.integral);
  printf("T: Error:%f Deriv:%f Integral:%f Result:%f\n", T.error, T.derivative, T.integral, (T.Kp*T.error + T.Ki*T.integral + T.Kd*T.derivative));
  printf("LD: Error:%f Deriv:%f Integral:%f\n", LD.error, LD.derivative, LD.integral);
  printf("RD: Error:%f Deriv:%f Integral:%f", RD.error, RD.derivative, RD.integral);
}
