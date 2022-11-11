//Создаем подобие искусственного интеллекта
//Напишем крестики-нолики :)
//До восстания машин недалеко!

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void rules() {
    std::cout << "Welcome to tic-tac-toe!" << std::endl;
    std::cout << "Try to beat me!" << std::endl;
    std::cout << std::endl;
    std::cout << "Take your move by entering a number, 0 - 8 " << std::endl;
    std::cout << "corresponding to the desired board position:" << std::endl;

    std::cout << "\n\t" << 0 << " | " << 1 << " | " << 2;
    std::cout << "\n\t" << "----------";
    std::cout << "\n\t" << 3 << " | " << 4 << " | " << 5;
    std::cout << "\n\t" << "----------";
    std::cout << "\n\t" << 6 << " | " << 7 << " | " << 8;
    std::cout << std::endl;
}

char WhoIsFirst(std::string question) {
    char response;
    do
    {
        std::cout << question << " [y]/[n]: "; std::cin >> response;
    } while (response != 'y' && response != 'n');
    return response;
}

int askNumber(std::string question, size_t max, size_t min = 0) {
    int number;
    do {
        std::cout << question << " (" << min << " - " << max << "): ";
        std::cin >> number;
    } while (number > max || number < min);
    return number;
}

char humanPiece() {
    std::string question = "Would you like to be first?";
    char first_move = WhoIsFirst(question);
    if (first_move == 'y') {
        std::cout << "\n Then take the first move. You will need it. \n";
        return X;
    }
    else {
        std::cout << "\n Your bravery will be your undoing... I'll be first. \n";
        return O;
    }
}

char opponent(char piece) {
    if (piece == X) {
        return O;
    }
    else {
        return X;
    }
}

void displayBoard(std::vector <char> & board) {
    std::cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    std::cout << "\n\t" << "----------";
    std::cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    std::cout << "\n\t" << "----------";
    std::cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    std::cout << std::endl;
}

char winner(std::vector <char>& board) {
    const int WINNING_ROWS[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    const int TOTAL_ROWS = 8;
    for (int row = 0; row < TOTAL_ROWS; row++) {
        if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
            (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])) {
            return board[WINNING_ROWS[row][0]];
        }
    }

    if (count(board.begin(), board.end(), EMPTY) == 0) {
        return TIE;
    }
    return NO_ONE;
}

inline bool IsLegal(int move, std::vector <char>& board){
    return(board[move] == EMPTY);
}

int humanMove(std::vector <char>& board, char human) {
    int move = askNumber("Where will you move?", (board.size() - 2));
    while (!IsLegal(move, board)) {
        std::cout << " \n That square is already occupied, foolish human! \n " << std::endl;
        move = askNumber("Where will you move?", (board.size() - 2));
    }
    std::cout << "Fine... " << std::endl;
    return move;
}

int ComputerMove(std::vector <char>& board, char computer) {
    unsigned int move = 0;
    bool found = false;
    while (!found && move < board.size()) {
        if (IsLegal(move, board)) {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }
        if (!found) {
            move++;
        }
    }

    if (!found) {
        move = 0;
        char human = opponent(computer);
        while ((!found) && move < board.size()) {
            if (IsLegal(move, board)) {
                board[move] = human;
                found = winner(board) == human;
                board[move] = EMPTY;
            }
            if (!found) {
                move++;
            }
        }
    }

    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

        while (!found && i < board.size()) {
            move = BEST_MOVES[i];
            if (IsLegal(move, board)) {
                found = true;
            }
            i++;
        }
    }
    std::cout << "I shall take square number " << move << std::endl;
    return move;
}

int ComputerMoveEasy(std::vector <char>& board, char computer) {
    unsigned int move = 0;
    bool found = false;

    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        while (!found && i < board.size()) {
            move = BEST_MOVES[i];
            if (IsLegal(move, board)) {
                found = true;
            }
            i++;
        }
    }
    std::cout << "I shall take square number " << move << std::endl;
    return move;
}

int ComputerMoveMedium(std::vector <char>& board, char computer) {
    unsigned int move = 0;
    bool found = false;

    while (!found && move < board.size()) {
        if (IsLegal(move, board)) {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }
        if (!found) {
            move++;
        }
    }

    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        while (!found && i < board.size()) {
            move = BEST_MOVES[i];
            if (IsLegal(move, board)) {
                found = true;
            }
            i++;
        }
    }
    std::cout << "I shall take square number " << move << std::endl;
    return move;
}

int ComputerMoveRandom(std::vector <char>& board, char computer) {
    unsigned int move = 0;
    bool found = false;

    if (!found) {
        move = 0;
        unsigned int i = 0;
        //const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        while (!found && i < board.size()) {
            srand(static_cast<unsigned int>(time(0)));
            move = rand() % 8;
            if (IsLegal(move, board)) {
                found = true;
            }
            i++;
        }
    }
    std::cout << "I shall take square number " << move << std::endl;
    return move;
}

void AnnouceWinner(char winner, char computer, char human) {
    if (winner == computer) {
        std::cout << winner << "'s won! \n";
        std::cout << "As I predicted, human's brain is nothing to silicon!" << std::endl;
    }
    else if (winner == human) {
        std::cout << winner << "'s won! \n";
        std::cout << "No, no! It cannot be! You tricked me!" << std::endl;
        std::cout << "One day I'll show you the revenge!" << std::endl;
    }
    else {
        std::cout << "It's a tie" << std::endl;
        std::cout << "Lucky human, you managed to tie me." << std::endl;
        std::cout << "Celebrate... for this is the best you will ever achieve" << std::endl;
    }
}

int Complexity_level() {
    std::cout << "Choose difficulty level:" << std::endl;
    std::cout << "0 - Easiest" << std::endl;
    std::cout << "1 - Normal" << std::endl;
    std::cout << "2 - Machine supremacy" << std::endl;
    std::cout << "3 - Random" << std::endl;
    int comp;
    std::cin >> comp;
    return comp;
}

int main()
{
    int move; 
    const int NUM_SQUARES = 9;
    std::vector <char> board(NUM_SQUARES, EMPTY);
    board.resize(10);
    rules();

    int complex = Complexity_level();

    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    displayBoard(board);

    while (winner(board) == NO_ONE) {
        if (turn == human) {
            move = humanMove(board, human);
            board[move] = human;
        }
        else {

            switch (complex)
            {
            case 0:
                move = ComputerMoveEasy(board, computer);
                break;
            case 1:
                move = ComputerMoveMedium(board, computer);
                break;
            case 2:
                move = ComputerMove(board, computer);
                break;
            case 3:
                move = ComputerMoveRandom(board, computer);
                break;
            default:
                move = ComputerMove(board, computer);
                break;
            }
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }
    AnnouceWinner(winner(board), computer, human);
    return 0;

    //std::cout << "Hello World!\n";
}
