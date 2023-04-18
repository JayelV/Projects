#include <cstring>
#include <sstream>
#include "Quiz.h"
#include "QuizComm.h"
#include "../react.h"
  
const string prompt("> ");

int main() {
  _init();
  if (_just_starting()) {
    Comm out(prompt, "");
    out.put_in_global_mem();
    _rput("QuizClient");
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
    Quiz Quiz1;
    Quiz1.put_in_global_mem(MAX_COMM);
    cerr << "  Note:  Constructed new Quiz, put in global mem" << endl;
    out.message = "success";
    out.put_in_global_mem();
    _rput("QuizClient");

  } else if (in.message == "display") {
    Quiz tmp;
    tmp.get_from_global_mem(MAX_COMM);
    out.message = tmp.display_kstats().c_str();
    out.put_in_global_mem();
    _rput("QuizClient");  

  /*} else if (in.message.find("deposit ") == 0) { // begins with "deposit "
    stringstream ss(in.message);
    string cmd;  // first word of in.message, i.e., "deposit"
    double amt;  // amount to deposit
    ss >> cmd >> amt;
    Account tmp;
    tmp.get_from_global_mem(MAX_COMM);
    tmp.deposit(amt);
    cerr << "  Note:  new balance is " << tmp.get_balance() << endl;
    tmp.put_in_global_mem(MAX_COMM);
    out.message = tmp.get_display_string().c_str();
    out.put_in_global_mem();
    _rput("AccountClient");

  } else if (in.message.find("set_owner ") == 0) { // begins with "set_owner "
    stringstream ss(in.message);
    string cmd, new_owner;
    ss >> cmd >> new_owner;
    Account tmp;
    tmp.get_from_global_mem(MAX_COMM);
    tmp.set_owner(new_owner.c_str());
    cerr << "  Note:  new owner is " << tmp.get_owner() << endl;
    tmp.put_in_global_mem(MAX_COMM);
    out.message = tmp.get_display_string().c_str();
    out.put_in_global_mem();
    _rput("AccountClient");*/

  } else {
    cerr << "  Note:  unrecognized message" << endl;
    out.put_in_global_mem();
    _rput("QuizClient");  
  }
}