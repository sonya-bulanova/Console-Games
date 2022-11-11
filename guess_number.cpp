#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int rand_func() {
    srand(static_cast<unsigned int>(time(0);
    int num = rand() % 50 + 1;
    //std::cout << num << std::endl;
    return num;
}

void logic(int num) {
    bool game_over = false;
    int counter = 0;
    int guess;
    char choice;
    while (!game_over) {
        std::cout << "I have a number. Guess it." << std::endl;
        std::cin >> guess;

        if (counter == 10) {
            std::cout << "Your attempts ran out. Goodbye." << std::endl;
            game_over = true;
        }
        else {
            if (guess == num) {
                std::cout << "Got it. You won!" << std::endl;
                game_over = true;
            }
            else if (guess > num) {
                std::cout << "No. Try smaller one." << std::endl;
            }
            else {
                std::cout << "No. Try bigger one." << std::endl;
            }
        }
        counter++;
    }

}

int main()
{
    logic(rand_func());
}
