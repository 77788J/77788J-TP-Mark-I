#include "lib/motor_sensor/motor.h"

// initialize a motor and add it to all_motors array
int motorInitint(int *ports, MotorSyncGroup *sync_group, Sensor *sensor) {
  all_motors[all_motors_count].init(ports, sync_group, sensor, all_motors_count);
  all_motors_count++;
  return all_motors[all_motors_count].id;
}

// initialize a single motor object
void Motor :: init(int *_ports, MotorSyncGroup *_sync_group, Sensor *_sensor, int _id) {
  
  // copy ports list
  for (int i = 0; i < 12; i++) {
    ports[i] = *(_ports + i);
  }

  // save everything else
  sync_group = _sync_group;
  sensor = _sensor;
  id = _id;
}

// update motor statistics (velocity, position, etc)
void Motor :: updateStats() {
  (*sensor).update();
  position = (*sensor).getValue(0);
  velocity = (*sensor).getVelocity();
  acceleration = (*sensor).getAcceleration();
}

// update physical motor(s)
void Motor :: updatePhysical() {
  for (int i = 0; i < 12; i++) {
    if (i != NULL && i > 0) motorSet(ports[i], raw_power);
  }
}

// get motor data
float Motor :: getRawPower() {return raw_power;}
float Motor :: getPercentPower() {return percent_power;}
float Motor :: getTargetPower() {return target_power;}
float Motor :: getPosition() {return position;}
float Motor :: getTargetPosition() {return target_position;}
float Motor :: getVelocity() {return velocity;}
float Motor :: getTargetVelocity() {return target_velocity;}
float Motor :: getAcceleration() {return acceleration;}

// sets motor power
  void Motor :: setPower(float pow, bool update_mode) {
    if (update_mode) mode = mode_power;
    target_power = pow;
  }

  // sets motor position
  void Motor :: setPosition(float pos, bool update_mode) {
    if (update_mode) mode = mode_position;
    target_position = pos;
  }

  // sets motor velocity
  void Motor :: setVelocity(float vel, bool update_mode) {
    if (update_mode) mode = mode_velocity;
    target_velocity = vel;
  }

  // sets motor velocity via position
  void Motor :: setPosVel(float vel, bool update_mode) {
    if (update_mode) mode = mode_posvel;
    target_velocity = vel;
  }