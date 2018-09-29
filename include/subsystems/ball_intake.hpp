#ifndef BALL_INTAKE_H_
#define BALL_INTAKE_H_

#include <lib/motor_sensor/sensor.hpp>

namespace ball_intake {

    // motor
    extern int motor;

    // intake direction
    extern int intake_dir;

    // initializer
    void init();

    // controllers
    void updateDriverControl();
    void update();

}

// #ifdef __cplusplus
// }
// #endif

#endif
