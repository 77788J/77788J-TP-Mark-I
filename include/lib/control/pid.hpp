#ifndef PID_H_
#define PID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.hpp>

class Pid {

public:

  // tuning parameters
  float kp;
  float ki;
  float kd;

  // anti-windup velocity threshold (0 for no anti-windup)
  float anti_windup_threshold;

  // reset integral on target change?
  bool integral_reset;

  // get the most recent calculation
  float get();

  // initializer/resetter
  void init(float _target, float _kp, float _ki, float _kd);

  // update the calculation (leave vel and accel null to use internal calculations)
  float update(float current, float given_vel, float time_delta);

  // set the target
  void setTarget(float t);

  // reset the integral to 0
  void resetIntegral();

private:

  // current target
  float target;

  // current integral calculation
  float integral;

  // most recent calculation
  float result;

  // previous position
  float prev_pos;

};

#ifdef __cplusplus
}
#endif

#endif
