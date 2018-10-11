#ifndef LCD_H_
#define LCD_H_

#include <main.hpp>
#include <string.h>
#include <math.h>

// lcd button enum
enum LcdButton {
  lcd_button_left,
  lcd_button_middle,
  lcd_button_right,
  lcd_button_none
};

// center text within specific boundaries
const char *centerText(const char *string, int new_size) {

  // get length of original string
  float size = strlen(string);

  // create string variable
  char result[16];

  // store leading padding
  for (int i = 0; i < floor((new_size - size) / 2.f); i++) {
    strcat(result, " ");
  }

  // store actual string
  strcat(result, string);

  // store lagging padding
  for (int i = 0; i < ceil((new_size - size) / 2.f); i++) {
    strcat(result, " ");
  }

  return result;
}

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

  // updates the text on the LCD (line is 0 or 1)
  void setText(int line_, const char *text_);

  // updates the button variables
  void updateButtons();

  // waits for a button to be pressed
  LcdButton waitForInteraction(int interval, int timeout);

private:

  // text displayed on top and bottom of LCD
  const char *text_top;
  const char *text_bottom;

};

#endif
