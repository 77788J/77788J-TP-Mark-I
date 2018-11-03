#include "lib/control/pid.hpp"
#include "math.h"

// initializer/resetter
void Pid :: init(float _target, float _kp, float _ki, float _kd) {

  // set give variables
  target = _target;
  kp = _kp;
  ki = _ki;
  kd = _kd;

  // set unspecified variables to defaults
  anti_windup_threshold = 10.f;
  integral_reset = true;
  integral = 0;
  result = 0;
  prev_pos = 0;
}

// gets the most recent calculation
float Pid :: get() {
  return result;
}

// tells whether or not the PID target has been reached within a specific precision
bool Pid :: isAtTarget(float precision) {
  return fabs(target - result) <= precision;
}

// update the calculation (leave vel and accel null to use internal calculations)
float Pid :: update(float current, float given_vel, float time_delta) {

  // calculate error
  float error = target - current;

  // if unspecified, calculate velocity
  float vel = (given_vel || given_vel == 0) ? given_vel : (current - prev_pos) / time_delta;

  // calculate P, and D
  float p = error * kp;
  float d = -vel * kd;

  // integrate if necessary
  if (anti_windup_threshold == 0 || fabs(vel) < anti_windup_threshold) integral += error / time_delta;

  // calculate I
  float i = integral * ki;

  // store and return calculation
  result = p + i + d;
  return result;
}

// set the target
void Pid :: setTarget(float t) {

  // update variable
  target = t;

  // reset integral if necessary
  if (integral_reset) integral = 0;
}

// set the target
void Pid :: resetIntegral() {
  integral = 0;
}
