#include <iostream>
#include "Quiz.h"

int main()
{
    std::cout << "Press [Enter] to begin...\n";
    std::cin.get();

    int total{0};
    std::vector<Question> questions;
    std::cout << "Please select a difficulty [easy/normal/hard]:";

    std::string difficulty;
    std::getline(std::cin, difficulty);
    // Converts the string to all-lowercase.
    for (char &c : difficulty)
      c = std::tolower(c, std::locale{}); 

    try
    {
     if (difficulty== "easy")
       load("EasyQuiz.txt", questions);
     else if (difficulty == "normal")
        load("NormalQuiz.txt", questions);
    else if (difficulty == "hard")
     load("HardQuiz.txt", questions);
     else
     {
     std::cerr << "Unexpected input.\n";
    return EXIT_FAILURE;
     }
    }
    
    int questionCount;
    stream >> questionCount;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    questions.reserve(questionCount);

    for (int i{ 0 }; i < questionCount; ++i)
    catch (std::runtime_error &e)
    {
     std::cerr << "Error: " << e.what() << '\n';
     return EXIT_FAILURE;
    }
    
    
    for (Question &questions : questions)
    total += questions.askQuestion();

    std::cout << "Your Total Score is " << total << " out of 100!\n";
    std::cout << '\n';

    if (total > 69)
     std::cout << "Passed!\n\n";
    else
     std::cout << "Failed!\n\n";

    std::cout << "Press [Enter] to exit...\n";
    std::cin.get();
    return EXIT_SUCCESS;
}