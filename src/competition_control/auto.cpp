#include "main.hpp"
#include "autons.hpp"
#include "subsystems/subsystems.hpp"
#include "controller.hpp"

#define BOTTOM_FLAG false

void autonomous() {
    if (autons::selected) {
        startAllTasks();
        switch (autons::side) {
            case (0): autons::flagSideDefault(autons::color, autons::park);
            case (1): autons::capSideDefault(autons::color, autons::park);
        }
    }
}
