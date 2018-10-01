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
    void init() {

        // init motors
        int port_tl[10] = {8};
        int port_bl[10] = {9};
        int port_tr[10] = {2};
        int port_br[10] = {3};
        Sensor ime_tl;
        Sensor ime_bl;
        Sensor ime_tr;
        Sensor ime_br;
        ime_tl.init(sensor_ime, 0, 0, false, IME_SPEED, NULL, NULL);
        ime_bl.init(sensor_ime, 1, 0, false, IME_SPEED, NULL, NULL);
        ime_tr.init(sensor_ime, 2, 0, false, IME_SPEED, NULL, NULL);
        ime_br.init(sensor_ime, 3, 0, false, IME_SPEED, NULL, NULL);
        motor_top_left = motorInit(port_tl, NULL, &ime_tl);
        motor_btm_left = motorInit(port_bl, NULL, &ime_bl);
        motor_top_right = motorInit(port_tr, NULL, &ime_tr);
        motor_btm_right = motorInit(port_br, NULL, &ime_br);
    }

    // update controller for driver control
    void updateDriverControl() {}

    // update general transmission controller
    void update(int delta_time) {

        

    }

}