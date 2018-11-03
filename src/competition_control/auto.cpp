#include "main.hpp"
#include "autons.hpp"
#include "subsystems/subsystems.hpp"
#include "controller.hpp"

#define FLAG false

void flagOnly() {
    while (!catapult::limit_switch.getValue(0)) delay(5);
    ball_intake::setDirection(1);
    delay(1000);
    ball_intake::setDirection(0);
    catapult::fire();
}

void autonomous() {
    startAllTasks();
    autons::flagSideDefault(1, true);
}
