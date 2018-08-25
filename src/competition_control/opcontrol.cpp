#include "main.h"
#include "lib/motor_sensor/sensor.h"
#include "lib/motor_sensor/motor.h"
#include "lib/joystick.h"

int mot;
Joystick j;

// motor control
void control() {
	for (int i = 0; i < all_motors_count; i++) {
		all_motors[i].updateStats();
	}
	all_motors[mot].setVelocity(j.analogLV, true);
	for (int i = 0; i < all_motors_count; i++) {
		all_motors[i].updatePhysical(20);
	}
}

void operatorControl() {

	j.init(1);
	Sensor pot(potentiometer, 1, 0, false, 0, NULL, NULL);
	Sensor sens(ime, 0, 0, false, IME_TORQUE, NULL, NULL);
	int ports[MAX_MOTOR_COUNT];
	ports[0] = 1;
	ports[1] = 2;
	mot = motorInit(ports, NULL, &sens);

	taskRunLoop(control, 20);

	while (true) {

		printf("pot: %f\time: %f\n", pot.getValue(0), sens.getValue(0));
		printf("pos: %f\tvel: %f\taccel: %f\n\n", all_motors[mot].getPosition(), all_motors[mot].getVelocity(), all_motors[mot].getAcceleration());
		all_motors[mot].setVelocity(j.analogLV, true);
		delay(250);
	}
}
