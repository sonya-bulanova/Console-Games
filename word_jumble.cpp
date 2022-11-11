#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>

int main() {

	std::map<std::string, std::string> dictionary;

	dictionary = { { "debug", "Getting rid of mistakes" },
		{"disconnect", "You get angry, when Wi-Fi does that"},
		{"compile", "Making words understandable for machine"},
		{"database", "SQL is native language for them"},
		{"encrypt", "Making data non-understandable"},
		{"namespace", "Not OK to write this with std"},
		{"password", "Magic set of symbols to enture"},
		{"prohibit", "not allow"},
		{"inheritage", "Getting from parents"},
		{"polymorphism", "Taking on different appearence"}};

	/* for (auto i = dictionary.begin(); i != dictionary.end(); i++) {
		std::cout << i->first << std::endl;
	}*/

	srand(static_cast<unsigned int>(time(0)));

	int choice = (rand() % dictionary.size());
	//std::cout << choice << std::endl;
	std::map<std::string, std::string>::iterator iter = dictionary.begin();
	advance(iter, choice);

	std::string jumbled_word = iter->first;
	int length = jumbled_word.size();
	for (int i = 0; i < length; i++) {
		int idx1 = rand() % length;
		int idx2 = rand() % length;
		char temp = jumbled_word[idx1];
		jumbled_word[idx1] = jumbled_word[idx2];
		jumbled_word[idx2] = temp;
	}

	std::cout << "I have mixed letters in this word!" << std::endl;
	std::cout << "Try to guess, what is the word!" << std::endl;
	std::cout << "If you get stuck, you can ask for help using [H]!" << std::endl;
	std::cout << "Good Luck!" << std::endl;

	std::cout << std::endl;
	std::cout << jumbled_word << std::endl;
	std::string guess;
	std::cout << "Your guess: ";
	std::cin >> guess;

	while (guess != iter->first) {
		if (guess == "H") {
			std::cout << iter->second << std::endl;
		}
		else {
			std::cout << "Oh, sorry, that's not the word :( " << std::endl;
		}
		std::cout << "Your guess: ";
		std::cin >> guess;
	}

	std::cout << "Good play! Thanks! Let's play again!" << std::endl;

	//std::cout << iter->first << std::endl;
	return 0;
}