//Motors
#define liftLeft 2
#define liftRight 9
#define chainLeft 3
#define chainRight 8

#define driveLeftFront 4
#define driveLeftBack 5
#define driveRightFront 7
#define driveRightBack 6

//sensors
#define BLPot 1
#define BRPot 2
#define button1 1
#define button2 2
#define QuadLeft1 3
#define QuadLeft2 4
#define QuadRight1 5
#define QuadRight2 6


//PID structs
#ifndef TEST0
#define TEST0
typedef struct {
  double Kp;
  double Ki;
  double Kd;
  double error;
  double previous_error;
  double integral;
  double derivative;
  double target;
  double sensor;
}PID;

PID BL;
PID BR;
PID T;

#endif

//thread prototypes
void mainLoop();
void debug();
