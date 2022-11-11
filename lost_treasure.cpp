/******************************************************************************

							  Online C++ Compiler.
			   Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>

struct character {
	std::string name;
	std::string weapon;
	std::string phrase;
};

struct song {
	std::string begin = "There once was a ship in a cosmic sea...\nThe name of the ship was ";
	std::string part1 = "The Sun winds blew up, her bow dipped down \nOh blow, my bully boys, blow \n";
	std::string chorus = "\nSoon may the Wellerman come \nTo bring us fuel and tea and rum \nOne day, when the tonguing is done \nWe'll take our leave and go\n";
	std::string part2 = "She'd not been two weeks from shore \nWhen down on her an asteroid bore \nCap ";
	std::string part3 = "Before the boat had hit the planet \nThe alien's tail came up and caught her \nAll hands to the side, harpooned and fought her \nWhen she dived down low\n";
	std::string part4 = "No line was cut, no alien was freed \nThe captain's mind was not of greed \nAnd he belonged to the Alienman's creed \nShe took that ship in tow\n";
	std::string part5 = "For forty years or even more \nThe line went slack then tight once more \nThe ship was lost, the crew was four \nBut still that alien did go\n";
	std::string part6 = "As far as I've heard, the fight's still on \nThe line's not cut, and the alien's not gone \nThe Wellerman makes his regular call \nTo encourage the captain, crew and all";

};

int main() {
	character captain;
	song song;
	std::string ship_name;

	std::cout << song.begin;
	getline(std::cin, ship_name);
	std::cout << song.begin + ship_name << std::endl;
	std::cout << song.part1 + "\n" + song.chorus << std::endl;
	std::cout << song.part2 << std::endl;
	getline(std::cin, captain.name);
	std::cout << song.part2 + captain.name + " took her ";
	getline(std::cin, captain.weapon);
	std::cout << captain.weapon << " and swore " << std::endl;
	getline(std::cin, captain.phrase);
	std::cout << captain.phrase << std::endl;
	std::cout << song.chorus << std::endl;
	std::cout << song.part3 + "\n" + song.chorus << std::endl;

	std::cout << song.part4 + "\n" + song.chorus << std::endl;

	std::cout << song.part5 + "\n" + song.chorus << std::endl;

	std::cout << song.part6 + "\n" + song.chorus << std::endl;
	std::cout << std::endl;
	std::cout << "Game over!" << std::endl;
	return 0;
}