#include "Quiz.h"
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
    char letter{static_cast<char>('a' + i)};
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
        std::cout << "Sorry, you're wrong...\n";
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

inline char Question::get_correct_answer() const noexcept
    {
    return correct_answer;
    }

inline void Question::set_correct_answer(char letter) noexcept
    {
    correct_answer = static_cast<char>(std::tolower(letter));
    }

void load(std::string_view path, std::vector<Question> &out)
{
    std::ifstream stream{path.data()};
    if (!stream)
      throw std::runtime_error{"Could not open file"};
  
    int questionCount;
    stream >> questionCount;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    out.reserve(questionCount);

    for (int i{ 0 }; i < questionCount; ++i)
    {
        Question question;
        std::getline(stream, question.question_text);
        int number_of_answers;
        stream >> number_of_answers;
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        question.answers.reserve(number_of_answers);
        for (int j{ 0 }; j < number_of_answers; ++j)
        {
            std::string answer;
            std::getline(stream, answer);
            question.answers.emplace_back(answer);
        }

        char correct_answer;
        stream >> correct_answer;
        question.set_correct_answer(correct_answer);

        stream >> question.question_score;
        out.emplace_back(std::move(question));
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}