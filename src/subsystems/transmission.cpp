#include "subsystems/transmission.hpp"
#include "main.hpp"
#include "lib/utility.hpp"
#include "math.h"

namespace transmission {

    // generic motors
    int motor_top_left;
    int motor_btm_left;
    int motor_top_right;
    int motor_btm_right;

    // sensors
    Sensor ime_tl;
    Sensor ime_bl;
    Sensor ime_tr;
    Sensor ime_br;

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
        ime_tl.init(sensor_ime, 0, 0, false, IME_SPEED, NULL, NULL);
        ime_bl.init(sensor_ime, 1, 0, false, IME_SPEED, NULL, NULL);
        ime_tr.init(sensor_ime, 2, 0, false, IME_SPEED, NULL, NULL);
        ime_br.init(sensor_ime, 3, 0, false, IME_SPEED, NULL, NULL);
        motor_top_left = motorInit(port_tl, NULL, &ime_tl);
        motor_btm_left = motorInit(port_bl, NULL, &ime_bl);
        motor_top_right = motorInit(port_tr, NULL, &ime_tr);
        motor_btm_right = motorInit(port_br, NULL, &ime_br);

        chassis::init();
        lift::init();
    }

    // update controller for driver control
    void updateDriverControl() {}

    // update general transmission controller
    void update(int delta_time) {

        // calculate positive ideal motor power for each subsystem
        float chassis_ideal = max(fabs(chassis::desired_power_left), fabs(chassis::desired_power_right));
        float lift_ideal = fabs(lift::desired_power);

        // calculate max power currently supposed to be exerted
        float total = chassis_ideal + lift_ideal;

        // calculate max possible power for each subsystem
        float chassis_real = min(chassis_ideal, max(chassis::priority * 100, chassis_ideal + 100 - total));
        total = chassis_real + lift_ideal; // recalculate total
        float lift_real = min(lift_ideal, max(lift::priority * 100, lift_ideal + 100 - total));

        // calculate multipliers
        float chassis_scale = chassis_real / chassis_ideal;
        float lift_scale = lift_real / lift_ideal;

        // calculate final subsystem powers
        float chassis_power_left = chassis::desired_power_left * chassis_scale;
        float chassis_power_right = chassis::desired_power_right * chassis_scale;
        float lift_power = lift::desired_power * lift_scale;

        // apply to motors
        all_motors[motor_top_left].setPower(chassis_power_left - lift_power, true);
        all_motors[motor_top_right].setPower(chassis_power_right - lift_power, true);
        all_motors[motor_btm_left].setPower(-chassis_power_left - lift_power, true);
        all_motors[motor_btm_right].setPower(-chassis_power_right - lift_power, true);
        all_motors[chassis::motor_left].setPower(chassis_power_left, true);
        all_motors[chassis::motor_right].setPower(chassis_power_right, true);
    }
}