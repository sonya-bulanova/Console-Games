//угадывать слово по буквам, невозможно ввести сразу все слово!

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>

int main()
{
    std::vector <std::string> dictionary = {"algorithm", "debug", 
        "disconnect", "compile", "database", "encrypt", "namespace", 
        "password", "prohibit", "inheritage", "polymorphism"};
    const int MAX_WRONG = 8;

    srand(static_cast<unsigned int>(time(0)));
    int choice = (rand () % dictionary.size());
    std::string chosen_word = dictionary[choice];

    int wrong = 0;

    std::string opened(chosen_word.size(), '_');
    //guessed letters
    std::string used = "";

    std::cout << chosen_word << std::endl;

    std::cout << "Welcome to Hangman!" << std::endl;
    std::cout << "I have a word for you. Try to guess it!" << std::endl;
    std::cout << opened << std::endl;

    while ((wrong < MAX_WRONG) && (opened != chosen_word)) {
        char letter;

        std::cout << " You have " << (MAX_WRONG - wrong) << " lives left " << std::endl;
        std::cout << "The word is: " << opened << std::endl;

        std::cout << std::endl;
        std::cout << "Enter your guess" << std::endl;
        std::cin >> letter;
        while (used.find(letter) != std::string::npos) {
            std::cout << std::endl;
            std::cout << "You're already guessed: " << letter << std::endl;
            std::cout << "Enter your guess: ";
            std::cin >> letter;
        }

        used += letter;
        if (chosen_word.find(letter) != std::string::npos) {
            std::cout << "That's right! Letter " << letter << " is in the word!" << std::endl;
            for (int i = 0; i < chosen_word.length(); i++) {
                if (chosen_word[i] == letter) {
                    opened[i] = letter;
                }
            }
        }
        else {
            std::cout << "Sorry. " << letter << " isn't in the word :( " << std::endl;
            wrong++;
        }
    }
    if (wrong == MAX_WRONG) {
        std::cout << " You have been hanged! " << std::endl;
    }
    else {
        std::cout << " You guessed it! " << std::endl;
    }
    std::cout << "The word was: " << chosen_word << std::endl;
    return 0;
}
