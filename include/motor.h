#ifndef MOTOR_H_
#define MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sensor.h>
#include <motor_sync_group.h>

// public array of all motors
Motor all_motors[12];
int total_motor_count;

// function to initialize motor and add to array
// USE THIS TO INITIALIZE MOTORS
// DO NOT CALL Motor(...)
// IT WILL BREAK STUFF
void motorInit(int *ports, MotorSyncGroup *sync_group, Sensor sensor);

// different control modes a motor may be in
// > power: raw power control with optional slewing
// > position: position control
// > velocity: velocity control
// > posvel: velocity control via position control
//    > goes to where it should be if it's travelling at a specified velocity, doesn't directly maintain velocity
//    > not always correct velocity, but speeds up if it falls behind
enum MotorMode {power, position, velocity, posvel};

// 'smart' Motor class
// one Motor obj can be associated with multiple physical motors
// > make a new object for each group of linked motors
// > e.g. each side of a chassis should get its own object, but not each individual motor
// includes velocity and position control/feedback
// > must be associated with a Sensor object for this to work
// > otherwise only raw power functions work
class Motor {

public:

  // array of all ports associated with one Motor obj
  int ports[12];

  // mode of motor
  MotorMode mode;

  // motor sync group
  // > all motors in a sync group attempt to stay in sync
  // > useful for things like drivestraight
  MotorSyncGroup *sync_group;

  // slew rate for motor power (max power change per second, 0 for no slewing)
  float slew_rate;

  // initializer
  // DO NOT CALL THIS
  // CALL motorInit(...)
  // USING THIS WILL BREAK STUFF
  Motor(int _ports[12], MotorSyncGroup *_sync_group, Sensor *_sensor);

  // update motor statistics (velocity, position, etc)
  void updateStats();

  // update physical motor
  void updatePhysical();

  // get motor data
  float getRawPower();
  float getTargetPower();
  float getPosition();
  float getTargetPosition();
  float getVelocity();
  float getTargetVelocity();

  // sets motor power
  void setPower(float pow, bool update_mode);

  // sets motor position
  void setPosition(float pos, bool update_mode);

  // sets motor velocity
  void setVelocity(float vel, bool update_mode);

  // sets motor velocity via position
  void setPosVel(float pv, bool update_mode);

private:

  // index of this motor in motors array
  int id;

  // sensor associated with this motor
  Sensor *sensor;

  // raw power of motor
  int raw_power;

  // target power of motor
  int target_power;

  // position history of motor (degrees)
  float position[SENSOR_HISTORY];

  // target position of motor
  float target_position;

  // velocity of motor (RPM)
  float velocity;

  // target velocity of motor
  float target_velocity;

};

#ifdef __cplusplus
}
#endif

#endif