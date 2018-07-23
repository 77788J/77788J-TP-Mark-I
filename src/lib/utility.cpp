#include "utility.h"
#include "math.h"

// returns the sign (+, -, or 0) of a value
int sign(float x) {
  return (x > 0) - (x < 0);
}

// returns the lesser of two values
float min(float a, float b) {
  if (a < b) return a;
  else return b;
}

// returns the greater of two values
float max(float a, float b) {
  if (a > b) return a;
  else return b;
}

// constrains a value between two values
float clamp(float val, float min, float max) {
  if (val > max) return max;
  if (val < min) return min;
  return val;
}

// wraps a value between two values
float wrap(int val, int min, int max) {
  return min + ((val - min) % (max - min));
}

// calculates RPM based on degrees per interval (ms)
float calcRpm(float error, int interval) {
  return (error * 166.67) / interval;
}
