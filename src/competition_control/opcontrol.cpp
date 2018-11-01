#include "main.hpp"
#include "lib/motor_sensor/sensor.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "lib/joystick.hpp"
#include "controller.hpp"
#include "macros.hpp"

void operatorControl() {
	startAllTasks();
    macros::init();
	while (true) {
		delay(20);
	}
}
