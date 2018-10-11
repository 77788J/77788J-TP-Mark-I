#include "lib/lcd.hpp"

// center text within specific boundaries
void centerText(const char *string, int new_size, char *out) {

  // get length of original string
  float size = strlen(string);

  // store leading padding
  for (int i = 0; i < floor((new_size - size) / 2.f); i++) {
    strcat(out, " ");
  }

  // store actual string
  strcat(out, string);

  // store lagging padding
  for (int i = 0; i < ceil((new_size - size) / 2.f); i++) {
    strcat(out, " ");
  }
}

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

  // update variable
  if (line_ == 0) text_top = text_;
  if (line_ == 1) text_bottom = text_;

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

// waits for a button to be pressed
LcdButton Lcd :: waitForInteraction(int interval, int timeout) {

  // initialize variables
  int elasped_time = 0;

  // wait for buttons
  while (!(btn_l || btn_m || btn_r) || (timeout > 0 && elasped_time > timeout)) {
    delay(interval);
    elasped_time += interval;
    updateButtons();
  }

  LcdButton choice;
  if (btn_l) choice = lcd_button_left;
  else if (btn_m) choice = lcd_button_middle;
  else if (btn_r) choice = lcd_button_right;
  else choice = lcd_button_none;

  while (btn_l || btn_m || btn_r) {
    delay(interval);
    updateButtons();
  }

  // return currently pressed button
  return choice;
}
