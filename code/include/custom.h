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

//PID structs
#ifndef NAME
typedef struct NAME{
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
#endif
#ifndef BL
PID BL = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0
};
#endif
#ifndef BR
PID BR = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0
};
#endif
#ifndef T
PID T = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0
};
#endif

//thread prototypes
void mainLoop();
void debug();
