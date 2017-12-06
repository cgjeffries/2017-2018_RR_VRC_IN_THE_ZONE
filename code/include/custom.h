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
#define BRPot 3
#define CBPot 2
#define expanderBatt 4
#define button1 1
#define button2 2
#define QuadLeft1 3
#define QuadLeft2 4
#define QuadRight1 1
#define QuadRight2 2
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
  int MAX_ERROR;
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
void awesomeLoop(void *ignore);

void setDriveLeft(int speed);
void setDriveRight(int speed);
void setLiftLeft(int speed);
void setLiftRight(int speed);
void setChainLeft(int speed);
void setChainRight(int speed);
void setChain(int speed);
void setClaw(int speed);
void setBase(int speed);

void buttonLift();
void joystickDrive();
void manualControl();
void motorTest();

void autonomousAlt();

//Position Definitions
#define CB_STANDARD_POS 200
#define CB_HALF_POS 1000
#define CB_VERTICAL_POS 3000
#define CB_VERTICAL_POS2 2950
#define LIFT_STANDARD_POS 1650
#define LIFT_DROP 175
#define ONE_CONE_STACK_HEIGHT 1550
#define CONE_HEIGHT 80
#define CLAW_CLOSE_TIME 750
#define CLAW_OPEN_TIME 600
#define LIFT_MAX 2500
#define LIFT_MIN 1450

#define CHAIN_MAX 3900
#define CHAIN_MIN 100

extern int chainTarget[16];
extern int liftTarget[16];
extern int coneCount;
extern bool basePresent;
extern bool isStacking;
extern bool manual;
extern bool liftDisabled;
extern bool eStop;
