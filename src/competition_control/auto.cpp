#include "main.hpp"
#include "autons.hpp"
#include "subsystems/subsystems.hpp"
#include "controller.hpp"

#define FLAG false

void autonomous() {

    startAllTasks();

    // if (autons::selected) {
    //     startAllTasks();
    //     switch (autons::side) {
    //         case (0): autons::flagSideDefault(autons::color, autons::park);
    //         case (1): autons::capSideDefault(autons::color, autons::park);
    //     }
    // }

    // autons::flagSideDefault(1, true);

    while (!catapult::limit_switch.getValue(0)) delay(5);
    ball_intake::setDirection(1);
    delay(2000);
    ball_intake::setDirection(0);
    catapult::fire();
    while (catapult::is_shooting) delay(5);

    if (FLAG) {
        chassis::moveInches(9999.f);
        delay(1500);
        chassis::moveDegrees(0.f);
    }
}
