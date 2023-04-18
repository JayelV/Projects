/* driver program for lib library
   Example for CS 251;  RAB 5/21 */

#include <iostream>
using namespace std;

#include "lib.h"

/* main() for driver */

int main()
{
  cerr << "*** Driver program for lib library ***" << endl;

  cerr << endl << "1. Test of general-purpose helper function(s)" << endl;
  cerr << "char *str = make_string(\"Hello!\"); cerr << str << endl;" << endl;
  char *str = make_string("Hello!"); cerr << str << endl;
  cerr << "delete [] str;" << endl;
  delete [] str;

  cerr << "max_lines():   ";
  cerr << max_lines() << endl;

  cerr << "get_suffix(kan[1]):   ";
  cerr << get_suffix("kan[1]") << endl;

  return 0;
}
