#include "KQuiz.h"
#include "Chapter.h"
#include "Kanji.h"
#include "../react.h"

Question::Question(std::string question_text, const std::vector<std::string> &answers, int question_score, char correct_answer) noexcept
    : question_text{question_text}, 
    answers{answers}, 
    question_score{question_score},
    correct_answer{std::tolower(correct_answer, std::locale{})}
    {
    }

int Question::askQuestion() const noexcept
    {
    char guess;
    std::cout << '\n';
    std::cout << question_text << '\n';
    for (Size_Type i{0}; i < answers.size(); ++i)
    {
    char letter{static_cast<char>('1' + i)};
    std::cout << letter << ". " << answers[i] << '\n';
    }
    std::cout << '\n';

    std::cin >> guess;
    guess = std::tolower(guess, std::locale{});
    if (guess == correct_answer) {
        std::cout << '\n';
        std::cout << "Correct!\n";
        std::cout << '\n';
        return question_score;
    }
    else 
    {
        std::cout << '\n';
        std::cout << "Incorrect.\n";
        std::cout << "The correct answer is " << correct_answer << '\n';
        std::cout << '\n';
        return 0;
    }
    }

void Question::pause() const noexcept
    {
    std::cout << "Press [Enter] to continue.";
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // include <limits> for std::numeric_limits.
    }

char Question::get_correct_answer() const noexcept
    {
    return correct_answer;
    }

void Question::set_correct_answer(char letter) noexcept
    {
    correct_answer = static_cast<char>(std::tolower(letter));
    }

/*void Question::put_in_global_mem(int offset) {
    gm_size = 4;
    gm_size += gm_put_string(offset + gm_size, question_text);
    gm_size += gm_put_string(offset + gm_size, answers);
    _put_int(offset, gm_size);
    _put_int(offset + 4, question_score);
}

void Question::get_from_global_mem(int offset) {
    gm_size = _get_int(offset);
    question_text = make_string(gm_get(string(offset)));
    answers = make_string(gm_get(string(offset + strlen(question_text))));
    question_score = _put_int(offset + strlen(question_text) + strlen(answers));

}*/