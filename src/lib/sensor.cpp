#include "sensor.h"

// initialize sensor
Sensor :: Sensor(SensorType _type, int _port1, int _port2, bool _reversed, float _extra_data, void (*_customInit)(), float (*_customUpdate)()) {

  // set variables
  type = _type;
  port1 = _port1;
  port2 = _port2;
  reversed = _reversed;
  extra_data = _extra_data;
  customUpdate = _customUpdate;

  // init specific sensors
  switch (type) {
    
    // sonar sensor
    case (sonar): sonar_sensor = ultrasonicInit(port1, port2); break;

    // quadrature encoder
    case (encoder): encoder_sensor = encoderInit(port1, port2, false); break;

    // gyro
    case (gyro): gyro_sensor = gyroInit(port1, extra_data);

    // custom sensor
    case (custom): _customInit();

    // added cause compiler warnings are annoying
    default: break;
  }
}

// returns the sensor value x intervals ago (0 is current)
float Sensor :: getValue(int x) {
  return (x >= 0 && x < SENSOR_HISTORY) ? history[x] : 0;
}

// returns the type of sensor
SensorType Sensor :: getType() {
  return type;
}

// initializes history
  void Sensor :: initHistory(float x) {
    for (int i = 0; i < SENSOR_HISTORY; i++) {
      history[i] = x;
    }
    history_initialized = true;
  }

// adds x to front of history and pushes everything else back (removes oldest value)
void Sensor :: pushValue(float x) {
  for (int i = SENSOR_HISTORY - 1; i > 0; i--) {
    history[i] = history[i - 1];
  }

  history[0] = x;
}

// updates the history database with the latest sensor value
void Sensor :: update() {

  // inits value variable
  float value = 0;

  // different code for different sensors
  switch (type) {

    // standard digital input
    case (digital): {
      value = digitalRead(port1);
      if (reversed) value = 1.f - value; // invert if reversed
    } break;

    // sonar sensor (cm)
    case (sonar): {
      value = ultrasonicGet(sonar_sensor);
      if (reversed) value = SONAR_MAX - value + SONAR_MIN; // invert if reversed
    } break;

    // quadrature encoder (deg)
    case (encoder): {
      value = (float) encoderGet(encoder_sensor) * extra_data;
      if (reversed) value *= -1.f; // reverse if reversed
    } break;

    // IME (deg)
    case (ime): {
      int val; // cause IMEs are stupid and can't be stored in floats
      imeGet(port1, &val);
      value = (float) val / extra_data;
      if (reversed) value *= -1.f; // reverse if reversed;
    } break;

    // potentiometer (deg)
    case (potentiometer): {
      value = (float) analogRead(port1) * (260.f/4095.f) * extra_data;
      if (reversed) value = 260.f - value; // invert if reversed
    } break;

    // gyro (deg)
    case (gyro): {
      value = gyroGet(gyro_sensor);
      if (reversed) value *= -1.f; // reverse if reversed;
    } break;

    // light sensor/line follower
    case (light): {
      value = analogRead(port1);
      if (reversed) value = 4095.f - value; // invert if reversed
    } break;

    // custom sensor
    case (custom): {
      value = customUpdate();
    } break;

    default: print("wtf"); break;
  }

  // push new value to history
  if (history_initialized) pushValue(value);
  else initHistory(value);
}