#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.hpp>

class Joystick {

public:

  // time when last updated
  int updated;

  // raw joystick button values
  bool btn5U;
  bool btn5D;
  bool btn6U;
  bool btn6D;
  bool btn7U;
  bool btn7D;
  bool btn7L;
  bool btn7R;
  bool btn8U;
  bool btn8D;
  bool btn8L;
  bool btn8R;

  // registers NEW button pressed
  int btn5U_new;
  int btn5D_new;
  int btn6U_new;
  int btn6D_new;
  int btn7U_new;
  int btn7D_new;
  int btn7L_new;
  int btn7R_new;
  int btn8U_new;
  int btn8D_new;
  int btn8L_new;
  int btn8R_new;

  // analog stick values (left/right, horizontal/vertical)
  int analogRH;
  int analogRV;
  int analogLV;
  int analogLH;

  // analog deadbands
  int deadbandRH;
  int deadbandRV;
  int deadbandLH;
  int deadbandLV;

  // default initializer
  // MAKE SURE TO FULLY INITIALIZE WITH <Joystick>.init()
  Joystick();

  // actually initializes the joystick
  void init(int joystick_);

  // updates the button readings
  void update();

private:

  // whether this refers to a primary or partner joystick
  int j;

};

#ifdef __cplusplus
}
#endif

#endif
