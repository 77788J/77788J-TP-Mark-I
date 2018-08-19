#ifndef MOTOR_H_
#define MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <lib/motor_sensor/sensor.h>
#include <lib/motor_sensor/motor_sync_group.h>

// max amount of motor objects
#define MAX_MOTOR_COUNT 10

// default truespeed array
// custom ones may be used as well
int default_true_speed[101] = {
  0,
  0,   0,   0,   0,   0,   0,   0,   0,  17,  17,
  17,  17,  18,  19,  19,  20,  20,  20,  20,  21,
  22,  22,  22,  23,  24,  24,  24,  24,  25,  25,
  26,  26,  27,  27,  28,  28,  28,  28,  29,  29,
  29,  30,  31,  31,  31,  31,  32,  32,  33,  34,
  35,  35,  35,  36,  36,  37,  38,  38,  39,  39,
  40,  41,  41,  42,  43,  44,  45,  45,  46,  47,
  48,  50,  50,  51,  52,  53,  54,  55,  56,  57,
  57,  58,  61,  61,  62,  62,  64,  65,  66,  66,
  68,  69,  69,  69,  70,  85,  90, 100, 100, 100
};

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
  int ports[12];

  // truespeed array to use in this motor
  int *truespeed;

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
  void init(int *_ports, MotorSyncGroup *_sync_group, Sensor *_sensor, int _id);

  // update motor statistics (velocity, position, etc)
  void updateStats();

  // update physical motor
  void updatePhysical();

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

  // raw power of motor
  int raw_power;

  // percentage power of motor (before truespeed is applied)
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

  // acceleration of motor (RPM/interval)
  float acceleration;

};

// array of all motors in project
int all_motors_count = 0;
Motor all_motors[MAX_MOTOR_COUNT];

#ifdef __cplusplus
}
#endif

#endif