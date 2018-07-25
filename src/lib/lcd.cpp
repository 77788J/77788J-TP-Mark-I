#include "lib/lcd.h"

// default initializer
Lcd :: Lcd() {}

// actual initializer
void Lcd :: init(FILE *port_) {

  // set port variable
  port = port_;

  // init the physical LCD
  lcdInit(port);
  lcdClear(port);
  lcdSetBacklight(port, true);
}

// gets the text currently displayed on the specified line
const char * Lcd :: getText(int line_) {
  switch (line_) {
    case (0): return text_top; break; // line 1
    case (1): return text_bottom; break; // line 2
    default: return ""; break; // returns a blank string if line_ is not 1 or 2
  }
}

// sets the text on the specified line
void Lcd :: setText(int line_, const char *text_) {

  // update varaible
  text_top = text_;

  // update physical LCD
  lcdSetText(port, line_ + 1, text_); // lcdSetText takes 1 or 2, so line_ (0 or 1) must be translated into that range
}

void Lcd :: updateButtons() {

  // save raw button data
  int btns_raw = lcdReadButtons(port); // raw integer containing 3 bits, one for each button
  int btn_l_raw = (btns_raw >> 0) & 1; // gets first bit
  int btn_m_raw = (btns_raw >> 1) & 1; // gets second bit
  int btn_r_raw = (btns_raw >> 2) & 1; // gets third bit

  // old code that does the same thing as above but in a less cool way
  // bool btn_l_raw = (b == 4 || b == 5 || b == 6 || b == 7); // first button?
  // bool btn_m_raw = (b == 2 || b == 3 || b == 6 || b == 7); // second button?
  // bool btn_r_raw = (b == 1 || b == 3 || b == 5 || b == 7); //third button?

  // determine new button presses
  btn_l_new = (btn_l_raw && !btn_l) - (!btn_l_raw && btn_l);
  btn_m_new = (btn_m_raw && !btn_m) - (!btn_m_raw && btn_m);
  btn_r_new = (btn_r_raw && !btn_r) - (!btn_r_raw && btn_r);

  // update public raw button pressed
  btn_l = btn_l_raw;
  btn_m = btn_m_raw;
  btn_r = btn_r_raw;
}
