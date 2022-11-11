#include <iostream>
#include <string>

std::string get_string(std::string str_) {
    std::string strings;
    std::cout << str_;
    std::cin >> strings;
    return strings;
}

int get_number(std::string str_) {
    int number;
    std::cout << str_;
    std::cin >> number;
    return number;
}

void make_text(std::string name, std::string noun, int number, std::string body_part, std::string verb) {
    std::cout << "Here's our story!"  << std::endl;
    std::cout << "The famous explorer " << name;
    std::cout << " had nearly given up a life-long quest to find " << std::endl;
    std::cout << "The Lost Planet of " << noun << ", when one day the " << noun;
    std::cout << " found the explorer. " << std::endl;
    std::cout << " Surrounded by " << number << " " << noun;
    std::cout << ", a tear came to " << name << "'s " << body_part << std::endl;
    std::cout << "After all this time, the quest was finally over. ";
    std::cout << "And then, the " << noun << std::endl;
    std::cout << " promptly devoured " << name << '.' << std::endl;
    std::cout << "The moral of the story? Be careful what you " << verb << " for. " << std::endl;
}

int main()
{
    std::string ask_name = "Enter a name: ";
    std::string ask_num = "Enter a number: ";
    std::string ask_noun = "Enter a plural noun: ";
    std::string ask_verb = "Enter a verb: ";
    std::string ask_body_part = "Enter a body part: ";

    std::cout << "Please, answer my questions to help create a story!" << std::endl;
    std::string name = get_string(ask_name);
    std::string noun = get_string(ask_noun);
    int num = get_number(ask_num);
    std::string body_part = get_string(ask_body_part);
    std::string verb = get_string(ask_verb);
    make_text(name, noun, num, body_part, verb);
}
