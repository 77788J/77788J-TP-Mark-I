#include "lib/control/motion_profile.hpp"
#include "math.h"

// initializer
void MotionProfile :: init(float _kv, float _ka, float _kp, float _kd) {

  // store variables
  kv = _kv;
  ka = _ka;
  kp = _kp;
  kd = _kd;
}

// start following profile
void MotionProfile :: followProfile(MotionProfilePoint *_profile, MotionProfilePoint _current, int _length, int _interval, int _time) {
  
  // store variables
  profile = _profile;
  profile_length = _length;
  current = _current;
  sample_interval = _interval;

  // store start time
  start_time = _time;
}

// update
float MotionProfile :: update(float _current_pos, float _current_vel, float _current_accel, int _time) {

  // update current
  current.pos = _current_pos;
  current.vel = _current_vel;
  current.accel = _current_accel;

  // calculate current index
  int index = round((float) (_time - start_time) / (float) sample_interval);
  if (index >= profile_length - 1 || index < 0) return 0; // return 0 if index is invalid

  // calculate feedforward
  float feedforward = 
    (*(profile + index + 1)).vel * kv + // velocity
    (*(profile + index + 1)).accel * ka; // acceleration

  // calculate feedback (PD controller)
  float feedback = 
    ((*(profile + index)).pos - current.pos) * kp + // proportional
    ((*(profile + index)).vel - current.vel) * kd; // derivative

  // calculate and return result
  result = feedforward + feedback;
  return result;
}
