#include "lib/motor_sensor/motor.hpp"
#include "math.h"
#include "lib/utility.hpp"

// default truespeed array
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

// all motor objects registererd
int all_motors_count = 0;
Motor all_motors[MAX_MOTOR_COUNT];

// initialize a motor and add it to all_motors array
int motorInit(int *ports, MotorSyncGroup *sync_group, Sensor *sensor) {
  all_motors[all_motors_count].init(ports, sync_group, sensor, all_motors_count);
  all_motors_count++;
  return all_motors[all_motors_count - 1].id;
}

// C++ is doing some wierd stuff and not reserving memory like it should, so here's some zero-initializations
// Motor :: Motor() {



// }

// initialize a single motor object
void Motor :: init(int *_ports, MotorSyncGroup *_sync_group, Sensor *_sensor, int _id) {

  // set defaults
  vel_offset = 0.f;
  truespeed = default_true_speed;
  vel_scalar = .8f;
  vel_accel_threshold = 5.f;
  vel_time_threshold = 500;
  kvel = .1f;
  ksync = .1f;
  
  // copy ports list
  for (int i = 0; i < MAX_MOTOR_COUNT; i++) {
    ports[i] = *(_ports + i);
  }

  // save everything else
  sync_group = _sync_group;
  sensor = _sensor;
  id = _id;

  // initialize PID to default settings
  pid.init(0.f, 1.f, 0.f, 1.f);
}

// update motor statistics (velocity, position, etc)
void Motor :: updateStats(int time_delta) {
  (*sensor).update(time_delta);
  position = (*sensor).getValue(0);
  velocity = (*sensor).getVelocity();
  acceleration = (*sensor).getAcceleration();
}

// update physical motor(s)
void Motor :: updatePhysical(int time_delta) {

  // velocity control (if enabled)
  if (mode == mode_velocity) {

    // if motor has stabilized, tweak offset to achieve target RPM
    if (fabs(acceleration) < vel_accel_threshold && time_elapsed >= vel_time_threshold * .01f * fabs(target_velocity - velocity)) vel_offset += (target_velocity - velocity) * kvel;

    // calcute target power that should result in target velocity
    target_power = (target_velocity * vel_scalar) + vel_offset;
  }

  // move posvel target (if enabled)
  if (mode == mode_posvel) {
    target_position += target_velocity * .006f * time_delta;
    pid.integral_reset = false;
    pid.setTarget(target_position);
  }

  // position control (if enabled)
  if (mode == mode_position || mode == mode_posvel) target_power = pid.update((*sensor).getValue(0), (*sensor).getVelocity(), time_delta);

  // make sure target power is within bounds of reality
  percent_power = clamp(percent_power, -100, 100);

  // update percent power to target power and apply slewing if enabled
  if (slew_rate == 0) percent_power = target_power;
  else percent_power += clamp(target_power - percent_power, -slew_rate, slew_rate);

  // sync motor (if enabled)
  if (sync_group) {
    float mean = (*sync_group).getMean();
    target_power += (mean - position) * ksync;
    percent_power += (mean - position) * ksync;
  }

  // make sure target power is within bounds of reality (again)
  percent_power = clamp(percent_power, -100, 100);

  // apply truespeed
  raw_power = *(truespeed + abs(percent_power)) * sign(percent_power);
    // printf("%d\n", percent_power);

  // loop through and set all physical motors
  for (int i = 0; i < MAX_MOTOR_COUNT; i++) {
    if (ports[i] && ports[i] > 0) motorSet(ports[i], raw_power);
  }

  time_elapsed += time_delta;
}

// get motor data
float Motor :: getRawPower() {return (float) raw_power;}
float Motor :: getPercentPower() {return (float) percent_power;}
float Motor :: getTargetPower() {return (float) target_power;}
float Motor :: getPosition() {return position;}
float Motor :: getTargetPosition() {return target_position;}
float Motor :: getVelocity() {return velocity;}
float Motor :: getTargetVelocity() {return target_velocity;}
float Motor :: getAcceleration() {return acceleration;}

// sets motor power
  void Motor :: setPower(float p, bool update_mode) {
    if (update_mode) mode = mode_power;
    target_power = p;
  }

  // sets motor position
  void Motor :: setPosition(float pos, bool update_mode) {
    if (update_mode) mode = mode_position;
    target_position = pos;
    pid.setTarget(target_position);
  }

  // sets motor velocity
  void Motor :: setVelocity(float vel, bool update_mode) {
    if (update_mode) mode = mode_velocity;
    if (fabs(target_velocity - vel) >= 3.5f) {
      vel_offset = 0.f;
      time_elapsed = 0;
    }
    target_velocity = vel;
  }

  // sets motor velocity via position
  void Motor :: setPosVel(float vel, bool update_mode) {
    if (update_mode) mode = mode_posvel;
    target_position = (*sensor).getValue(0);
    target_velocity = vel;
  }