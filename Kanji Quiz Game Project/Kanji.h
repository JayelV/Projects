#ifndef _Kanji_H
#define _Kanji_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include<iterator>
#include<algorithm>
#include<vector>

#include "lib.h"
#include "../react.h"
using namespace std;

class Kanji {
    int chapter;
    char *character;
    char *meaning;
    char *onyomi;
    char *kunyomi;
    
    int kstats_length;
    int gm_size;
    int ui_offset;
    int ui_size;
    Dict ui_params;
    char KanjiTypeCode;
    
public:
    int DEFAULT_SIZE = 50;
    const char *archivefile = "KanjiArchive.txt";

    Kanji(int ch, const char *c, const char *m, const char *on, const char *kun);
    Kanji(char ch);
    Kanji(int line) { build_kstats(line); } // constructor from line in KanjiArchive.txt
    Kanji(const char *k) { build_kstats(k); } // constructor for identifying kanji character by const char *
    Kanji(string k) { build_kstats(k); } // constructor for identifying kanji character by string
    Kanji(void);
    Kanji(const Kanji &kanji);
    virtual ~Kanji(void) { 
        delete [] character;
        delete [] meaning;
        delete [] onyomi;
        delete [] kunyomi; }

    virtual Kanji *clone() { return new Kanji(*this); }
    virtual void display(void) { cerr << make_kstring(); }
    virtual string make_kstring();

    Kanji &operator=(const Kanji &kanji);

    vector<char*> split_readings(const char *reading);

    char *get_character() { return character; }
    char *get_meaning() { return meaning; }
    char *meaning_space();
    char *get_onyomi(int n);
    char *get_onyomi() { return onyomi; }
    char *get_kunyomi(int n);
    char *get_kunyomi() { return kunyomi; }
    int get_chapter() { return chapter; }

    int find_kanji_line();
    int find_kanji_line(const char *k);
    void build_kstats(int line);
    void build_kstats(const char *k);
    void build_kstats(string k);
    void build_all_kstats();

    string make_kstring(int line);
    void display_kstats();

    virtual int put_in_global_mem(int offset);
    virtual int get_from_global_mem(int offset);
    virtual int draw(string id, int offset);  // store UI strings in _global_mem
    virtual char *get_ui_string(string key) {
        return &_global_mem[ui_params[key].as_long()]; }
    virtual void put_ui_string(string key, string str) {
        _put_raw(ui_params[key].as_long(), str.c_str()); }

protected:
  void ui_setup(int offset);

};

#endif