#include"../react.h"

int main() {
  _init();

  add_yaml("one_image.yaml", {{"fname", "wood.png"}});

  _quit();
}
