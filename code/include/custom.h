//Motors
#define liftLeft 2
#define liftRight 9
#define chainLeft 3
#define chainRight 8

//PID structs
struct PID {
  double Kp = 0;
  double Ki = 0;
  double Kd = 0;
  double error = 0;
  double previous_error = 0;
  double integral = 0;
  double derivative = 0;
  double target = 0;
  double sensor = 0;
};

struct PID BL;
struct PID BR;
struct PID T;

//thread prototypes
void mainLoop();
void debug();
