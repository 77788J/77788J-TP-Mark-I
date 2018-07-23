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
enum SensorType {digital, sonar, encoder, ime, potentiometer, gyro, light};

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
  Sensor(SensorType _type, int _port1, int _port2, bool _reversed, float _extra_data1);

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