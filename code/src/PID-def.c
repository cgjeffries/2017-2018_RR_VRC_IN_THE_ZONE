#include <main.h>
PID BL = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0, .MAX_ERROR = 0
};

PID BR = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0, .MAX_ERROR = 0
};

PID T = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0, .MAX_ERROR = 0
};

PID RD = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0, .MAX_ERROR = 0
};

PID LD = {
  .Kp = 0, .Ki = 0, .Kd = 0, .error = 0, .previous_error = 0, .integral = 0, .derivative = 0, .target = 0, .sensor = 0, .MAX_ERROR = 0
};
