#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include <string>
#include <stdexcept>

using namespace std;

// ==================== Enums ====================
enum class PLAYER { HUMAN, BOT };
enum class JUMP { LADDER, SNAKE };

// ==================== Jump Base ====================
class Jump {
public:
    virtual int getInward() const = 0;
    virtual int getOutward() const = 0;
    virtual ~Jump() = default;
};

class Ladder : public Jump {
    int inward, outward;
public:
    Ladder(int in, int out) : inward(in), outward(out) {
        if (out <= in) throw invalid_argument("Ladder must go upwards!");
        cout << "Ladder created: " << in << " -> " << out << "\n";
    }
    int getInward() const override { return inward; }
    int getOutward() const override { return outward; }
};

class Snake : public Jump {
    int inward, outward;
public:
    Snake(int in, int out) : inward(in), outward(out) {
        if (out >= in) throw invalid_argument("Snake must go downwards!");
        cout << "Snake created: " << in << " -> " << out << "\n";
    }
    int getInward() const override { return inward; }
    int getOutward() const override { return outward; }
};

// ==================== Jump Factory ====================
class JumpFactory {
public:
    static shared_ptr<Jump> createJump(JUMP type, int inward, int outward) {
        switch (type) {
            case JUMP::SNAKE: return make_shared<Snake>(inward, outward);
            case JUMP::LADDER: return make_shared<Ladder>(inward, outward);
            default: throw invalid_argument("Invalid jump type");
        }
    }
};

// ==================== Player Base ====================
class Player {
public:
    virtual int getId() const = 0;
    virtual string getName() const = 0;
    virtual ~Player() = default;
};

class Human : public Player {
    string name;
    int id;
public:
    Human(const string& name, int id) : name(name), id(id) {
        cout << "Human player created: " << name << "\n";
    }
    int getId() const override { return id; }
    string getName() const override { return name; }
};

class Bot : public Player {
    string name;
    int id;
public:
    Bot(const string& name, int id) : name(name), id(id) {
        cout << "Bot player created: " << name << "\n";
    }
    int getId() const override { return id; }
    string getName() const override { return name; }
};

// ==================== Player Factory ====================
class PlayerFactory {
public:
    static shared_ptr<Player> createPlayer(PLAYER type, const string& name, int id) {
        switch (type) {
            case PLAYER::HUMAN: return make_shared<Human>(name, id);
            case PLAYER::BOT: return make_shared<Bot>(name, id);
            default: throw invalid_argument("Invalid player type");
        }
    }
};

// ==================== Dice ====================
class Dice {
    vector<int> faces;
    mt19937 gen;
    uniform_int_distribution<> dist;
public:
    Dice(int limit) : gen(random_device{}()), dist(1, limit) {
        for (int i = 1; i <= limit; i++) faces.push_back(i);
    }
    int roll() { return dist(gen); }
};

// ==================== Board ====================
class Board {
    int boardSize;
    unordered_map<int, int> playerPositions; // playerId -> position
    unordered_map<int, int> jumpMap;
    unordered_set<int> usedOutward;
public:
    Board(int size) : boardSize(size) {}

    int getSize() const { return boardSize; }

    bool addJump(const shared_ptr<Jump>& jump) {
        int in = jump->getInward(), out = jump->getOutward();
        if (jumpMap.count(in) || usedOutward.count(out)) return false;
        jumpMap[in] = out;
        usedOutward.insert(out);
        return true;
    }

    int movePlayer(int id, int move) {
        int currentPos = playerPositions[id];
        int newPos = currentPos + move;

        if (newPos > boardSize) {
            cout << "Player " << id << " rolled too high, stays at " << currentPos << "\n";
            return currentPos;
        }

        // Check for jump
        if (jumpMap.count(newPos)) {
            cout << "Player " << id << " hit a jump at " << newPos << " -> " << jumpMap[newPos] << "\n";
            newPos = jumpMap[newPos];
        }

        playerPositions[id] = newPos;
        cout << "Player " << id << " moved to " << newPos << "\n";
        return newPos;
    }

    void addPlayer(int id) { playerPositions[id] = 0; }
};

// ==================== Game Controller ====================
class GameController {
    vector<int> turnOrder;
    unordered_map<int, shared_ptr<Player>> players;
    unique_ptr<Dice> dice;
    unique_ptr<Board> board;
    int turnIndex = 0;
public:
    GameController(int boardSize, int diceLimit)
        : dice(make_unique<Dice>(diceLimit)), board(make_unique<Board>(boardSize)) {}

    void addPlayer(const shared_ptr<Player>& player) {
        int id = player->getId();
        if (players.count(id)) throw invalid_argument("Duplicate player ID");
        players[id] = player;
        turnOrder.push_back(id);
        board->addPlayer(id);
        cout << "Player added: " << player->getName() << "\n";
    }

    void addJump(const shared_ptr<Jump>& jump) {
        if (!board->addJump(jump)) {
            throw invalid_argument("Invalid jump placement");
        }
    }

    void playTurn() {
        if (turnOrder.empty()) {
            cout << "No players available.\n";
            return;
        }

        int playerId = turnOrder[turnIndex];
        auto player = players[playerId];
        int rollValue = dice->roll();

        cout << player->getName() << " rolled a " << rollValue << "\n";
        int newPos = board->movePlayer(playerId, rollValue);

        if (newPos == board->getSize()) {
            cout << "🎉 " << player->getName() << " won the game!\n";
            exit(0); // End game
        }

        turnIndex = (turnIndex + 1) % turnOrder.size();
    }
};

// ==================== Main ====================
int main() {
    try {
        GameController game(30, 6);

        auto p1 = PlayerFactory::createPlayer(PLAYER::HUMAN, "Alice", 1);
        auto p2 = PlayerFactory::createPlayer(PLAYER::BOT, "Bot_1", 2);

        game.addPlayer(p1);
        game.addPlayer(p2);

        game.addJump(JumpFactory::createJump(JUMP::LADDER, 3, 22));
        game.addJump(JumpFactory::createJump(JUMP::SNAKE, 25, 5));

        cout << "\n=== Game Start ===\n";
        while (true) {
            game.playTurn();
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}
