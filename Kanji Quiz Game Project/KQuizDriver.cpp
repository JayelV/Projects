#include <iostream>
using namespace std;

#include "KQuiz.h"
#include "Chapter.h"
#include "Kanji.h"

int main()
{
    srand(time(0));
    std::cout << "Press [Enter] to begin...\n";
    std::cin.get();

    reset_txt("KanjiQuiz.txt");

    int chapterNumber;
    int category;
    std::cout << "*** Kanji Oboeru ***" << endl; 
    std::cout << "*** 漢字覚える ***" << endl; 
    std::cerr << "Choose a chapter to quiz on. Enter a chapter number." << std::endl;
    display_chapters(0);
    std::cin >> chapterNumber;
    if (does_chapter_exist(chapterNumber) == false) {
        std::cerr << "Choose a chapter that exists. Try again." << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "Choose a category to quiz on. Pick a number." << std::endl;
    std::cerr << "1. Meaning" << '\n' << "2. On'yomi readings" << '\n' << "3. Kun'yomi readings" << std::endl;
    std::cin >> category;
    choose_quiz(chapterNumber, category);
    

    int total{0};
    std::vector<Question> questions;
    std::ifstream stream{"KanjiQuiz.txt"};
    if (!stream)
    {
        std::cerr << "Could not open file!\n";
        return EXIT_FAILURE;
    }

    int questionCount;
    stream >> questionCount;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    questions.reserve(questionCount);

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
        questions.emplace_back(std::move(question));
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::random_device rand_device;
    std::default_random_engine engine{rand_device()};
    std::shuffle(questions.begin(), questions.end(), engine);
    
    
    for (Question &questions : questions)
    total += questions.askQuestion();

    std::cout << "You answered " << total << " out of " << questionCount << " correctly! " << '\n';
    std::cout << '\n';

    return EXIT_SUCCESS;
}