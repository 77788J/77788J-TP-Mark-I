#ifndef MOTION_PROFILE_H_
#define MOTION_PROFILE_H_

#ifdef __cplusplus
extern "C" {
#endif

// point on motion profile
typedef struct MotionProfilePoint {
  float pos;
  float vel;
  float accel;
} MotionProfilePoint;

class MotionProfile {

public:

  // tuning paramaters
  float kv; // velocity scalar to convert motor power to velocity
  float ka; // acceleration scalar
  float kp; // proportional
  float kd; // derivative (probably really small, often unecessary)

  // initialize
  void init(float _kv, float _ka, float _kp, float _kd);

  // start
  void followProfile(MotionProfilePoint *_profile, MotionProfilePoint _current, int _length, int _interval, int _time);

  // update
  float update(float _current_pos, float _current_vel, float _current_accel, int _time);

private:

  // pointer to array that should contain profile data
  MotionProfilePoint *profile;
  int profile_length;

  // interval between profile samples
  int sample_interval;

  // time when profile following began
  int start_time;

  // most recent result
  float result;

  // current data
  MotionProfilePoint current;

};

#ifdef __cplusplus
}
#endif

#endif
