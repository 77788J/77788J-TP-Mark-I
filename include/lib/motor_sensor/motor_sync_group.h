#ifndef MOTOR_SYNC_H_
#define MOTOR_SYNC_H_

#ifdef __cplusplus
extern "C" {
#endif

// group of motors to sync
// like drivestraight
class MotorSyncGroup {

public:

  // enable or disable group
  bool enabled;

  // pointer to array of motors in this group
  int *motors;

  // amount of motors in group
  int motor_count;

  // initializer
  MotorSyncGroup(bool _enabled, int *_motors, int _motor_count);

  // recalculate the mean motor position
  void updateData();

private:

  // mean motor position
  float mean_position;

};

#ifdef __cplusplus
}
#endif

#endif