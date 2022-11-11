#include <iostream>

int main()
{
    char option;
    do {
        std::cout << "0. Q - Leave" << std::endl;
        std::cout << "1. A - Listen to your critter" << std::endl;
        std::cout << "2. F - Feed your critter" << std::endl;
        std::cout << "3. D - Play with your critter" << std::endl;
        std::cin >> option;
        std::cout << "Choice: " << option << std::endl;

        switch (option) {
        case 'A':
            std::cout << "Option A" << std::endl;
            break;
        case 'F':
            std::cout << "Option F" << std::endl;
            break;
        case 'D':
            std::cout << "Option D" << std::endl;
            break;
        default:
            std::cout << "I did nothing" << std::endl;
        }

    } while (option != 'Q');

    std::cout << "Hello World!\n";
}
