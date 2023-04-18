#ifndef Comm_h_
#define Comm_h_

/* code shared between client and server */

#include <sstream>
#include <iostream>
#include "../react.h"
#define MAX_COMM 1000  // maximum len for Comm object at _global_mem offset 0

using namespace std;

struct Comm {  /* represents a communication between client and server */
  string prefix;
  string message;
  string *mwords;  /* array of words in message */
  int mw_count;  /* length of mwords[] */

  Comm(string p, string m) { 
    prefix = p;
    message = m;
  }

  Comm() { // default constructor retrieves state vars from _global_mem
    prefix = _global_mem; 
    message = _global_mem + prefix.length()+1;
  }

  void put_in_global_mem() {
    _put_raw(0, prefix.c_str());
    _put_raw(prefix.length()+1, message.c_str());
  }

  void display() {
    cerr << "[" << prefix << "]" << message << endl;
  }

};

#endif  // _Comm_h_
