#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Player{
    public : 
        virtual string getName() = 0;
        virtual char getSign() = 0;
        virtual ~Player() = default;
};


class Piece{
    private :
        char sign;
    public :
        Piece(char sign) : sign(sign){};
        char getSign(){ return sign;};
};


class GameBoard{
    private :
        int boardSize;
        vector<vector<char>> board;
    public :
        GameBoard(int size){
            for(int i = 0;i<size;i++){
                vector<char> vs;
                for(int j = 0;j<size;j++){
                    vs.push_back('.');
                }
                board.push_back(vs);
            }
        }
        bool placePiece(int row, int col, char symbol) {
            if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size())
                throw invalid_argument("Invalid coordinates");
            if (board[row][col] != '.')
                throw invalid_argument("Cell already occupied");
            board[row][col] = symbol;
            return true;
        }
    
        const vector<vector<char>>& getBoard() const{
            return board;
        }

};

class Human:public Player{
    private : 
        string name;
        shared_ptr<Piece>piece;
    public :
        Human(string name , char sign){
            this->name =name;
            piece = make_shared<Piece>(sign);
        }
        string getName() {return name;};
        char getSign() {return piece->getSign();};
};


class GameController{
    private :
        int size;
        shared_ptr<GameBoard> board;
        int currentSeq = 0;
        vector<shared_ptr<Player>> players;
        unordered_map<char,shared_ptr<Player>>playerPieceMap;
    public :
        GameController(int size){
            this->size = size;
            board = make_shared<GameBoard>(size);
        }
        void addPlayer(shared_ptr<Player> plr){
            if(playerPieceMap.count(plr->getSign())){
                cout<<"player with this sign is already assigned \n";
                return;
            }else{
                playerPieceMap[plr->getSign()] = plr;
                players.push_back(plr);
            }
        }
        bool isFull() const{
            const vector<vector<char>> &board = this->board->getBoard();
            for(auto row : board){
                for(auto col : row){
                    if(col == '.') return false;
                }
            }
            return true;
        }
        bool checkWinner(char player) const{
            const vector<vector<char>> &board = this->board->getBoard();
            int n = board.size();

            // Check rows and cols
            for (int i = 0; i < n; i++) {
                bool rowWin = true, colWin = true;
                for (int j = 0; j < n; j++) {
                    if (board[i][j] != player) rowWin = false;
                    if (board[j][i] != player) colWin = false;
                }
                if (rowWin || colWin) return true;
            }

            // Check diagonals
            bool diag1 = true, diag2 = true;
            for (int i = 0; i < n; i++) {
                if (board[i][i] != player) diag1 = false;
                if (board[i][n - 1 - i] != player) diag2 = false;
            }
            return diag1 || diag2;
        }
        void checkDraw() const{
            if(!isFull()){
                throw invalid_argument("Board is not fully filled yet");
            }
            for(auto &[sign,plr] : playerPieceMap){
                if(checkWinner(sign)){
                    cout<<plr->getName()<<" "<<"has won the game hurray \n"<<endl;
                    return;
                }
            }
            cout<<"Match is draw \n";
        }
        void checkWin() const{
            for(auto &[sign,plr] : playerPieceMap){
                if(checkWinner(sign)){
                    cout<<plr->getName()<<" "<<"has won the game hurray \n"<<endl;
                    return;
                }
            }
            cout<<"No winner yet \n";
        }

        void makeMove(int x,int y){
            if(board->placePiece(x,y,players[currentSeq]->getSign())){
                currentSeq++;
                currentSeq =  currentSeq%players.size();
            }
        }
};

int main() {
    // Create a game controller for 3x3 board
    GameController game(3);

    // Create players
    shared_ptr<Player> p1 = make_shared<Human>("Alice", 'X');
    shared_ptr<Player> p2 = make_shared<Human>("Bob", 'O');

    // Add players
    game.addPlayer(p1);
    game.addPlayer(p2);

    // Print empty board
    cout << "Initial Board:" << endl;
    game.makeMove(0, 0); // Alice -> X
    game.makeMove(0, 1); // Bob -> O
    game.makeMove(1, 1); // Alice -> X
    game.makeMove(0, 2); // Bob -> O
    game.makeMove(2, 2); // Alice -> X -> should win

    cout << "Board after moves:" << endl;
    game.checkDraw(); // Should declare Alice winner

    // Test invalid move (out of bounds)
    try {
        game.makeMove(3, 3);
    } catch (exception &e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    // Test invalid move (already filled cell)
    try {
        game.makeMove(0, 0);
    } catch (exception &e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    // Test draw case
    GameController drawGame(3);
    shared_ptr<Player> p3 = make_shared<Human>("Charlie", 'X');
    shared_ptr<Player> p4 = make_shared<Human>("Dave", 'O');
    drawGame.addPlayer(p3);
    drawGame.addPlayer(p4);

    // Fill board to draw
    drawGame.makeMove(0,0); // X
    drawGame.makeMove(0,1); // O
    drawGame.makeMove(0,2); // X
    drawGame.makeMove(1,0); // O
    drawGame.makeMove(1,2); // X
    drawGame.makeMove(1,1); // O
    drawGame.makeMove(2,0); // X
    drawGame.makeMove(2,2); // O
    drawGame.makeMove(2,1); // X

    cout << "Checking for draw:" << endl;
    drawGame.checkWin(); // Should print draw

    // Test win case

    GameController winGame(3);
    shared_ptr<Player> p5 = make_shared<Human>("Harshit", 'X');
    shared_ptr<Player> p6 = make_shared<Human>("james", 'O');
    winGame.addPlayer(p5);
    winGame.addPlayer(p6);

    // Fill board to draw
    winGame.makeMove(0,0); // X
    winGame.makeMove(1,0); // O
    winGame.makeMove(0,1); // X
    winGame.makeMove(1,1); // O
    winGame.makeMove(0,2); // X

    cout << "Checking for draw:" << endl;
    winGame.checkWin(); // Should print draw
    
}
