#include "Comm.h"
#include "../react.h"

int main() {
  _init();
  Comm in;
  cerr << in.message << endl;
  cerr << in.prefix;
  Comm out("KQuizClient", "");
  out.put_in_global_mem();
  _user_input(out.prefix.length()+1);
  _rput("KQuizServer");
}