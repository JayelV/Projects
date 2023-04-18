#include"../react.h"

int link_text_index = 7;

int main() {
  _init();

  add_yaml("link.yaml", {{"index", link_text_index}});
  _put_raw(link_text_index, "homepage");

  _quit();
}
