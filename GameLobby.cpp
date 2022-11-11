//Симулируется зона ожидания игроков
//ака ожидание соперника в Warface... 

#include <iostream>
#include <vector>

class Player {
public:
    Player(const std::string & name = "");
    std::string GetName() const;
    Player* GetNext() const;
    void SetNext(Player* next);
private:
    std::string m_Name;
    Player* m_pNext;
};

Player::Player(const std::string& name) : m_Name(name), m_pNext(0) {}

std::string Player::GetName() const {
    return m_Name;
}

Player* Player::GetNext() const {
    return m_pNext;
}

void Player::SetNext(Player* next) {
    m_pNext = next;
}

class Lobby {
    friend std::ostream& operator<<(std::ostream& os, const Lobby& aLobby);
public:
    Lobby();
    ~Lobby();
    void AddPlayer();
    void RemovePlayer();
    void Clear();
private:
    Player* m_pHead; //указатель на головной элемент
};

Lobby::Lobby() : m_pHead(0) {}

Lobby::~Lobby() {
    //Clear();
}

void Lobby::AddPlayer() {
    std::cout << "Please enter the name of the new player: ";
    std::string name;
    std::cin >> name;
    Player* NewPlayer = new Player(name);
    if (m_pHead == 0) {
        m_pHead = NewPlayer;
    }
    else {
        Player* pIter = m_pHead;
        while (pIter->GetNext() != 0) {
            pIter = pIter->GetNext();
        }
        pIter->SetNext(NewPlayer);
    }
}

void Lobby::RemovePlayer() {
    if (m_pHead) {
        std::cout << "The game lobby is empty. No one is to remove. " << std::endl;
        //std::cout << "mistake is here" << std::endl;
    }
    else {
        Player* pTemp = m_pHead;
        m_pHead = m_pHead->GetNext();
        delete pTemp;
    }
}

void Lobby::Clear() {
    while (m_pHead != 0) {
        RemovePlayer();
    }
}

std::ostream& operator<<(std::ostream& os, const Lobby& aLobby) {
    Player* pIter = aLobby.m_pHead;
    os << "\n Here's who's in the game lobby: \n";
    if (pIter == 0) {
        os << "The lobby is empty... \n";
    } else {
        while (pIter != 0) {
            os << pIter->GetName() << std::endl;
            pIter = pIter->GetNext();
        }
    } 
    return os;
}

int main()
{
    Lobby myLobby;
    int choice;

    do
    {
        //std::cout << myLobby;
        std::cout << "\n GAME LOBBY \n";
        std::cout << "0 - Exit the program." << std::endl;
        std::cout << "1 - Add a player to the lobby." << std::endl;
        std::cout << "2 - Remove a player from the lobby." << std::endl;
        std::cout << "3 - Clear tle lobby." << std::endl;
        std::cout << "4 - Show the lobby." << std::endl;

        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 0: std::cout << "Bye!" << std::endl; break;
        case 1: myLobby.AddPlayer(); break;
        case 2: myLobby.RemovePlayer(); break;
        case 3: myLobby.Clear(); break;
        case 4: std::cout << myLobby << std::endl;
        default: std::cout << "I did nothing" << std::endl;
        }

    } while (choice != 0);
}
