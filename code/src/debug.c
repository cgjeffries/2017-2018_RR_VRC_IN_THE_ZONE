#include "main.h"
void debug(){
  printf("\n\n\n\n\n");
  printf("BL: Error:%lf Deriv:%lf Integral:%lf\n", BL.error, BL.derivative, BL.integral);
  printf("BR: Error:%lf Deriv:%lf Integral:%lf\n", BR.error, BR.derivative, BR.integral);
  printf("T: Error:%lf Deriv:%lf Integral:%lf\n", T.error, T.derivative, T.integral);
}
