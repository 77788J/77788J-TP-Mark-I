#include "subsystems/ball_intake.hpp"
#include "subsystems/catapult.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "macros.hpp"
#include "controller.hpp"
#include "math.h"

namespace ball_intake {
    
    bool in_macro = false;

    // motor declaration
    int motor;

    // line tracker
    Sensor ball_identifier;
    float no_ball_light_level = 3000.f;
    float yes_ball_light_level = 200.f;

    // is there a ball in the intake?
    bool ball_identified = false;

    // auto-load toggle
    bool auto_load = true;

    // current direction intake is spinning
    int intake_dir = 0;

    // initialize motor and varaibles
    void init() {

        // init motors
        int ports[10] = {1};
        motor = motorInit(ports, NULL, NULL);

        // init ball identifier
        ball_identifier.init(sensor_light, 2, 0, false, 0, NULL, NULL);
    }

    // change the direction in which the intake spins
    void setDirection(int dir) {
        intake_dir = dir;
    }

    // loads catapult
    void load(bool wait_for_load_pos) {
        auto_load = true;
        if (wait_for_load_pos) {
            while (!catapult::is_loaded) delay(5);
        }
    }

    // moves current ball out of way of catapult
    void getOutOfWay() {
        setDirection(-1);
        delay(500);
        setDirection(0);
    }

    // update controller for driver control
    void updateDriverControl() {
        
        // stop macro if in macro and driven
        if (in_macro && (joystick.btn6U_new == 1 || joystick.btn8L_new == 1)) macros::stopMacro();

        auto_load = false;
        if (joystick.btn6U) setDirection(1); // intake override
        else if (joystick.btn8L) setDirection(-1); // outtake override
        else auto_load = true;
    }

    // update general ball intake controller
    void update() {

        // decide if ball is detected
        float v = ball_identifier.getValue(0);
        float prev_identified = ball_identified;
        ball_identified = (fabs(v - yes_ball_light_level) < fabs(v - no_ball_light_level));

        // auto-load if applicable
        if (auto_load) {

            // check if just loaded
            if (!ball_identified && prev_identified) catapult::is_loaded = true;

            // default to on
            setDirection(1);

            // turn on if applicable
            if (ball_identified && (catapult::is_loaded || !catapult::limit_switch.getValue(0))) setDirection(0);
        }

        // set physical motor
        all_motors[motor].setPower(100 * intake_dir, true);
    }
}