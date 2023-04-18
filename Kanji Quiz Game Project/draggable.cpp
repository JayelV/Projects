#include"../react.h"

int main() {
  _init();
  int left = 0, top = 0;  // default values at start
  if (_received_event()) {
    left = _get_event_left_drag();
    top = _get_event_top_drag();
    cerr << "dragged to: " << left << ", " << top << endl;
  }
  add_yaml("draggable.yaml", {{"fname", "wood.png"}, {"left", left}, {"top", top}});
  _quit();
}
