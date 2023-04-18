#include <cstring>
#include <sstream>
#include "Chapter.h"
<<<<<<< HEAD
#include <stdlib.h>

Chapter& Chapter::operator=(const Chapter &c) {
  chapter = c.chapter
  delete [] title;
  title = make_string(a.title);
  return *this;  
}

char *Chapter::make_string(const char *str) {
  int len = strlen(str);
  char *tmp = new char[len+1];
  for (int i=0; i<len;  i++)
    tmp[i] = str[i];
  tmp[len] = 0;
  return tmp;
}

void Chapter::shuffle(int *array, size n) {
    if (n > 1){
        size i;
        for (i = 0; i < n - 1; i++) {
          size j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
=======
#include "Kanji.h"
#include "../react.h"

Chapter::Chapter(int ch) : chapter(ch) { // constructor by chapter
  size = DEFAULT_SIZE;
  elt = new Kanji*[size];
  for (int i = 0; i < size; ++i) {
    elt[i] = new Kanji(i + 1);
  }
  build_chapter();
}
Chapter::Chapter(void) { // default constructor
  chapter = 0;
  size = DEFAULT_SIZE;
  elt = new Kanji*[size];
  for (int i = 0; i < size; ++i) {
    elt[i] = 0;
  }
}
Chapter::Chapter(const Chapter &c) { // copy constructor
  chapter = c.chapter;
  size = c.size;
  elt = new Kanji*[size];
  for (int i = 0; i < size; ++i) {
    if (c.elt[i] == 0) {
      elt[i] = 0;
    } else {
      elt[i] = new Kanji[size];
    }
  }
}

Chapter& Chapter::operator=(const Chapter &c) {
  chapter = c.chapter;
  size = c.size;
  delete [] elt;
  elt = new Kanji*[size];
    for (int i = 0; i < size; ++i) {
        if (c.elt[i] == 0){
            elt[i] = 0;
        } else {
            elt[i] = new Kanji[size];
        }
    }
    return *this;
}

char *Chapter::get_character(int n) {
  Kanji findK((DEFAULT_SIZE * chapter) - 15 + n - 1);
  cerr << findK.get_character() << endl;
  
  return findK.get_character();
}

string Chapter::display_kstats(int n) { // displays the stats of all kanji in a given chapter
  return elt[n]->make_kstring((DEFAULT_SIZE * chapter) - 15 + n);
}

void compare_ch_lines(int &return_line, int &line, int &min_ch_line, int &max_ch_line) {
  if (line >= min_ch_line && line <= max_ch_line) {
    return_line = line;
  } else if (line < min_ch_line) {
    return_line = min_ch_line;
  } else if (line > max_ch_line) {
    return_line = max_ch_line;
  }
}

int Chapter::kanji_in_chapter(const char *k) {
  Kanji kline;
  int line = kline.find_kanji_line(k);
  int min_ch_line = (DEFAULT_SIZE * chapter) - 15;
  int max_ch_line = DEFAULT_SIZE * chapter;
  int return_line;
  compare_ch_lines(return_line, line, min_ch_line, max_ch_line);
  return return_line;
}

string Chapter::display_kstats(const char *k) {
  int return_line = kanji_in_chapter(k);
  int chapter_line = return_line - ((DEFAULT_SIZE * chapter) - 15);
  string return_string;
  return_string = elt[chapter_line]->make_kstring(return_line);
  return return_string;
}

string Chapter::display_kstats(string k) {
  char *kan = const_cast<char*>(k.c_str());
  int return_line = kanji_in_chapter(kan);
  int chapter_line = return_line - ((DEFAULT_SIZE * chapter) - 15);
  string return_string;
  return_string = elt[chapter_line]->make_kstring(return_line);
  return return_string;
}

string Chapter::make_chapterline(void) { // creates string version of display()
  stringstream ss;
  ss << "Chapter " << chapter << ":" << '\t';
  int i = 0;
  while (i < DEFAULT_SIZE) {
    ss << elt[i]->get_character() << ' ';
    ++i;
  }
  return string(ss.str());
}

void Chapter::display(void) {
  cerr << "Chapter " << chapter << ": ";
  int i = 0;
  while (i < DEFAULT_SIZE) {
    cerr << elt[i]->get_character() << ' ';
    ++i;
  }
}

void Chapter::display_all_chapters(void) {
  ifstream g(archivefile);
  string kanji_line;
  int current_line = 0;
  int max_chapter;
  while (getline(g, kanji_line)) {
      istringstream g(kanji_line);
      int ch;
      g >> ch;
      max_chapter = ch;
      current_line++;
  }
  int i = 1;
  while (i <= max_chapter) {
    Chapter chap(i);
    chap.display();
    i++;
    cerr << endl;
  }
}

string Chapter::make_chstring(void) { // makes string of all kanji in the chapter with their stats
  string elt_string;
  int i = 0;
  while (i < DEFAULT_SIZE) {
    string c = elt[i]->make_kstring((DEFAULT_SIZE * chapter) - 15 + i);
    elt_string += c;
    ++i;
  }
  return elt_string;
}

Kanji &Chapter::operator[](int i) {
  if (i > size - 1) {
      cerr << "Error, bad index" << endl;
      i = size - 1;
  } else if (i < 0) {
      cerr << "Error, bad index" << endl;
      i = 0;
  } else if (elt[i] == 0) {
      elt[i] = new Kanji;
  }
  return *elt[i];
}

void Chapter::build_chapter(void) { // every index in a Chapter array points to a Kanji class
  ifstream g(archivefile);
  string kanji_line;
  int i = 0;
  while (getline(g, kanji_line)) {
    istringstream g(kanji_line);
    int ch;
    g >> ch;
    if (ch == chapter) {
      elt[i]->build_kstats((DEFAULT_SIZE * chapter) - 15 + i); // dereference to build_kstats in Kanji.cpp which takes the stats from KanjiArchive.txt
      i++; 
    }
  }
}


int Chapter::find_kanji_line(const char *k) { // identifies the number of the line a kanji character is in
  char *character = make_string(k);
  int current_line = 0;
  ifstream g(archivefile);
  string kanji_line;
  while (std::getline(g, kanji_line)) {
    current_line++;
    if (kanji_line.find(character, 1) != string::npos) {
      break;
    }
  }
  return current_line - 1;
}

void Chapter::put_in_global_mem(int offset) {
  string s = make_chstring();
  _put_int(offset + 4, chapter);
  _put_int(offset + 12, size);
  gm_size = 20;
  gm_size += gm_put_string(offset + gm_size, s);
  _put_int(offset, gm_size);
}
void Chapter::get_from_global_mem(int offset) {
  gm_size = _get_int(offset);
  chapter = _get_int(offset + 4);
  size = _get_int(offset + 12);
  string s = make_chstring();
  s = make_string(gm_get_string(offset + 20));
>>>>>>> bd510a183ce850bcf93c340bbdc130c45db5fa05
}