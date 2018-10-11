#include "main.hpp"
#include "controller.hpp"
#include "subsystems/subsystems.hpp"

void initializeIO() {}

void initialize() {

    // initialize joystick
    joystick.init(1);

    // initialize subsystems
    ball_intake::init();
    cap_manipulator::init();
    catapult::init();
    transmission::init();

    // start all tasks
    startAllTasks();
}
