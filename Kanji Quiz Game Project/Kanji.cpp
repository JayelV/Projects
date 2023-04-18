#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<chrono>

#include "Kanji.h"
#include "../react.h"

Kanji::Kanji(int ch, const char *c, const char *m, const char *on, const char *kun) : chapter(ch){ // raw constructor
    character = make_string(c);
    meaning = make_string(m);
    onyomi = make_string(on);
    kunyomi = make_string(kun);
}

Kanji::Kanji(char ch) { // default constructor
    chapter = ch;
    character = make_string("");
    meaning = make_string("");
    onyomi = make_string("");
    kunyomi = make_string("");
}

Kanji::Kanji(void) { // true default constructor
    chapter = 0;
    character = make_string("");
    meaning = make_string("");
    onyomi = make_string("");
    kunyomi = make_string("");
}

Kanji::Kanji(const Kanji &kanji) { // copy constructor
    chapter = kanji.chapter;
    character = make_string(kanji.character);
    meaning = make_string(kanji.meaning);
    onyomi = make_string(kanji.onyomi);
    kunyomi = make_string(kanji.kunyomi);
}


char *Kanji::meaning_space() {
    char *new_meaning = make_string(meaning);
    int len = strlen(meaning);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (new_meaning[j + 1] == '_') {
                new_meaning[j + 1] = ' ';
            }
        }
    }
    return new_meaning;
}

Kanji &Kanji::operator=(const Kanji &kanji) { // assignment operator
    chapter = kanji.chapter;
    delete [] character;
    delete [] meaning;
    delete [] onyomi;
    delete [] kunyomi;

    character = make_string(kanji.character);
    meaning = make_string(kanji.meaning);
    onyomi = make_string(kanji.onyomi);
    kunyomi = make_string(kanji.kunyomi);

    return *this;
}

vector<char*> Kanji::split_readings(const char *reading) { // splits onyomi or kunyomi into an array
    string reading_string = reading;
    stringstream ss(reading_string);
    string item;
    vector<string> list;

    while(getline(ss, item, ',')) {
        list.push_back(item);
    }

    vector<char*> reading_char;
    transform(list.begin(), list.end(), back_inserter(reading_char), convert);

    /*for (size_t i = 0; i < reading_char.size(); ++i) {
        cout << reading_char[i] << endl;
    }*/

    return reading_char;
}

char *Kanji::get_onyomi(int n) {
    vector<char*> reading_arr = split_readings(onyomi);

    size_t ns = n;
    size_t index = n - 1;
    size_t i = 0;
   
    while (i < reading_arr.size()) {
        ++i;
    }

    if (ns <= 0) {
        return reading_arr[0];
    } else if (ns > i - 1) {
        return reading_arr[i - 1];
    } else {
        return reading_arr[index];
    }
}


char *Kanji::get_kunyomi(int n) { 
    vector<char*> reading_arr = split_readings(kunyomi);

    size_t ns = n;
    size_t index = n - 1;
    size_t i = 0;
   
    while (i < reading_arr.size()) {
        ++i;
    }

    if (ns <= 0) {
        return reading_arr[0];
    } else if (ns > i - 1) {
        return reading_arr[i - 1];
    } else {
        return reading_arr[index];
    }
}

int Kanji::find_kanji_line() { // identifies the number of the line the kanji character is in
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

int Kanji::find_kanji_line(const char *k) { // identifies the number of the line a kanji character is in
    character = make_string(k);
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

void Kanji::build_kstats(int line) { // creates the stats of a kanji character by a line
    ifstream g(archivefile);
    string kanji_line;
    int current_line = 0;
    while (getline(g, kanji_line)) {
        if (current_line == line) {
            istringstream g(kanji_line);
            char c[DEFAULT_SIZE], m[DEFAULT_SIZE], on[DEFAULT_SIZE], kun[DEFAULT_SIZE];
            int ch;
            g >> ch >> c >> m >> on >> kun;
            chapter = ch;
            character = make_string(c);
            meaning = make_string(m);
            onyomi = make_string(on);
            kunyomi = make_string(kun);
        }
        current_line++;
    }
}


void Kanji::build_kstats(const char *k) { // creates the stats of a kanji character by const char *
    int line = find_kanji_line(k);
    build_kstats(line);
}

void Kanji::build_kstats(string k) { // creates the stats of a kanji character by string
    char *kan = const_cast<char*>(k.c_str());
    int line = find_kanji_line(kan);
    build_kstats(line);
}

void Kanji::build_all_kstats() { // creates stats for all the kanji in KanjiArchive.txt
    ifstream g(archivefile);
    string kanji_line;
    int current_line = 0;
    while (getline(g, kanji_line)) {
        istringstream g(kanji_line);
        char c[DEFAULT_SIZE], m[DEFAULT_SIZE], on[DEFAULT_SIZE], kun[DEFAULT_SIZE];
        int ch;
        g >> ch >> c >> m >> on >> kun;
        chapter = ch;
        character = make_string(c);
        meaning = make_string(m);
        onyomi = make_string(on);
        kunyomi = make_string(kun);
        current_line++;
        cerr << kanji_line << endl;
    }
}

string Kanji::make_kstring() {
    stringstream ss;
    ss << chapter << ' ' << character << ' ' << meaning << ' '  << onyomi << ' ' << kunyomi << '\n';
    return string(ss.str());
}

string Kanji::make_kstring(int line) {
    stringstream ss;
    ss << chapter << ' ' << character << ' ' << meaning << ' '  << onyomi << ' ' << kunyomi << '\n';
    return string(ss.str());
}

void Kanji::display_kstats(void) {
    cerr << '\n' << "Chapter " << chapter << '\n' << character << ' ' << meaning << '\n' << "On: " << onyomi << "  Kun: " << kunyomi << '\n' << endl;
}


int Kanji::put_in_global_mem(int offs) {
        // Note: lowest 4 bytes reserved for the final value of gm_size
    int curr = 4; // offs+curr is offset of next available location in _global_mem
    _put_char(offs+curr, KanjiTypeCode);  // store type code for polymorphism
    curr++;
    _put_int(offs+curr, chapter);
    curr += 4;
    curr += gm_put_string(offs+curr, character);
    _put_int(offs+curr, ui_offset);  
    curr += 4;
    curr += gm_put_string(offs+curr, meaning);
    _put_int(offs+curr, ui_offset);  
    curr += 4;
    /*curr += gm_put_string(offs+curr, onyomi);
    _put_int(offs+curr, ui_offset);  
    curr += 4;
    curr += gm_put_string(offs+curr, kunyomi);
    _put_int(offs+curr, ui_offset);  
    curr += 4;*/
    _put_int(offs+curr, ui_size);
    curr += 4;

    gm_size = curr;  
    _put_int(offs, gm_size);
    return gm_size;
}

int Kanji::get_from_global_mem(int offs) {
    int curr = 0;  // offs+curr is offset of next value in _global_mem
    gm_size = _get_int(offs+curr);
    curr += 4;
    curr++;  // skip past type code - used else wherefor polymorphism
    chapter = _get_int(offs+curr);  
    curr += 4;
    character = make_string(gm_get_string(offs+curr));  
    curr += gm_get_string_length(offs+curr);
    ui_offset = _get_int(offs+curr);  
    curr += 4;
    meaning = make_string(gm_get_string(offs+curr));  
    curr += gm_get_string_length(offs+curr);
    ui_offset = _get_int(offs+curr);  
    curr += 4;
  /*onyomi = make_string(gm_get_string(offs+curr));  
    curr += gm_get_string_length(offs+curr);
    ui_offset = _get_int(offs+curr);  
    curr += 4;
    kunyomi = make_string(gm_get_string(offs+curr));  
    curr += gm_get_string_length(offs+curr);
    ui_offset = _get_int(offs+curr);  
    curr += 4; */
    ui_size = _get_int(offs+curr);  
    curr += 4;
    ui_setup(ui_offset);

    return curr;
}

void Kanji::ui_setup(int offs) {
    ui_params = {{"header", offs},
        {"kanji", offs+26},
        {"choice1", offs+50},
        {"choice2", offs+74},
        {"choice3", offs+98},
        {"choice4", offs+122}};
    ui_size = 146;
}

// store this objects UI strings in _global_mem using id, starting at offs
// returns offset 
int Kanji::draw(string id, int offs) { 
    ui_offset = offs;
    ui_setup(offs);
    Dict params = ui_params;
    params["id"] = id;
    add_yaml("KanjiQuizApp.yaml", params);
    put_ui_string("heading", "The meaning of the kanji:");
    put_ui_string("kanji", get_character());

    int kanji_line = find_kanji_line();

    int ran1 = random_line();
    int ran2 = random_line();
    int ran3 = random_line();
    differentiate(kanji_line, ran1, ran2, ran3);

    Kanji kanRan1(ran1);
    Kanji kanRan2(ran2);
    Kanji kanRan3(ran3);

    char *correct_choice;
    char *wrong1;
    char *wrong2;
    char *wrong3;

    std::vector<int> ranAnswer = {1, 2, 3, 4};
    unsigned num = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(ranAnswer.begin(), ranAnswer.end(), default_random_engine(num));

    int j = 1;
    for (int& x: ranAnswer) {
        stringstream ss;
        if (x == 1) {
            correct_choice = meaning_space();
            ss << correct_choice;
            put_ui_string("choice1", ss.str().c_str());
        } else if (x == 2) {
            wrong1 = kanRan1.meaning_space();
            ss << wrong1;
            put_ui_string("choice2", ss.str().c_str());
        } else if (x == 3) {
            wrong2 = kanRan2.meaning_space();
            ss << wrong2;
            put_ui_string("choice3", ss.str().c_str());
        } else if (x == 4) {
            wrong3 = kanRan3.meaning_space();
            ss << wrong3;
            put_ui_string("choice4", ss.str().c_str());
        }
        j++;
    }

    return ui_size;
}