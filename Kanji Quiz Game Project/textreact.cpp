#include"../react.h"

int main() {
  _init();

  add_yaml("textreact.yaml");
  _put_raw(0, ".....Hello World");

  _quit();
}
