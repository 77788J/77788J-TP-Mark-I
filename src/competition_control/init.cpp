#include "main.hpp"
#include "controller.hpp"

void initializeIO() {



}

void initialize() {

    // initialize joystick
    joystick.init(1);

    // start all tasks
    startAllTasks();
}
