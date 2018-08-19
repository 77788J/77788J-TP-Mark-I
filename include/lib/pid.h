#ifndef PID_H_
#define PID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

class Pid {

public:

  // tuning parameters
  float kp;
  float ki;
  float kd;

  // reset integral on target change?
  bool integral_reset;

  // reset derivitive on target change?
  bool derivitive_reset;

};

#ifdef __cplusplus
}
#endif

#endif
