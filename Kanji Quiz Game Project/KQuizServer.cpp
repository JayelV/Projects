#include <cstring>
#include <sstream>
#include "Kanji.h"
#include "Chapter.h"
#include "KQuiz.h"
#include "Comm.h"
#include "../react.h"
  
const string prompt("> ");

int main() {
  _init();
  if (_just_starting()) {
    Comm out(prompt, "");
    out.put_in_global_mem();
    _rput("KanjiClient");
    return 0;
  }

  /* not just starting */
  Comm in; // retrieve Comm values
  // in.display();  // debugging
  Comm out(prompt, ""); // start outgoing Comm
  cerr << "Received from " << in.prefix << ": " << in.message << endl;
  reset_txt("KanjiQuiz.txt");

  if (in.message == "quit")
    return 0;  // end of application, since we didn't call _rput()