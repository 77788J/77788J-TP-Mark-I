#include "main.hpp"
#include "controller.hpp"
#include "subsystems/subsystems.hpp"
#include "lib/autonomous_picker.hpp"

Lcd lcd;

void selectAutonomous() {
    namespace picker = autonomous_picker;

    picker::LcdMenuItem red_sides[2] = {
        picker::LcdMenuItem(1, "LEFT", false, NULL, NULL),
        picker::LcdMenuItem(2, "RIGHT", false, NULL, NULL)
    };

    picker::LcdMenuItem blue_sides[2] = {
        picker::LcdMenuItem(3, "LEFT", false, NULL, NULL),
        picker::LcdMenuItem(4, "RIGHT", false, NULL, NULL)
    };

    picker::LcdMenuItem colors[2] = {
        picker::LcdMenuItem(0, "RED", true, 2, red_sides),
        picker::LcdMenuItem(0, "BLUE", true, 2, blue_sides)
    };

    picker::LcdMenuItem programs[3] = {
        picker::LcdMenuItem(5, "STD BALL", false, NULL, NULL),
        picker::LcdMenuItem(6, "STD CAP", false, NULL, NULL),
        picker::LcdMenuItem(7, "KYLE", false, NULL, NULL)
    };

    picker::LcdMenuItem color = picker::LcdMenuItem(0, "COLOR", true, 2, colors);
    picker::LcdMenuItem program = picker::LcdMenuItem(0, "PROGRAM", true, 3, programs);
    int sel_color = picker::loadItem(color, &lcd);
    int sel_prgm = picker::loadItem(program, &lcd);
    printf("POS: %d\tPRGM: %d\n", sel_color, sel_prgm);
}

void initializeIO() {}

void initialize() {

    // initialize LCD
    lcd.init(uart1);

    // initialize joystick
    joystick.init(1);

    // turn on all IMEs
    imeInitializeAll();
    delay(250);

    // initialize subsystems
    ball_intake::init();
    cap_manipulator::init();
    catapult::init();
    transmission::init();

    // start all tasks
    startAllTasks();

    // start autonomous selection
    // selectAutonomous();
}
