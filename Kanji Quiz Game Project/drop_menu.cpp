#include"../react.h"

int main() {
  _init();
  add_yaml("drop_menu.yaml");
  if (_just_starting()) {  // initial setup
    _put_raw(10, "option A");
    _put_raw(20, "option B");
    _put_raw(30, "option C");
    _put_raw(40, "0");
    _put_raw(50, "hello");
  } else if (_received_event()) { // check if the user picked something
    int i = _get_event_item_index();
    string message = "item_index ";
    message += to_string(i);
    _put_raw(50, message.c_str());
  }
  _quit();
}
