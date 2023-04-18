/* library functions for Kanji Quiz application - header file */

#include<cstring>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

#include "lib.h"
#include "Chapter.h"
#include "Kanji.h"
#include "../react.h"

char *make_string(const char *str) {
    int len = strlen(str);
    char *tmp = new char[len+1];
    for (int i=0; i<len;  i++)
        tmp[i] = str[i];
    tmp[len] = 0;
    return tmp;
}

/* store a C-style string in _global_mem, and return the number of bytes 
   of _global_mem that are used (including nullbyte) */

int gm_put_string(int offset, const char *str) {
  int len = 4 + strlen(str)+1;
  _put_int(offset, len);
  _put_raw(offset+4, str);
  return len;
}

/* store a std::string object in _global_mem, and return the number of bytes 
   of _global_mem that are used (including nullbyte) */

int gm_put_string(int offset, string &str) {
  return gm_put_string(offset, str.c_str());
}


/* return a C-style string stored in _global_mem */

const char *gm_get_string(int offset) {
  return &_global_mem[offset+4];
}

/* return the number of bytes used by a style string stored in _global_mem */

int gm_get_string_length(int offset) {
  return _get_int(offset);
}


char *convert(const std::string & s) {
   char *pc = new char[s.size()+1];
   std::strcpy(pc, s.c_str());
   return pc; 
}

string get_suffix(const char* str) {
  int len = strlen(str);
  int suffixlen = strlen(str) - 1;
  string suffix;
  suffix += (len - suffixlen);
  return suffix;
}

/* Kanji Quiz specific methods */

int max_lines() {
  ifstream g("KanjiArchive.txt");
  string kanji_line;
  int i = 0;
  while (getline(g, kanji_line)) {
      istringstream g(kanji_line);
      ++i;
  }
  return i;
}

int max_readings(vector<char*> reading_arr) {
  return reading_arr.size();
}

bool does_chapter_exist(int ch) {
  ifstream g("KanjiArchive.txt");
  string kanji_line;
  int chapter;
  while (getline(g, kanji_line)) {
      istringstream g(kanji_line);
      g >> chapter;
  }
  if (ch > 0 && ch <= chapter) {
    return true;
  } else {
    return false;
  }
}

int randomNumber(int start, int end) {
    int ranNumber = start + rand() % (end - start + 1);
    return ranNumber;
}

void differentiate_lines (int &correct_line, int &ranNumber) {
  int max = max_lines();
  if (ranNumber == correct_line) {
    while (ranNumber == correct_line) {
      ranNumber = randomNumber(1, max);
    }
  }
}

void differentiate (int &correct_line, int &ranNumber1, int &ranNumber2, int &ranNumber3) {
  int max = max_lines();
  if (ranNumber1 == correct_line) {
    while (ranNumber1 == correct_line) {
      ranNumber1 = randomNumber(1, max);
    }
  }
  if (ranNumber2 == correct_line) {
    while (ranNumber2 == correct_line) {
      ranNumber2 = randomNumber(1, max);
      if (ranNumber2 == ranNumber1) {
        while (ranNumber2 == ranNumber1) {
          ranNumber2 = randomNumber(1, max);
        }
      }
    }
  }
  if (ranNumber3 == correct_line) {
    while (ranNumber3 == correct_line) {
      ranNumber3 = randomNumber(1, max);
      if (ranNumber3 == ranNumber1) {
        while (ranNumber3 == ranNumber1) {
          ranNumber3 = randomNumber(1, max);
          if (ranNumber3 == ranNumber2) {
            while (ranNumber3 == ranNumber2) {
              ranNumber3 = randomNumber(1, max);
            }
          }
        }
      }
    }
  }
}

void diff2 (char *&correct, char *&r1, char *&r2, char *&r3) {
  const char *annoyance = "none";
  if (r1 == correct) {
    while (r1 == correct) {
      r1 = random_on_reading();
      if (r1 != correct) {
        continue;
      }
    }
  }
  if (r2 == correct) {
    while (r2 == correct) {
      r2 = random_on_reading();
      if (r2 == r1) {
        while (r2 == r1) {
          r2 = random_on_reading();
          if (r2 != correct && r2 != r1 && r2 != annoyance) {
            continue;
          }
        }
      }
    }
  }
  if (r3 == correct) {
    while (r3 == correct) {
      r3 = random_on_reading();
      if (r3 == r1) {
        while (r3 == r1) {
          r3 = random_on_reading();
          if (r3 == r2) {
            while (r3 == r2) {
              r3 = random_on_reading();
              if (r3 != correct && r3 != r1 && r3 != r2 && r3 != annoyance) {
                continue;
              }
            }
          }
        }
      }
    }
  }
}

void display_chapters(int ch){
    Chapter chapQ(ch);
    chapQ.display_all_chapters();
}

void choose_quiz(int ch, int ca) {
  Chapter chapQ(ch);
  string category;
  if (ca == 1) {
      category = "meaning";
      write_meaning_quiz(ch);
  } else if (ca == 2) {
      category == "On'yomi reading";
      write_on_quiz(ch);
  } else if (ca == 3) {
      category == "Kun'yomi reading";
      write_kun_quiz(ch);
  }
}

int random_line() {
  int maxl = max_lines();
  int ranNumber = randomNumber(1, maxl);
  return ranNumber;
}

char *random_on_reading() {
  int maxl = max_lines();
  int ranNumber = randomNumber(1, maxl);
  Kanji kanRan(ranNumber);
  vector<char*> split_r = kanRan.split_readings("onyomi");
  int maxr = max_readings(split_r);
  int ranRead = randomNumber(1, maxr);
  char *ranRn = kanRan.get_onyomi(ranRead);
  char *ranR = make_string(ranRn);
  return ranR;
}

char *random_kun_reading() {
  int maxl = max_lines();
  int ranNumber = randomNumber(1, maxl);
  Kanji kanRan(ranNumber);
  vector<char*> split_r = kanRan.split_readings("kunyomi");
  int maxr = max_readings(split_r);
  int ranRead = randomNumber(1, maxr);
  char *ranRn = kanRan.get_kunyomi(ranRead);
  char *ranR = make_string(ranRn);
  return ranR;
}

int find_kanji_line(const char *k) {
    char *character = make_string(k);
    int current_line = 0;
    ifstream g("KanjiArchive.txt");
    string kanji_line;
    while (std::getline(g, kanji_line)) {
        current_line++;
        if (kanji_line.find(character, 1) != string::npos) {
            break;
        }
    }
    return current_line - 1;
}

char *build_kstats(int line) {
    ifstream g("KanjiArchive.txt");
    string kanji_line;
    int current_line = 0;
    char *kanji_built;
    while (getline(g, kanji_line)) {
        if (current_line == line) {
            istringstream g(kanji_line);
            break;
        }
        current_line++;
    }
    Kanji k(current_line);
    kanji_built = k.get_character();
    return kanji_built;
}

void write_meaning_quiz(int ch) {
    std::ifstream g("KanjiArchive.txt");
    
    int numQuestions = 16;
    int chapter = ch;
    
    std::ofstream f("KanjiQuiz.txt");
    f << numQuestions << std::endl;
    int i = 1;
    while (i <= numQuestions) {
        Kanji kanQuestion((16 * chapter) - 16 + i);

        int correct_line = kanQuestion.find_kanji_line();
        int ranNumber1 = random_line();
        int ranNumber2 = random_line();
        int ranNumber3 = random_line();
        differentiate (correct_line, ranNumber1, ranNumber2, ranNumber3);

        Kanji kanRan1(ranNumber1);
        Kanji kanRan2(ranNumber2);
        Kanji kanRan3(ranNumber3);
        
        f << "What is the meaning of the kanji:  " << kanQuestion.get_character() << std::endl;
        f << "4" << std::endl;

        std::vector<int> ranAnswer = {1, 2, 3, 4};
        unsigned num = chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(ranAnswer.begin(), ranAnswer.end(), default_random_engine(num));

        int j = 1;
        char answer;
        for (int& x: ranAnswer) {
          if (x == 1) {
            f << kanQuestion.meaning_space() << std::endl;
            if (j == 1) {
              answer = '1';
            } else if (j == 2) {
              answer = '2';
            } else if (j == 3) {
              answer = '3';
            } else if (j == 4) {
              answer = '4';
            }
          } else if (x == 2) {
            f << kanRan1.meaning_space() << std::endl;
          } else if (x == 3) {
            f << kanRan2.meaning_space() << std::endl;
          } else if (x == 4) {
            f << kanRan3.meaning_space() << std::endl;
          }
          j++;
        }
        f << answer << std::endl;
        f << 1 << std::endl;
        ++i;

    }
    f.close();
}

void write_on_quiz(int ch) {
    std::ifstream g("KanjiArchive.txt");
    
    int numQuestions = 16;
    int chapter = ch;
    
    std::ofstream f("KanjiQuiz.txt");
    f << numQuestions << std::endl;
    int i = 1;
    while (i <= numQuestions) {
        Kanji kanQuestion((16 * chapter) - 16 + i);
        char *on = kanQuestion.get_onyomi();
        
        f << "What is an On'yomi reading of:  " << kanQuestion.get_character() << std::endl;
        f << "4" << std::endl;

        vector<char*> split_r = kanQuestion.split_readings(on);
        int maxr = max_readings(split_r);
        int ranRead = randomNumber(1, maxr);
        char *correct_read = kanQuestion.get_onyomi(ranRead);
        char *ran_on1 = random_on_reading();
        char *ran_on2 = random_on_reading();
        char *ran_on3 = random_on_reading();
        /*int correct_line = find_kanji_line(correct_read);
        int r1 = find_kanji_line(ran_on1);
        int r2 = find_kanji_line(ran_on2);
        int r3 = find_kanji_line(ran_on3);
        differentiate(correct_line, r1, r2, r3);
        ran_on1 = build_kstats(r1);
        ran_on2 = build_kstats(r2);
        ran_on3 = build_kstats(r3);*/
        diff2(correct_read, ran_on1, ran_on2, ran_on3);
        ran_on1 = make_string(ran_on1);
        ran_on2 = make_string(ran_on2);
        ran_on3 = make_string(ran_on3);

        std::vector<int> ranAnswer = {1, 2, 3, 4};
        unsigned num = chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(ranAnswer.begin(), ranAnswer.end(), default_random_engine(num));

        int j = 1;
        char answer;
        for (int& x: ranAnswer) {

            if (x == 1) {
                f << correct_read << std::endl;
                if (j == 1) {
                    answer = '1';
                } else if (j == 2) {
                    answer = '2';
                } else if (j == 3) {
                    answer = '3';
                } else if (j == 4) {
                    answer = '4';
                }
            } else if (x == 2) {
                f << ran_on1 << std::endl;
            } else if (x == 3) {
                f << ran_on2 << std::endl;
            } else if (x == 4) {
                f << ran_on3 << std::endl;
            }
            
            j++;
        }
        f << answer << std::endl;
        f << 1 << std::endl;
        ++i;

    }
    f.close();
}

void write_kun_quiz(int ch) {
    std::ifstream g("KanjiArchive.txt");
    
    int numQuestions = 16;
    int chapter = ch;
    
    std::ofstream f("KanjiQuiz.txt");
    f << numQuestions << std::endl;
    int i = 1;
    while (i <= numQuestions) {
        Kanji kanQuestion((16 * chapter) - 16 + i);
        char *kun = kanQuestion.get_kunyomi();
        
        f << "What is a Kun'yomi reading of:  " << kanQuestion.get_character() << std::endl;
        f << "4" << std::endl;

        vector<char*> split_r = kanQuestion.split_readings(kun);
        int maxr = max_readings(split_r);
        int ranRead = randomNumber(1, maxr);
        char *correct_read = kanQuestion.get_kunyomi(ranRead);
        char *ran_kun1 = random_kun_reading();
        char *ran_kun2 = random_kun_reading();
        char *ran_kun3 = random_kun_reading();
        /*int correct_line = find_kanji_line(correct_read);
        int r1 = find_kanji_line(ran_on1);
        int r2 = find_kanji_line(ran_on2);
        int r3 = find_kanji_line(ran_on3);
        differentiate(correct_line, r1, r2, r3);
        ran_on1 = build_kstats(r1);
        ran_on2 = build_kstats(r2);
        ran_on3 = build_kstats(r3);*/
        diff2(correct_read, ran_kun1, ran_kun2, ran_kun3);
        ran_kun1 = make_string(ran_kun1);
        ran_kun2 = make_string(ran_kun2);
        ran_kun3 = make_string(ran_kun3);

        std::vector<int> ranAnswer = {1, 2, 3, 4};
        unsigned num = chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(ranAnswer.begin(), ranAnswer.end(), default_random_engine(num));

        int j = 1;
        char answer;
        for (int& x: ranAnswer) {
            if (x == 1) {
                f << correct_read << std::endl;
                if (j == 1) {
                    answer = '1';
                } else if (j == 2) {
                    answer = '2';
                } else if (j == 3) {
                    answer = '3';
                } else if (j == 4) {
                    answer = '4';
                }
            } else if (x == 2) {
                f << ran_kun1 << std::endl;
            } else if (x == 3) {
                f << ran_kun2 << std::endl;
            } else if (x == 4) {
                f << ran_kun3 << std::endl;
            }
            j++;
        }
        f << answer << std::endl;
        f << 1 << std::endl;
        ++i;

        delete [] correct_read;
        delete [] ran_kun1;
        delete [] ran_kun2;
        delete [] ran_kun3;

    }
    f.close();
}


void reset_txt(const char *file) {  
    std::ofstream ofs;
    ofs.open(file, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
