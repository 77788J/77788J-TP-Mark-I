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

	all_motors[motL].setPower(j.analogLV, true);
	all_motors[motR].setPower(j.analogRV, true);

	for (int i = 0; i < all_motors_count; i++) {
		all_motors[i].updatePhysical(20);
	}
}

void operatorControl() {

	j.init(1);
	Sensor encLeft(encoder, 3, 4, false, 3.f/7.f, NULL, NULL);
	Sensor encRight(encoder, 1, 2, false, 3.f/7.f, NULL, NULL);
	int portsL[MAX_MOTOR_COUNT] = {10};
	int portsR[MAX_MOTOR_COUNT] = {1};
	motL = motorInit(portsL, NULL, &encLeft);
	motR = motorInit(portsR, NULL, &encRight);

	all_motors[motL].slew_rate = 8;
	all_motors[motR].slew_rate = 8;

	taskRunLoop(control, 20);

	while (true) {

		// printf("left: %f\tright: %f\n", encLeft.getValue(0), encRight.getValue(0));
		printf("pos: %f\tvel: %f\taccel: %f\n", all_motors[motL].getPosition(), all_motors[motL].getVelocity(), all_motors[motL].getAcceleration());
		printf("pos: %f\tvel: %f\taccel: %f\n\n", all_motors[motR].getPosition(), all_motors[motR].getVelocity(), all_motors[motR].getAcceleration());

		// printf("left: %f\tright: %f\n\n", all_motors[motL].getTargetPower(), all_motors[motR].getTargetPower());

		delay(250);
	}
}
