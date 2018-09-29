#include "subsystems/catapult.hpp"

namespace catapult {

    // motor/sensor declarations
    int motors;
    Sensor limit_switch;

    // initialize motors, sensors, etc
    void init() {

        int ports[10] = {4};
        motors = motorInit(ports, NULL, NULL);

    }

    // update controller for driver control
    void updateDriverControl() {

    }

    // update general catapult controller
    void update() {

    }

}