#ifndef MOTOR_H_
#define MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <lib/motor_sensor/sensor.h>
#include <lib/motor_sensor/motor_sync_group.h>
#include <lib/control/pid.h>

// max amount of motor objects
#define MAX_MOTOR_COUNT 10

// default truespeed array
// custom ones may be used as well
extern int default_true_speed[101];

// function to initialize motor and add to array
// USE THIS TO INITIALIZE MOTORS
// DO NOT CALL Motor(...)
// IT WILL BREAK STUFF
int motorInit(int *ports, MotorSyncGroup *sync_group, Sensor *sensor);

// different control modes a motor may be in
// > power: raw power control with optional slewing
// > position: position control
// > velocity: velocity control
// > posvel: velocity control via position control
//    > goes to where it should be if it's travelling at a specified velocity, doesn't directly maintain velocity
//    > not always correct velocity, but speeds up if it falls behind
enum MotorMode {mode_power, mode_position, mode_velocity, mode_posvel};

// 'smart' Motor class
// one Motor obj can be associated with multiple physical motors
// > make a new object for each group of linked motors
// > e.g. each side of a chassis should get its own object, but not each individual motor
// includes velocity and position control/feedback
// > must be associated with a Sensor object for this to work
// > otherwise only raw power functions work
class Motor {

public:

  // index of this motor in motors array
  int id;

  // array of all ports associated with one Motor obj
  int ports[MAX_MOTOR_COUNT];

  // truespeed array to use in this motor
  int *truespeed;

  // scalar that approximates velocity from truespeed motor power
  float vel_scalar;

  // velocity control tuning parameter
  float kvel;

  // mode of motor
  MotorMode mode;

  // motor sync group
  // > all motors in a sync group attempt to stay in sync
  // > useful for things like drivestraight
  MotorSyncGroup *sync_group;

  // PID controller
  // > will set default parameters unless manually initialized via '[motor].pid.init(...)'
  Pid pid;

  // motor syncing tuning parameter
  float ksync;

  // slew rate for motor power (max power change per second, 0 for no slewing)
  float slew_rate;

  // initializer
  // DO NOT CALL THIS
  // CALL motorInit(...)
  // USING THIS WILL BREAK STUFF
  void init(int *_ports, MotorSyncGroup *_sync_group, Sensor *_sensor, int _id);

  // update motor statistics (velocity, position, etc)
  void updateStats();

  // update physical motor
  void updatePhysical(int time_delta);

  // get motor data
  float getRawPower();
  float getPercentPower();
  float getTargetPower();
  float getPosition();
  float getTargetPosition();
  float getVelocity();
  float getTargetVelocity();
  float getAcceleration();

  // sets motor power
  void setPower(float pow, bool update_mode);

  // sets motor position
  void setPosition(float pos, bool update_mode);

  // sets motor velocity
  void setVelocity(float vel, bool update_mode);

  // sets motor velocity via position
  void setPosVel(float vel, bool update_mode);

private:

  // sensor associated with this motor
  Sensor *sensor;

  //  time since target set
  int time_elapsed;

  // raw power of motor
  int raw_power;

  // percentage power of motor (approx. linear via truespeed)
  int percent_power;

  // target power of motor
  int target_power;

  // position of motor (degrees)
  float position;

  // target position of motor
  float target_position;

  // velocity of motor (RPM)
  float velocity;

  // target velocity of motor
  float target_velocity;

  // current power offset for velocity control
  float vel_offset;

  // acceleration threshold for velocity control to take effect
  float vel_accel_threshold;

  // time threshold for velocity control to take effect
  float vel_time_threshold;

  // acceleration of motor (RPM/interval)
  float acceleration;
};

// array of all motors in project
extern int all_motors_count;
extern Motor all_motors[MAX_MOTOR_COUNT];

#ifdef __cplusplus
}
#endif

#endif