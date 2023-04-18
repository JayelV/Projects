/* library functions for Kanji Quiz application - header file */

#include <string>
#include<cstring>
#include <chrono>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

char *make_string(const char *str);

int gm_put_string(int offset, const char *str);
int gm_put_string(int offset, string &str);
const char *gm_get_string(int offset);
int gm_get_string_length(int offset);

char *convert(const std::string & s);

string get_suffix(const char* str);

int max_lines();
int max_readings(vector<char*> reading_arr);
bool does_chapter_exist(int ch);
int randomNumber();
void differentiate_lines (int &correct_line, int &ranNumber);
void differentiate(int &right_answer, int &ranNumber1, int &ranNumber2, int &ranNumber3);
void diff2 (char *&correct, char *&r1, char *&r2, char *&r3);

void display_chapters(int ch);

void choose_quiz(int ch, int ca);
int random_line();
char *random_on_reading();
char *randon_kun_reading();
void write_meaning_quiz(int ch);
void write_on_quiz(int ch);
void write_kun_quiz(int ch);
int find_kanji_line(const char *k);

void reset_txt(const char* file);
    
