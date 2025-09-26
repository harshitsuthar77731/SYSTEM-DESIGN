#include<iostream>
#include<unordered_set>

using namespace std;


enum PLAYER { HUMAN, BOT };
enum JUMP { LADDER, SNAKE };

class Jump{
    public :
        virtual int getInward() const= 0;
        virtual int getOutward() const = 0;
        virtual ~Jump() = default;
};

class Ladder : public Jump{
    private :
        int inward;
        int outward;
    public :    
        Ladder(int in,int out):inward(in),outward(out){
            cout<<"Ladder is created \n";
        };
        int getInward() const override{return this->inward;};
        int getOutward() const override{return this->outward;};
};
class Snake : public Jump{
    private :
        int inward;
        int outward;
    public :    
        Snake(int in,int out):inward(in),outward(out){
            cout<<"Snake is created \n";
        };
        int getInward() const override{return this->inward;};
        int getOutward() const override{return this->outward;};
};

class JumpFactory{
    public :
        shared_ptr<Jump> createJump(JUMP jump,int inward,int outward){
            switch (jump)
            {
                case SNAKE:
                    return make_shared<Snake>(inward,outward);
                    break;
                case LADDER:
                    return make_shared<Ladder>(inward,outward);
                    break;
                default:
                    break;
            }
        }
};

class Player{
    public :
        virtual int getPosition() const= 0;
        virtual int getId() const= 0;
        virtual string getName() const= 0;
        virtual void setPosition(int position) = 0;
        virtual ~Player() = default;
};

class Human : public Player{
    private : 
        string name;
        int position = 0;
        int id;
    public :
        Human(string name,int id){
            this->name = name;
            this->id = id;
            cout<<"New player created \n";
        }
        int getPosition()const override {
            return this->position;
        };
        int getId()const override {
            return this->id;
        };
        string getName()const override{
            return this->name;
        }
        void setPosition(int position)  override{
            this->position = position;
        };

};

class Bot : public Player{
    private : 
        string name;
        int position = 0;
        int id;
    public :
        Bot(string name,int id){
            this->name = name;
            this->id = id;
            cout<<"New bot created \n";
        }
        int getPosition()const override {
            return this->position;
        };
        int getId()const override{
            return this->id;
        };
        string getName()const override{
            return this->name;
        }
        void setPosition(int position)  override{
            this->position = position;
        };
};

class PlayerFactory{
    public :
        shared_ptr<Player> createPlayer(PLAYER player,string name,int id){
            switch (player)
            {
                case HUMAN:
                    return make_shared<Human>(name,id);
                    break;
                case BOT:
                    return make_shared<Bot>(name,id);
                    break;
                default:
                    break;
            }
        }
};


class Dice{
    private :
        vector<int>dice;
    public :
        Dice(int limit){
            for(int i = 0;i<limit;i++){
                dice.push_back(i+1);
            }
        }
        
        int rollMe() {
            int idx = rand() % dice.size();  // pick random index
            return dice[idx];
        }
};

class Board{
    private :
        int boardSize;
        unordered_map<int,vector<int>>playerMap;
        unordered_map<int,int>jumpMap;
        unordered_set<int> usedOutward;
    public :    
        Board(int size){
            this->boardSize = size;
        }
        int getSize(){
            return this->boardSize;
        }
        int updatePlayerPosition(int position, int move, int id) {
        int newPos = position + move;

        if (newPos > boardSize) {
            newPos = boardSize; // clamp (your rule)
        }

        // collision rule: no two players on same cell
        for (auto &p : playerMap) {
            if (p.first == id) continue;
            if (!p.second.empty() && p.second.back() == newPos) {
                throw invalid_argument("Can't move: target cell occupied");
            }
        }

        // apply jump if any
        auto it = jumpMap.find(newPos);
        if (it != jumpMap.end()) newPos = it->second;

        playerMap[id].push_back(newPos);

        if (newPos == boardSize) {
            cout << "Player " << id << " reached the final cell!\n";
        } else {
            cout << "Player " << id << " moved to " << newPos << "\n";
        }
        return newPos;
    }

        bool addJump(shared_ptr<Jump> jump){
            int in = jump->getInward();
            int out = jump->getOutward();
            if (jumpMap.count(in) || usedOutward.count(out)) {
                return false;
            }
            jumpMap[in] = out;
            usedOutward.insert(out);

            return true;
        }
};


class GameController {
    private : 
        vector<int>PlayerList;
        unordered_map<int,shared_ptr<Player>>PlayerMap;
        shared_ptr<Dice> dice;
        shared_ptr<Board> board;
        int sequence = 0;
    public :
    GameController(int boardSize,int diceLimit){
        this->dice = make_shared<Dice>(diceLimit);
        this->board = make_shared<Board>(boardSize);
    }
    int rollDice(){
        return dice->rollMe();
    }
    void addPlayer(shared_ptr<Player> player){
        if(PlayerMap.count(player->getId())){
            cout<<"Player with Player Id exist \n";
            return;
        }
        PlayerMap[player->getId()] = player;
        PlayerList.push_back(player->getId());
        cout<<"Player added\n";
    }
    void addJump(shared_ptr<Jump> jump){
        this->board->addJump(jump);
    }
    
    void movePlayer(){
        try
        {
            if(PlayerList.size()==0){
                cout<<"No player to play game \n";
                return ;
            }

            sequence = sequence%PlayerList.size();
            int currenPlayerId =  PlayerList[sequence];
            int currentPosition = PlayerMap[currenPlayerId]->getPosition();
            int moves = rollDice();
            sequence++;
            int newPosition = board->updatePlayerPosition(currentPosition,moves,currenPlayerId);
            if(newPosition == board->getSize()){
                cout<<PlayerMap[currenPlayerId]->getName()<<" "<<"Won the game"<<endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
};

int main() {
    srand(time(0)); // seed for dice randomness

    // ✅ Setup Game
    GameController game(30, 6); // board size=30, dice limit=6

    // ✅ Create players
    shared_ptr<Player> p1 = make_shared<Human>("Alice", 1);
    shared_ptr<Player> p2 = make_shared<Bot>("Bot_1", 2);

    game.addPlayer(p1);
    game.addPlayer(p2);

    // ✅ Add jumps
    JumpFactory jf;
    game.addJump(jf.createJump(LADDER, 3, 22)); // ladder: 3 → 22
    game.addJump(jf.createJump(SNAKE, 25, 5));  // snake: 25 → 5

    cout << "\n=== Test Case 1: Ladder ===" << endl;
    cout << "\n=== Test Case 5: Turn Rotation ===" << endl;
    game.movePlayer(); // Alice
    game.movePlayer(); // Bot
    game.movePlayer(); // Alice again
}