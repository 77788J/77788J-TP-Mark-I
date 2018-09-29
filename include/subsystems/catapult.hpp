#ifndef CATAPULT_H_
#define CATAPULT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <lib/motor_sensor/motor.hpp>
#include <lib/motor_sensor/sensor.hpp>

namespace catapult {

    // motors/sensors
    extern int motors;
    extern Sensor limit_switch;

    // initialozer
    void init();

    // controllers
    void updateDriverControl();
    void update();

}

#ifdef __cplusplus
}
#endif

#endif
