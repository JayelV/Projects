#include <cstring>
#include <sstream>
#include "Chapter.h"
#include "Comm.h"
#include "../react.h"

const string prompt("> ");

int main() {
    _init();
    if (_just_starting()) {
        Comm out(prompt, "");
        out.put_in_global_mem();
        _rput("ChapterClient");
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
        Kanji kan1;
        kan1.put_in_global_mem(MAX_COMM);
        cerr << "  Note:  Constructed new Chapter, put in global mem" << endl;
        out.message = "success";
        out.put_in_global_mem();
        _rput("ChapterClient");

    } else if (in.message == "display") {
        Chapter tmp;
        tmp.get_from_global_mem(MAX_COMM);
        out.message = tmp.make_chstring().c_str();
        out.put_in_global_mem();
        _rput("AccountClient");  

    } else if (in.message.find("build_chapter") == 0 ) {
        stringstream ss(in.message);
        string cmd;
        int ch;
        ss >> cmd >> ch;
        Chapter tmp(ch);
        tmp.get_from_global_mem(MAX_COMM);
        cerr << "Chapter " << ch << ": " << '\n' << tmp.make_chstring() << endl;
        tmp.put_in_global_mem(MAX_COMM);
        out.message = tmp.make_chapterline().c_str();
        out.put_in_global_mem();
        _rput("ChapterClient");
    
    } else {
    cerr << "  Note:  unrecognized message" << endl;
    out.put_in_global_mem();
    _rput("ChapterClient");  
    }
}