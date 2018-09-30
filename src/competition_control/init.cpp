#include "main.hpp"
#include "controller.hpp"
#include "subsystems/subsystems.hpp"

void initializeIO() {}

void initialize() {

    // initialize joystick
    joystick.init(1);

    // initialize subsystems
    ball_intake::init();
    catapult::init();

    // start all tasks
    startAllTasks();
}
