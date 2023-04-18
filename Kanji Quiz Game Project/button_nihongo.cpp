#include"../react.h"
  
int main() {
  _init();

  if (_received_event()) {
    if (_event_id_is("go")) {
      std::cerr << "Go!\n";
    } else if (_event_id_is("stop")) {
      std::cerr << "Stop.\n";
    }
  }
  add_yaml("button2.yaml");

  _quit();
}
