#ifndef _Quiz_H
#define _Quiz_H
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

class Question{
public:
    std::string question_text;
    std::vector<std::string> answers;
    int question_score{0};

    
    Question() = default;
    Question(std::string question_text, const std::vector<std::string> &answers, int question_score, char correct_answer) noexcept;    
    int askQuestion()const noexcept;
    void pause()const noexcept; 
    char get_correct_answer() const noexcept;
    void set_correct_answer(char letter) noexcept; 
    void load(std::string_view path, std::vector<Question> &out); 
private:
    using Size_Type = std::vector<std::string>::size_type;
    char correct_answer{'a'};
};
#endif
