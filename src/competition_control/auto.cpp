#include "main.hpp"
#include "autons.hpp"
#include "subsystems/subsystems.hpp"
#include "controller.hpp"

#define BOTTOM_FLAG false

void autonomous() {
    // if (autons::selected) {
    //     switch (autons::side) {
    //         case (0): autons::flagSideDefault(autons::color, autons::park);
    //         case (1): autons::capSideDefault(autons::color, autons::park);
    //     }
    // }
    startAllTasks();
    catapult::waitForLoadPos(2000);
    ball_intake::setDirection(1);
    delay(2500);
    catapult::fire();
    ball_intake::setDirection(0);

    if (BOTTOM_FLAG) {
        chassis::moveInches(-48);
        chassis::waitForCompletion(30.f, 3500);
        chassis::moveInches(0.f);
        chassis::control_type == chassis::control_manual;
    }
}
