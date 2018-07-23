#ifndef LCD_H_
#define LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

class Lcd {

public:

  // LCD port (uart1 or uart2)
  FILE *port;

  // raw button values
  bool btn_l;
  bool btn_m;
  bool btn_r;

  // updated button values
  int btn_l_new;
  int btn_m_new;
  int btn_r_new;

  // default initializer
  // MAKE SURE TO FULLY INITIALIZE WITH <Lcd>.init()
  Lcd();

  // actually initializes the joystick
  void init(FILE *port_);

  // returns the text on the LCD
  const char *getText(int line_);

  // updates the text on the LCD
  void setText(int line_, const char *text_);

  // updates the button variables
  void updateButtons();

private:

  // text displayed on top and bottom of LCD
  const char *text_top;
  const char *text_bottom;

};

#ifdef __cplusplus
}
#endif

#endif
