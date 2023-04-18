#include <cstring>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <iterator>
#include "Chapter.h"
#include "Kanji.h"
#include "../react.h"
#include "lib.h"
#define OBJ_START 1000

int draw(const char *id, int offs) {
    Dict params;   // parameters for add_yaml() calls
    params = {{"id", id}, {"app_title", offs}};
    add_yaml("KanjiQuizApp.yaml", params);
    _put_raw(offs, "Kanji Oboeru");  // null byte appended automatically
    offs += 24;

    return 24;
}

int main() {
    _init();
    srand(time(0));

    /*if (_just_starting()) {
        Chapter chap(1);
        for (int i = 0; i < 16; i++) {
            chap[i] = *new Kanji(i);
            std::cerr << i << std::endl;
        }

        int offs = 0;
        offs += draw("main", offs);
        for (int i = 0; i < 16; i++) {
            std::string tmp = std::to_string(i);
            char const *num_char = tmp.c_str();
            offs += chap[i].draw(num_char, offs);
        }

        int curr = OBJ_START;
        for (int i = 0; i < 16; i++) {
            curr += chap[i].put_in_global_mem(curr);
        }
    }*/
    if (_just_starting()) {
        Kanji *kan[1];
        //Kanji *kan[3];
        kan[0] = new Kanji(54);
        //kan[1] = new Kanji(12);
        //kan[2] = new Kanji(138);

        int offs = 0;
        offs += draw("main", offs);
        offs += kan[0]->draw("0", offs);
        //offs += kan[1]->draw("1", offs);
        //offs += kan[2]->draw("2", offs);

        int curr = OBJ_START;
        curr += kan[0]->put_in_global_mem(curr);
        //curr += kan[1]->put_in_global_mem(curr);
        //curr += kan[2]->put_in_global_mem(curr);

    } else {
        int curr = OBJ_START;
        Kanji *kan[1];
        //Kanji *kan[3];
        kan[0] = new Kanji;
        curr += kan[0]->get_from_global_mem(curr);
        /*kan[1] = new Kanji;
        curr += kan[1]->get_from_global_mem(curr);
        kan[2] = new Kanji;
        curr += kan[2]->get_from_global_mem(curr);*/

        if (_received_event()) {
            string eid = _get_event_id();
            if (eid.find("choice1_") == 0) {
                int id = stoi(eid);
                string correct_meaning = kan[id]->meaning_space();
                stringstream ss;
                string choice1 = kan[id]->get_ui_string("choice1");
                if (choice1 == correct_meaning) {
                    cerr << "Correct!";
                } else {
                    cerr << "Incorrect.";
                }
                ss.str(std::string());
            } else if (eid.find("choice2_") == 0) {
                int id = stoi(eid);
                string correct_meaning = kan[id]->meaning_space();
                stringstream ss;
                string choice2 = kan[id]->get_ui_string("choice2");
                if (choice2 == correct_meaning) {
                    cerr << "Correct!";
                } else {
                    cerr << "Incorrect.";
                }
                ss.str(std::string());
            } else if (eid.find("choice3_") == 0) {
                int id = stoi(eid);
                string correct_meaning = kan[id]->meaning_space();
                stringstream ss;
                string choice3 = kan[id]->get_ui_string("choice3");
                if (choice3 == correct_meaning) {
                    cerr << "Correct!";
                } else {
                    cerr << "Incorrect.";
                }
                ss.str(std::string());
            } else if (eid.find("choice4_") == 0) {
                int id = stoi(eid);
                string correct_meaning = kan[id]->meaning_space();
                stringstream ss;
                string choice4 = kan[id]->get_ui_string("choice4");
                if (choice4 == correct_meaning) {
                    cerr << "Correct!";
                } else {
                    cerr << "Incorrect.";
                }
                ss.str(std::string());
            }
        }

        int offs = 0;
        offs += draw("main", offs);
        offs += kan[0]->draw("0", offs);
        //offs += kan[1]->draw("0", offs);
        //offs += kan[2]->draw("0", offs);

        curr = OBJ_START;
        curr += kan[0]->put_in_global_mem(curr);
        //curr += kan[1]->put_in_global_mem(curr);
        //curr += kan[2]->put_in_global_mem(curr);
    }
    
    _quit();
}