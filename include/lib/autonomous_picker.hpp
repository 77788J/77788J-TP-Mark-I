#ifndef AUTONOMOUS_PICKER_H_
#define AUTONOMOUS_PICKER_H_

#include <lcd.hpp>

namespace autonomous_picker {

  // item for LCD menu
  class LcdMenuItem {

  public:

    // id of item (to be used as an identifier)
    int id;

    // title of item
    const char *title;

    // determines whether or not this item contains a submenu
    bool has_submenu;

    // amount of items in submenu
    int submenu_size;

    // array of submenu items
    LcdMenuItem *submenu;

    // initializer
    LcdMenuItem(int _id, const char *_title, bool _has_submenu, int _submenu_size, LcdMenuItem *_submenu);
  };

  // loads menu item and processes user interaction
  int loadItem(LcdMenuItem item, Lcd *lcd);

}

#endif
