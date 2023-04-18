#ifndef _Chapter_H_
#define _Chapter_H_

#include <stdlib.h>


#include "Kanji.h"
#include "lib.h"

#include "../react.h"

#include <iostream>
using namespace std;

class Chapter {

protected:
  int chapter;  // current chapter
  char *title;  // title of the chapter

public:
  Chapter(const char *t) { 
    title = make_string(t);
  }
  Chapter(void) { chapter = 0; title = make_string(""); }
  Chapter(const Chapter &c) { 
    chapter = c.chapter;
    title = make_string(c.title);
  }
  void display(void) { cerr << "Chapter display() called, title=" << title; }
  void shuffle(int *array, size_t n);

  double get_chapter () { return chapter; }
  const char *get_title() { return title; }
  void set_title(const char *t) { delete [] title; title = make_string(t); }


protected: 
  char *make_string(const char *str);

  Kanji **elt;
  int chapter;
  int size;

  int gm_size;
  int ui_offset;
  int ui_size;
  Dict ui_params;

public:
  const char *archivefile = "KanjiArchive.txt"; // the chapter class will take every kanji that has the same chapter number as given from this txt file
  int DEFAULT_SIZE = 16;
  int DEFAULT_SIZE2= 50;
  Chapter(int ch);
  Chapter(void);
  Chapter(const Chapter &c);
  virtual ~Chapter(void) {
    for(int i = 0; i < size; ++i){
      if (elt[i] !=0 ){
        delete elt[i];
      }
    }
    delete [] elt;
  }

  int get_chapter_number() { return chapter; }

  Chapter& operator=(const Chapter &c);
  char *get_character(int n);
  string display_kstats(int n);
  int kanji_in_chapter(const char *k);
  string display_kstats(const char *k);
  string display_kstats(string k);
  string make_chapterline(void);
  
  void display(void);
  void display_all_chapters(void);
  string make_chstring(void);
  Kanji &operator[] (int i);
  void build_chapter(void);

  int find_kanji_line(const char *k);

  void put_in_global_mem(int offset);
  void get_from_global_mem(int offset);


protected:
  void ui_setup(int offset);

};

#endif  // _Chapter_H_