#include <iostream> 
#include <string>
#include <string_view>
#include <array>
char guess; 
int total; 

class Question{
    using SizeType = std::array<std::string_view, 4>::size_type;
public:
    void setValues(std::string_view, std::string_view, std::string_view, std::string_view, std::string_view, char, int); 
    void askQuestion(); 
    void Question();

private:
    std::array<std::string_view, 4> answers;
    SizeType correct_answer;
    int Question_Score;
};
Question::Question(std::string_view text, const std::array<std::string> &answers, SizeType correct_answer, int score) noexcept
  : question_text{text},
answers{answers},
  correct_answer{correct_answer},
  question_score{score}
{
}
void Question::askQuestion()
{
    std::cout << "\n";
    std::cout << std::string_view Question_Text << "\n";
    std::cout << "a. " << answer_1 << "\n";
    std::cout << "b. " << answer_2 << "\n";
    std::cout << "c. " << answer_3 << "\n";
    std::cout << "d. " << answer_4 << "\n";
    std::cout << "\n";

    std::cin >> guess;
    if (guess == SizeType correct_answer) {
        std::cout << "\n";
        std::cout << "Correct!\n";
        total = total + Question_Score;
        std::cout << "\n";
        std::cout << "Press enter to continue.\n";
        std::cin.get();
        std::cin.ignore();
    }
    else 
    {
        std::cout << "\n";
        std::cout << "Sorry, you're wrong...\n";
        std::cout << "The correct answer is " << SizeType correct_answer << ".\n";
        std::cout << "\n";
        std::cout << "Press enter to continue.\n";
        std::cin.get();
        std::cin.ignore();
    }
}
int main()
{
    std::cout << "Press enter to start...\n";
    std::cin.get();
    std::string_view respond;
    std::cout << "Are you ready to start the KANJI quiz, " << "? Yes/No.\n";
    std::cin >> respond;
    if (respond == "Yes" || respond == "yes") {
        std::cout << "\n";
        std::cout << "Good luck!\n";
        std::cout << "\n";
        std::cout << "Press enter to continue.";
        std::cin.get();
        std::cin.ignore();
    }else{
        std::cout << "\n";
        std::cout << "Goodbye!\n";
        std::cin.ignore();
        std::cin.get();
        return 0;
    }

    Question q1;
    Question q2;
    Question q3;
    Question q4;
    Question q5;

    q1.setValues("1.",
        "A",
        "B",
        "C",
        "D",
        'C',
        4);

    q2.setValues("2.",
        "A",
        "B",
        "C",
        "D",
        'C',
        4);

    q3.setValues("3. ",
        "A",
        "B",
        "C",
        "D",
        'C',
        4);

    q4.setValues("4. ",
        "A",
        "B",
        "C",
        "D",
        'C',
        4);

    q5.setValues("5. ",
        "A",
        "B",
        "C",
        "D",
        'C',
        4);

    q1.askQuestion();
    q2.askQuestion();
    q3.askQuestion();
    q4.askQuestion();
    q5.askQuestion();

    std::cout << "Your Total Score is " << total << " out of 100!\n";
    std::cout << "\n";

    if (total > 69) {
        std::cout << "( Passed )\n";
        std::cout << "\n";
        std::cin.get();
        std::cin.ignore();
        return 0;
    }
    else
    {
        std::cout << "You failed. \n";
        std::cout << "\n";
    }
    std::cin.get();
    std::cin.ignore();
    return 0;
}