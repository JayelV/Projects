#include"../react.h"

int main() {
  _init();

  add_yaml("boxes.yaml", {{"id", 12}, {"bg", "yellow"}});
  add_yaml("circle.yaml", {{"x", 30}});

  _quit();
}
