#include <lib/autonomous_picker.hpp>

namespace autonomous_picker {

  #define GO_BACK -1

  // menu item initializer
    LcdMenuItem :: LcdMenuItem(int _id, const char *_title, bool _has_submenu, int _submenu_size, LcdMenuItem *_submenu) {
      id = _id;
      title = _title;
      has_submenu = _has_submenu;
      submenu_size = _submenu_size;
      submenu = _submenu;
    }

  // loads menu item and processes user interaction
  int loadItem(LcdMenuItem item, Lcd *lcd) {

    // if there isn't a submenu, return itself
    if (!item.has_submenu) return item.id;

    // display menu differently based on amount of options
    switch (item.submenu_size) {

      // if it's empty, return itself
      case (0): return item.id; break;

      // if there's only 1 option, return that option
      case (1): return loadItem(*item.submenu, lcd);

      // if there's 2 options, map each button to one option, and one button to back
      case (2): {

        lcdClear(uart1);
        
        // make top row say current item's title
        char top_text[16];
        centerText(item.title, 16, top_text);
        lcd->setText(0, top_text);

        // make bottom row display the options and back ('<')
        char bottom_text[16];
        strcpy(bottom_text, "<");
        char center_option_text[16];
        centerText((*(item.submenu + 0)).title, 8, center_option_text);
        strcat(bottom_text, center_option_text); // first option
        char right_option_text[16];
        centerText((*(item.submenu + 1)).title, 7, right_option_text);
        strcat(bottom_text, right_option_text); // second option
        lcd->setText(1, bottom_text); // update LCD text visibly

        // wait for user interaction
        LcdButton choice = lcd->waitForInteraction(5, 0);

        // return correct selection
        switch (choice) {
          case (lcd_button_left): return GO_BACK; break;
          case (lcd_button_middle): return loadItem(*(item.submenu + 0), lcd); break;
          case (lcd_button_right): return loadItem(*(item.submenu + 1), lcd); break;
          default: return item.id; break;
        }
      }; break;

      // if there's more than 3 options, scroll through all options
      default: {

        lcdClear(uart1);

        // variables
        int current_option = 0; // currently visible option
        LcdButton choice = lcd_button_none; // start with nothing pressed

        // make top row say current item's title
        char top_text[16];
        centerText(item.title, 16, top_text);
        lcd->setText(0, top_text);

        // loop until an option is selected
        while (choice != lcd_button_middle) {

          lcdClear(uart1);

          // make bottom row display the currently visible option and arrows/whitespace for left/right
          if (current_option == -1) lcd->setText(1, "      BACK     >"); // update LCD text to 'BACK' visibly
          else {
            char bottom_text[16];
            strcpy(bottom_text, (current_option > -1) ? "<" : " "); // either show '<' or ' ' depending on if there's an option to the left
            char selected[16];
            centerText((*(item.submenu + current_option)).title, 14, selected);
            strcat(bottom_text, selected); // selected option
            strcat(bottom_text, (current_option < item.submenu_size - 1) ? ">" : " "); // either show '>' or ' ' depending on if there's an option to the right
            lcd->setText(1, bottom_text); // update LCD text visibly
          }

          // wait for button press
          choice = lcd->waitForInteraction(5, 0);

          // scroll if applicable
          if (choice == lcd_button_left && current_option > -1) --current_option;
          if (choice == lcd_button_right && current_option < item.submenu_size - 1) ++current_option;
        }

        // return correct selection
        if (choice == -1) return GO_BACK;
        return loadItem(*(item.submenu + current_option), lcd); break;
      }; break;
    }
  }
}
