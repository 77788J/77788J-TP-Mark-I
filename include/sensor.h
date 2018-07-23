#ifndef SENSOR_H_
#define SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

#define SENSOR_HISTORY 10

// IME ticks/rev
#define IME_TORQUE 627.2f
#define IME_SPEED 392.f
#define IME_TURBO 261.333f

// sonar range
#define SONAR_MIN 3.f
#define SONAR_MAX 300.f

// sensor types
enum SensorType {digital, sonar, encoder, ime, potentiometer, gyro, light, custom};

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
  float extra_data;

  // initialize sensor
  // > leave _customInit and _customUpdate null if not using custom sensor
  // > leave _extra_data null if no extra data is required
  Sensor(SensorType _type, int _port1, int _port2, bool _reversed, float _extra_data, void (*_customInit)(), float (*_customUpdate)());

  // returns the sensor value x intervals ago (0 is current)
  float getValue(int x);

  // returns the type of sensor
  SensorType getType();

  // updates the history database with the latest sensor value
  void update();

private:

  // type of sensor
  SensorType type;

  // sensor objects for special sensors
  Ultrasonic sonar_sensor;
  Encoder encoder_sensor;
  Gyro gyro_sensor;

  // pointer to update function of custom sensor
  float (*customUpdate)();

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