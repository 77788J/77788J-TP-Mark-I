#ifndef BALL_INTAKE_H_
#define BALL_INTAKE_H_

#include <lib/motor_sensor/sensor.hpp>

namespace ball_intake {

    extern bool in_macro;

    // motor
    extern int motor;

    // line tracker
    extern Sensor ball_identifier;
    extern float no_ball_light_level;
    extern float yes_ball_light_level;

    // is there a ball in the intake?
    extern bool ball_identified;

    // auto-load toggle
    extern bool auto_load;

    // intake direction
    extern int intake_dir;

    // initializer
    void init();

    // control functions
    void setDirection(int dir);
    void load(bool wait_for_load_pos);
    void getOutOfWay();

    // controllers
    void updateDriverControl();
    void update();

}

// #ifdef __cplusplus
// }
// #endif

#endif
