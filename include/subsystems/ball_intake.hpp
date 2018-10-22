#ifndef BALL_INTAKE_H_
#define BALL_INTAKE_H_

#include <lib/motor_sensor/sensor.hpp>

namespace ball_intake {

    extern bool in_macro;

    // motor
    extern int motor;

    // intake direction
    extern int intake_dir;

    // initializer
    void init();

    // control functions
    void setDirection(int dir);

    // controllers
    void updateDriverControl();
    void update();

}

// #ifdef __cplusplus
// }
// #endif

#endif
