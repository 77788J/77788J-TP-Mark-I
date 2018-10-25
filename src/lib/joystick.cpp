#include "lib/joystick.hpp"
#include "math.h"

// default initializer
Joystick :: Joystick() {
  deadbandLH = 10;
  deadbandLV = 10;
  deadbandRH = 10;
  deadbandRV = 10;
}

// "factory" that inits a Joystick
void Joystick :: init(int joystick_) {
  j = joystick_;
  updated = 0;
}

// updates the stored variables
void Joystick :: update() {

  // save raw joystick button data
  bool raw_5U = joystickGetDigital(j, 5, JOY_UP);
  bool raw_5D = joystickGetDigital(j, 5, JOY_DOWN);
  bool raw_6U = joystickGetDigital(j, 6, JOY_UP);
  bool raw_6D = joystickGetDigital(j, 6, JOY_DOWN);
  bool raw_7U = joystickGetDigital(j, 7, JOY_UP);
  bool raw_7D = joystickGetDigital(j, 7, JOY_DOWN);
  bool raw_7L = joystickGetDigital(j, 7, JOY_LEFT);
  bool raw_7R = joystickGetDigital(j, 7, JOY_RIGHT);
  bool raw_8U = joystickGetDigital(j, 8, JOY_UP);
  bool raw_8D = joystickGetDigital(j, 8, JOY_DOWN);
  bool raw_8L = joystickGetDigital(j, 8, JOY_LEFT);
  bool raw_8R = joystickGetDigital(j, 8, JOY_RIGHT);

  // determine new button presses
  btn5U_new = (raw_5U && !btn5U) - (!raw_5U && btn5U);
  btn5D_new = (raw_5D && !btn5D) - (!raw_5D && btn5D);
  btn6U_new = (raw_6U && !btn6U) - (!raw_6U && btn6U);
  btn6D_new = (raw_6D && !btn6D) - (!raw_6D && btn6D);
  btn7U_new = (raw_7U && !btn7U) - (!raw_7U && btn7U);
  btn7D_new = (raw_7D && !btn7D) - (!raw_7D && btn7D);
  btn7L_new = (raw_7L && !btn7L) - (!raw_7L && btn7L);
  btn7R_new = (raw_7R && !btn7R) - (!raw_7R && btn7R);
  btn8U_new = (raw_8U && !btn8U) - (!raw_8U && btn8U);
  btn8D_new = (raw_8D && !btn8D) - (!raw_8D && btn8D);
  btn8L_new = (raw_8L && !btn8L) - (!raw_8L && btn8L);
  btn8R_new = (raw_8R && !btn8R) - (!raw_8R && btn8R);

  // update button hold times
  int btn5U_hold_time = (raw_5U && !btn5U_new) ? btn5U_hold_time + millis() - updated : 0;
  int btn5D_hold_time = (raw_5D && !btn5D_new) ? btn5D_hold_time + millis() - updated : 0;
  int btn6U_hold_time = (raw_6U && !btn6U_new) ? btn6U_hold_time + millis() - updated : 0;
  int btn6D_hold_time = (raw_6D && !btn6D_new) ? btn6D_hold_time + millis() - updated : 0;
  int btn7U_hold_time = (raw_7U && !btn7U_new) ? btn7U_hold_time + millis() - updated : 0;
  int btn7D_hold_time = (raw_7D && !btn7D_new) ? btn7D_hold_time + millis() - updated : 0;
  int btn7L_hold_time = (raw_7L && !btn7L_new) ? btn7L_hold_time + millis() - updated : 0;
  int btn7R_hold_time = (raw_7R && !btn7R_new) ? btn7R_hold_time + millis() - updated : 0;
  int btn8U_hold_time = (raw_8U && !btn8U_new) ? btn8U_hold_time + millis() - updated : 0;
  int btn8D_hold_time = (raw_8D && !btn8D_new) ? btn8D_hold_time + millis() - updated : 0;
  int btn8L_hold_time = (raw_8L && !btn8L_new) ? btn8L_hold_time + millis() - updated : 0;
  int btn8R_hold_time = (raw_8R && !btn8R_new) ? btn8R_hold_time + millis() - updated : 0;

  // update public raw button presses
  btn5U = raw_5U;
  btn5D = raw_5D;
  btn6U = raw_6U;
  btn6D = raw_6D;
  btn7U = raw_7U;
  btn7D = raw_7D;
  btn7L = raw_7L;
  btn7R = raw_7R;
  btn8U = raw_8U;
  btn8D = raw_8D;
  btn8L = raw_8L;
  btn8R = raw_8R;

  // update analog sticks (range of -100:100)
  analogRH = (float) joystickGetAnalog(j, 1) * 0.787401575f;
  if (fabs(analogRH) <= deadbandRH) analogRH = 0.f;
  analogRV = (float) joystickGetAnalog(j, 2) * 0.787401575f;
  if (fabs(analogRV) <= deadbandRV) analogRV = 0.f;
  analogLV = (float) joystickGetAnalog(j, 3) * 0.787401575f;
  if (fabs(analogLV) <= deadbandLV) analogLV = 0.f;
  analogLH = (float) joystickGetAnalog(j, 4) * 0.787401575f;
  if (fabs(analogLH) <= deadbandLH) analogLH = 0.f;

  // update time when last updated
  updated = millis();
}
