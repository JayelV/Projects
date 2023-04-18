#include <cstring>
#include <sstream>
#include "Kanji.h"
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
  
  if (in.message == "quit")
    return 0;  // end of application, since we didn't call _rput()

  else if (in.message == "construct") {
    Kanji kan;
    kan.put_in_global_mem(MAX_COMM);
    cerr << "  Note:  Constructed new Kanji, put in global mem" << endl;
    out.message = "success";
    out.put_in_global_mem();
    _rput("KanjiClient");

  } else if (in.message.find("display_kanji") == 0) {
    stringstream ss(in.message);
    string cmd, C_kanji;
    ss >> cmd >> C_kanji;
    Kanji kan1;
    kan1.get_from_global_mem(MAX_COMM);
    kan1.build_kstats(C_kanji);
    cerr << "  Note: kanji information of  " << kan1.get_character() << endl;
    out.message = kan1.make_kstring().c_str();
    out.put_in_global_mem();
    _rput("KanjiClient");

  } else if (in.message.find("kanji_meaning") == 0) {
    stringstream ss(in.message);
    string cmd, C_kanji;
    ss >> cmd >> C_kanji;
    Kanji kan1;
    kan1.get_from_global_mem(MAX_COMM);
    kan1.build_kstats(C_kanji);
    cerr << "  The meaning of "<< kan1.get_character() << " is " << kan1.get_meaning() << endl;
    out.message = kan1.make_kstring().c_str();
    out.put_in_global_mem();
    _rput("KanjiClient");

  } else if (in.message.find("kanji_onyomi_one") == 0) {
    stringstream ss(in.message);
    string cmd, C_kanji;
    int index;
    ss >> cmd >> C_kanji >> index;
    Kanji kan1;
    kan1.get_from_global_mem(MAX_COMM);
    kan1.build_kstats(C_kanji);
    cerr << "  On'yomi selected of " << kan1.get_character() << " is " << kan1.get_onyomi(index) << endl;
    out.message = kan1.make_kstring().c_str();
    out.put_in_global_mem();
    _rput("KanjiClient");
  } else if (in.message.find("kanji_onyomi") == 0) {
    stringstream ss(in.message);
    string cmd, C_kanji;
    ss >> cmd >> C_kanji;
    Kanji kan1;
    kan1.get_from_global_mem(MAX_COMM);
    kan1.build_kstats(C_kanji);
    cerr << "  On'yomi of " << kan1.get_character() << " is " << kan1.get_onyomi() << endl;
    out.message = kan1.make_kstring().c_str();
    out.put_in_global_mem();
    _rput("KanjiClient");

  } else if (in.message.find("kanji_kunyomi_one") == 0) {
    stringstream ss(in.message);
    string cmd, C_kanji;
    int index;
    ss >> cmd >> C_kanji >> index;
    Kanji kan1;
    kan1.get_from_global_mem(MAX_COMM);
    kan1.build_kstats(C_kanji);
    cerr << "  Kun'yomi selected of " << kan1.get_character() << " is " << kan1.get_kunyomi(index) << endl;
    out.message = kan1.make_kstring().c_str();
    out.put_in_global_mem();
    _rput("KanjiClient");
  } else if (in.message.find("kanji_kunyomi") == 0) {
    stringstream ss(in.message);
    string cmd, C_kanji;
    ss >> cmd >> C_kanji;
    Kanji kan1;
    kan1.get_from_global_mem(MAX_COMM);
    kan1.build_kstats(C_kanji);
    cerr << "  Kun'yomi of " << kan1.get_character() << " is " << kan1.get_kunyomi() << endl;
    out.message = kan1.make_kstring().c_str();
    out.put_in_global_mem();
    _rput("KanjiClient");

  } else {
    cerr << "  Note:  unrecognized message" << endl;
    out.put_in_global_mem();
    _rput("KanjiClient");  
  }
}