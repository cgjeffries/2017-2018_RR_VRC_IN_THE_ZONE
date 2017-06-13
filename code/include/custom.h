//Motors
#define liftLeft 2
#define liftRight 9
#define chainLeft 3
#define chainRight 8

//sensors
#define BLPot 1
#define BRPot 2
#define QUAD1 1
#define QUAD2 2
#define button1 3
#define button2 4

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
