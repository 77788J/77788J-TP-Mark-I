#include "main.hpp"
#include "controller.hpp"
#include "subsystems/subsystems.hpp"
#include "lib/autonomous_picker.hpp"
#include "autons.hpp"
// #include "watchdog.h"

Lcd lcd;


extern "C" {
    void watchdogInit();
}

bool autons::selected = false;
int autons::color = 0;
int autons::side = 0;
int autons::park = 0;

void selectAutonomous() {
    namespace picker = autonomous_picker;

    picker::LcdMenuItem colors[2] = {
        picker::LcdMenuItem(0, "RED", false, 0, NULL),
        picker::LcdMenuItem(1, "BLUE", false, 0, NULL)
    };

    picker::LcdMenuItem sides[2] = {
        picker::LcdMenuItem(0, "FLAG", false, 0, NULL),
        picker::LcdMenuItem(1, "CAP", false, 0, NULL)
    };

    picker::LcdMenuItem will_park[2] = {
        picker::LcdMenuItem(0, "NO", false, 0, NULL),
        picker::LcdMenuItem(1, "YES", false, 0, NULL)
    };

    picker::LcdMenuItem color_picker = picker::LcdMenuItem(0, "COLOR", true, 2, colors);
    picker::LcdMenuItem side_picker = picker::LcdMenuItem(0, "SIDE", true, 2, sides);
    picker::LcdMenuItem park_picker = picker::LcdMenuItem(0, "PARK", true, 2, will_park);

    int selections[3] = {0, 0, 0};
    int current = 0;

    while (current < 3) {
        int p;
        switch (current) {
            case (0): p = picker::loadItem(color_picker, &lcd); break;
            case (1): p = picker::loadItem(side_picker, &lcd); break;
            case (2): p = picker::loadItem(park_picker, &lcd); break;
        }

        if (p == -1 && current > 0) --current;
        else {
            selections[current] = p;
            ++current;
        }
    }

    autons::color = selections[0];
    autons::side = selections[1];
    autons::park = selections[2];
}

void initializeIO() {
    watchdogInit();
}

void initialize() {

    // initialize LCD
    lcd.init(uart1);

    // initialize joystick
    joystick.init(1);

    // turn on all IMEs
    // imeInitializeAll();
    // delay(250);

    // initialize subsystems
    ball_intake::init();
    // cap_manipulator::init();
    catapult::init();
    transmission::init();

    // start all tasks
    startAllTasks();

    // start autonomous selection
    // selectAutonomous();
}
