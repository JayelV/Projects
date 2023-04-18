#include"../react.h"

const int text_index_1 = 20, text_index_2 = 10;
const int counter_index = 5;

void handle_button(int i) {
  int len = length_of(text_index_1);
  _global_mem[text_index_1 + len]  = 'A' + i;
  _global_mem[text_index_1 + len + 1]  = 0;
}

int main() {
  _init(true);
  // _init();

  int n = 0;
  if (_just_starting()) {
    _put_raw(text_index_1, ">");
    _put_int(counter_index, n);
  } else if (_received_event()) {
    n = _get_int(counter_index);
    ++n;
    _put_int(counter_index, n);
    cerr << "n is " << n << endl;

    // check if a button was pressed
    for (int i = 0; i < 3; ++i) {
      if (_event_id_is("b", i)) {
        cerr << "button " << i << endl;
        handle_button(i);
      }
    }
  }
  _put_raw(text_index_2, to_string(n).c_str());
  add_yaml("texts.yaml", {{"index_1", text_index_1}, {"index_2", text_index_2}});
  for (int i = 0; i < 3; ++i) 
    add_yaml("button.yaml", {{"id", i}, {"x", 10 + 110*i}});

// quit("none");
// quit("yaml");
// quit("mem");
  _quit();
}
