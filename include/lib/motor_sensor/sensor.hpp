#ifndef SENSOR_H_
#define SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.hpp>

#define SENSOR_HISTORY 10

// IME ticks/rev
#define IME_TORQUE 627.2f
#define IME_SPEED 392.f
#define IME_TURBO 261.333f

// sonar range
#define SONAR_MIN 3.f
#define SONAR_MAX 300.f

// sonar conversion factors
#define CM_TO_IN_FACTOR 0.3937007874f
#define CM_TO_FT_FACTOR 0.03280839895f

// calculates the acceleration of a value given its history
float calcAccel(float *history, float prev_vel, float prev_accel, int delta_time);

// calculates the valocity of a value given its history
float calcVel(float *history, float prev_vel, int delta_time);

// sensor types
enum SensorType {sensor_digital, sensor_sonar, sensor_encoder, sensor_ime, sensor_potentiometer, sensor_gyro, sensor_light, sensor_custom};

// primary sensor class
// this class is basically a wrapper for all Vex sensors (excluding the accelerometer)
// it also allows you to utilize custom sensors with it, as long as your function return a single float
// > logic for initializing and updating sensor data is provided via function pointers
// > groups of sensors can also be considered custom sensors
// > e.g. a lift has an encoder for accurate, precise height data and a potentiometer to periodically calibrate it
// > as long as you provide the logic, this class treats groups as a single sensor
// > this is important, as this Sensor class is used in my 'smart' motor class for velocity and posititon data
class Sensor {

public:

  // port(s) sensor is plugged into (leave port2 blank if single wire)
  int port1;
  int port2;

  // determines whether or not the value is reversed
  bool reversed;

  // extra data for specific sensor
  // > gear ratio for potentiometer/encoder (2 is speed, 1/2 is torque)
  // > internal motor gear config for ime
  // > scale for gyro
  // > conversion factor for sonar
  float extra_data;

  // sensor objects for special sensors
  Ultrasonic sonar_sensor;
  Encoder encoder_sensor;
  Gyro gyro_sensor;

  // initialize sensor
  // > leave _customInit and _customUpdate null if not using custom sensor
  // > leave _extra_data null if no extra data is required
  void init(SensorType _type, int _port1, int _port2, bool _reversed, float _extra_data, void (*_customInit)(), float (*_customUpdate)());

  // returns the sensor value x intervals ago (0 is current)
  float getValue(int x);

  // returns the current velocity
  float getVelocity();

  // returns the current acceleration
  float getAcceleration();

  // returns the type of sensor
  SensorType getType();

  // updates the history database with the latest sensor value
  void update(int update_delta);

private:

  // type of sensor
  SensorType type;

  // pointer to update function of custom sensor
  float (*customUpdate)();

  // velocity and acceleration of sensor value
  float velocity;
  float acceleration;

  // array of size SENSOR_HISTORY storing the history of sensor values
  float history[SENSOR_HISTORY];

  // stores whether history has been initialized or not
  bool history_initialized;

  // initializes history
  void initHistory(float x);

  // adds x to front of history and pushes everything else back (removes oldest value)
  void pushValue(float x);

};

#ifdef __cplusplus
}
#endif

#endif