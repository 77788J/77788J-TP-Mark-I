#include "main.hpp"
#include "autons.hpp"
#include "subsystems/subsystems.hpp"
#include "controller.hpp"

void autonomous() {

    startAllTasks();

    // if (autons::selected) {
    //     startAllTasks();
    //     switch (autons::side) {
    //         case (0): autons::flagSideDefault(autons::color, autons::park);
    //         case (1): autons::capSideDefault(autons::color, autons::park);
    //     }
    // }

    autons::flagSideDefault(1, true);
}
