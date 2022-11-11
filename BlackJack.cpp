#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

class Card {
    friend std::ostream& operator<<(std::ostream& os, const Card& aCard);
public:
    enum rank { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };
    enum suit { DIAMONDS, HEARTS, CLUBS, SPADES };

    Card(rank r = ace, suit s = DIAMONDS, bool ifu = true);
    ~Card(){};
    int GetValue() const;
    void Flip();
protected:
    rank Rank;
    suit Suit;
    bool IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) {
    this->Rank = r;
    this->Suit = s;
    this->IsFaceUp = ifu;
}

void Card::Flip() {
    IsFaceUp = !(IsFaceUp);
}

int Card::GetValue() const{
    int value = 0;
    if (IsFaceUp) {
        value = Rank;
        if (value > 10) {
            value = 10;
        }
    }
    return value;
}

class Hand {
public: 
    Hand();
    virtual ~Hand();
    void Add(Card* card);
    void Clear();
    int GetTotal() const;
protected:
    std::vector <Card*> Cards;
};

Hand::Hand() {
    Cards.reserve(7);
}

Hand::~Hand() {
    Clear();
}

void Hand::Clear() {
    for (auto iter = Cards.begin(); iter != Cards.end(); iter++) {
        delete* iter;
        *iter = 0;
    }
    Cards.clear();
}

void Hand::Add(Card* card) {
    Cards.push_back(card);
}

int Hand::GetTotal() const {
    if (Cards.empty()) {
        return 0;
    }
    if (Cards[0]->GetValue() == 0) {
        return 0;
    }
    int total = 0;
    for (auto iter = Cards.begin(); iter != Cards.end(); iter++) {
        total += (*iter)->GetValue();
    }
    bool contains_ace = false;
    for (auto iter = Cards.begin(); iter != Cards.end(); iter++) {
        if ((*iter)->GetValue() == Card::ace) {
            contains_ace = true;
        }
    }
    if (contains_ace && total <= 11) {
        total += 10;
    }
    return total;
}

class GenericPlayer : public Hand {
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer);
public:
    GenericPlayer(const std::string & name = "");
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0;
    bool IsBusted() const;
    void Bust() const;
protected:
    std::string name;
};

GenericPlayer::GenericPlayer(const std::string& name) {
    this->name = name;
}

GenericPlayer::~GenericPlayer(){}

bool GenericPlayer::IsBusted() const {
    return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
    std::cout << name << " busts." << std::endl;
}

class Player : public GenericPlayer {
public: 
    Player(const std::string& name = " ");
    ~Player();
    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
};

Player::Player(const std::string& name) : GenericPlayer(name){}

Player::~Player(){}

bool Player::IsHitting() const{
    std::cout << name << " , do you want a hit? [Y]/[N]: ";
    char responce;
    std::cin >> responce;
    return (responce == 'Y' || responce == 'y');
}

void Player::Win() const {
    std::cout << name << " wins." << std::endl;
}

void Player::Lose() const {
    std::cout << name << " loses." << std::endl;
}

void Player::Push() const {
    std::cout << name << " pushes." << std::endl;
}

class House : public GenericPlayer {
public:
    House(const std::string& name = "House");
    ~House();
    bool IsHitting() const;
    void FlipFirstCard();
};

House::House(const std::string& name) : GenericPlayer(name){ }

House::~House(){}

bool House::IsHitting() const{
    return(GetTotal() <= 16);
}

void House::FlipFirstCard() {
    if (!(Cards.empty())) {
        Cards[0]->Flip();
    }
    else {
        std::cout << "No cards to flip!" << std::endl;
    }
}

class Desk : public Hand {
public:
    Desk();
    ~Desk();
    void Populate();
    void Shuffle();
    void Deal(Hand& aHand);
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

Desk::Desk() {
    Cards.reserve(52);
    Populate();
}

Desk::~Desk(){}

void Desk::Populate() {
    Clear();
    for (int i = Card::DIAMONDS; i < Card::SPADES; i++) {
        for (int j = Card::ace; j < Card::king; j++) {
            Add(new Card(static_cast<Card::rank>(j), static_cast<Card::suit>(i)));
        }
    }
}

void Desk::Shuffle() {
    random_shuffle(Cards.begin(), Cards.end());
}

void Desk::Deal(Hand& aHand) {
    if (!(Cards.empty())) {
        aHand.Add(Cards.back());
        Cards.pop_back();
    }
    else {
        std::cout << "Out of cards. Unable to deal." << std::endl;
    }
}

void Desk::AdditionalCards(GenericPlayer& aGenericPlayer) {
    while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) {
        Deal(aGenericPlayer);
        std::cout << aGenericPlayer << std::endl;
        if (aGenericPlayer.IsBusted()) {
            aGenericPlayer.Bust();
        }
    }
}

class Game {
public:
    Game(const std::vector<std::string>& names);
    ~Game();
    void Play();
private:
    Desk desk;
    House house;
    std::vector<Player> players;
};

Game::Game(const std::vector<std::string>& names) {
    for (auto iter = names.begin(); iter != names.end(); iter++) {
        players.push_back(Player(*iter));
    }
    srand(static_cast<unsigned int>(time(0)));
    desk.Populate();
    desk.Shuffle();
}

Game::~Game(){}

void Game::Play() {
    for (int i = 0; i < 2; i++) {
        for (auto pPlayer = players.begin(); pPlayer != players.end(); pPlayer++) {
            desk.Deal(*pPlayer);
        }
        desk.Deal(house);
    }
    house.FlipFirstCard();
    for (auto pPlayer = players.begin(); pPlayer != players.end(); pPlayer++) {
        std::cout << *pPlayer << std::endl;
    }
    std::cout << house << std::endl;

    for (auto pPlayer = players.begin(); pPlayer != players.end(); pPlayer++) {
        desk.AdditionalCards(*pPlayer);
    }

    house.FlipFirstCard();
    std::cout << std::endl << house;
    desk.AdditionalCards(house);

    if (house.IsBusted()) {
        for (auto pPlayer = players.begin(); pPlayer != players.end(); pPlayer++) {
            if (!(pPlayer->IsBusted())) {
                pPlayer->Win();
            }
        }
    }
    else {
        for (auto pPlayer = players.begin(); pPlayer < players.end(); pPlayer++) {
            if (!(pPlayer->IsBusted())) {
                if (pPlayer->GetTotal() > house.GetTotal()) {
                    pPlayer->Win();
                }
                else if (pPlayer->GetTotal() < house.GetTotal()) {
                    pPlayer->Lose();
                }
                else {
                    pPlayer->Push();
                }
            }
        }
    }

    for (auto pPlayer = players.begin(); pPlayer < players.end(); pPlayer++) {
        pPlayer -> Clear();
    }
    house.Clear();
}

std::ostream& operator<<(std::ostream& os, const Card& aCard) {
    const std::string ranks[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const std::string suits[] = { "d", "h", "c", "s" };
    if (aCard.IsFaceUp) {
        os << ranks[aCard.Rank] << suits[aCard.Suit];
    }
    else {
        os << "XX";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.name << ":\t";
    std::vector <Card*>::const_iterator pCard;
    if (!aGenericPlayer.Cards.empty()) {
        for (pCard = aGenericPlayer.Cards.begin(); pCard != aGenericPlayer.Cards.end(); pCard++) {
            os << *(*pCard) << "\t";
        }
        if (aGenericPlayer.GetTotal() != 0) {
            std::cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else {
        os << "<empty>";
    }
    return os;
}


int main()
{
    std::cout << "Welcome to BlackJack!" << std::endl;
    std::cout << std::endl;
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7) {
        std::cout << "How many players? (1 - 7)" << std::endl;
        std::cin >> numPlayers;
    }

    std::vector <std::string> namePlayers;
    std::string name;
    for (int i = 0; i < numPlayers; i++) {
        std::cout << "Enter player's name: ";
        std::cin >> name;
        namePlayers.push_back(name);
    }
    std::cout << std::endl;

    Game aGame(namePlayers);
    char again = 'y';
    while (again != 'n' && again != 'N') {
        aGame.Play();
        std::cout << "Wanna play again? [Y]/[N]: ";
        std::cin >> again;
    }
    return 0;

}
