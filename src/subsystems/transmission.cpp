#include "subsystems/transmission.hpp"
#include "main.hpp"

#define _USE_MATH_DEFINES
#include "math.h"

namespace transmission {

    // generic motors
    int motor_top_left;
    int motor_btm_left;
    int motor_top_right;
    int motor_btm_right;

    // set priority ratio of chassis/lift
    // basically means that if both are meant to be given full power, 
    // this is the ratio of how power is distributed
    void setPriorityRatio(float chassis_part, float lift_part) {
        float total = chassis_part + lift_part;
        chassis::priority = chassis_part / total;
        lift::priority = lift_part / total;
    }

    // initializer
    void init();

    // controllers
    void updateDriverControl();
    void update(int delta_time);

}