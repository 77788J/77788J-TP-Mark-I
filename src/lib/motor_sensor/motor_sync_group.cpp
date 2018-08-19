#include "lib/motor_sensor/motor_sync_group.h"
#include "lib/motor_sensor/motor.h"

// initializer
MotorSyncGroup :: MotorSyncGroup(bool _enabled, int *_motors, int _motor_count) {
  enabled = _enabled;
  motors = _motors;
  motor_count = motor_count;
}

// get mean position
float MotorSyncGroup :: getMean() {
  return mean_position;
}

// recalculate the mean motor position
void MotorSyncGroup :: updateData() {

  // get sum of motor positions
  float sum = 0;
  for (int i = 0; i < all_motors_count; i++) {
    for (int j = 0; j < motor_count; j++) {
      if (all_motors[i].id == *(motors + j)) sum += all_motors[i].getPosition();
    }
  }

  // update mean
  mean_position = sum/motor_count;
}