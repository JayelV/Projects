#ifndef _Quiz_H_
#define _Quiz_H_

#include <iostream> 
#include <string>
#include <array>
#include <vector>
#include <limits>
#include <algorithm> 
#include <fstream>
#include <utility>
#include <locale> 
#include <cstdlib> 
#include <random>
#include "Chapter.h"
#include "Kanji.h"

class Question{
protected:
    int gm_size;
public:
    
    std::string question_text;
    std::vector<std::string> answers;
    int question_score{0};

    Question() = default;
    Question(std::string question_text, const std::vector<std::string> &answers, int question_score, char correct_answer) noexcept;
    int randomNumber();
    int askQuestion()const noexcept;
    void pause()const noexcept; 
    char get_correct_answer() const noexcept;
    void set_correct_answer(char letter) noexcept;  

    void put_in_global_mem(int offset);
    void get_from_global_mem(int offset);

private:
    using Size_Type = std::vector<std::string>::size_type;
    char correct_answer{'1'};
};

#endif