/* React UI view prototype interface */

#include "../react.h"
#include<string>
#include<sstream>

int main() {
  _init();

  add_yaml("protoKanji.yaml");
  _put_raw(0, "Kanji Oboeru");  // null byte appended automatically
  int offs = 24;  // starting offset in _global_mem for related UI values
  _put_raw(offs, "The meaning of the kanji:");  // null byte appended automatically
  //string kanji = "魚";
  _put_raw(offs+26, "魚");
  _put_raw(offs+48, "outside");
  _put_raw(offs+72, "to meet");
  _put_raw(offs+96, "fish");
  _put_raw(offs+120, "horse");
  _put_raw(offs+144, "exit");

  offs += 168;

  _quit();
}
