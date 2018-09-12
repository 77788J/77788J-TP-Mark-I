#include "main.h"
#include "lib/motor_sensor/sensor.h"
#include "lib/motor_sensor/motor.h"
#include "lib/joystick.h"

int motL;
int motR;
Joystick j;

// motor control
void control() {
	j.update();

	for (int i = 0; i < all_motors_count; i++) {
		all_motors[i].updateStats(20);
	}

	all_motors[motL].setVelocity(j.analogLV * 1.6f, true);
	all_motors[motR].setVelocity(j.analogRV * 1.6f, true);

	// all_motors[motL].setVelocity(50.f, true);
	// all_motors[motR].setVelocity(-50.f, true);

	for (int i = 0; i < all_motors_count; i++) {
		all_motors[i].updatePhysical(20);
	}
}

void operatorControl() {

	delay(2500);

	j.init(1);
	Sensor encLeft(encoder, 3, 4, false, 3.f/7.f, NULL, NULL);
	Sensor encRight(encoder, 1, 2, false, 3.f/7.f, NULL, NULL);
	int portsL[MAX_MOTOR_COUNT] = {10};
	int portsR[MAX_MOTOR_COUNT] = {1};
	motL = motorInit(portsL, NULL, &encLeft);
	motR = motorInit(portsR, NULL, &encRight);

	all_motors[motL].kvel = .035f;
	all_motors[motL].vel_scalar = .8f;
	all_motors[motR].kvel = .035f;
	all_motors[motR].vel_scalar = .8f;

	all_motors[motL].slew_rate = 18;
	all_motors[motR].slew_rate = 18;

	taskRunLoop(control, 20);

	while (true) {

		// printf("left: %f\tright: %f\n", encLeft.getValue(0), encRight.getValue(0));
		printf("pos: %f\tvel: %f\tpow: %f\n", all_motors[motL].getPosition(), all_motors[motL].getVelocity(), all_motors[motL].getTargetPower());
		printf("pos: %f\tvel: %f\tpow: %f\n\n", all_motors[motR].getPosition(), all_motors[motR].getVelocity(), all_motors[motR].getTargetPower());

		// printf("left: %f\tright: %f\n\n", all_motors[motL].getTargetPower(), all_motors[motR].getTargetPower());

		delay(250);
	}
}
