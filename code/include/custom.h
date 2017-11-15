//Motors
#define baseRight 1
#define baseLeft 10
#define liftLeft 2
#define liftRight 9
#define chainLeft 3
#define chainRight 8

#define driveLeft 4
#define driveRight 7

#define claw 6


//sensors
#define BLPot 1
#define BRPot 2
#define CBPot 3
#define button1 1
#define button2 2
#define QuadLeft1 3
#define QuadLeft2 4
#define QuadRight1 5
#define QuadRight2 6
#define mainQuad1 7
#define mainQuad2 8


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
PID RD;
PID LD;

#endif

//thread prototypes
void mainLoopOp();
void mainLoopAuto();
void debug();

void setDriveLeft(int speed);
void setDriveRight(int speed);
void setLiftLeft(int speed);
void setLiftRight(int speed);
void setChainLeft(int speed);
void setChainRight(int speed);
void setClaw(int speed);

void buttonLift();
void joystickDrive();
void manualControl();
void motorTest();

//Position Definitions
#define CB_STANDARD_POS 2000;
#define LIFT_STANDARD_POS 2000;

extern int chainTarget[16];
extern int liftTarget[16];
extern int coneCount;
extern bool basePresent;
extern bool isStacking;
