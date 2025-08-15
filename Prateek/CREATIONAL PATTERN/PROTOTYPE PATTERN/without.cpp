#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GamePiece{
    private :
        string color;
        string position;
    public :
        GamePiece(string color,string position):color(color),position(position){};
        string getColor(){
            return color;
        }
        string getPosition(){
            return position;
        }
        void setPosition(string input){
            this->position = input;
        }
        void setColor(string input){
            this->color = input;
        }
};

class GameBoard{
    private :
        vector<GamePiece*>gp;
    public :
        void addPiece(GamePiece* piece){
            gp.push_back(piece);
        }
        void printPosition(){
            for(auto elem : gp){
                cout<<"color:- "<<elem->getColor()<<" "<<"position:-"<<elem->getPosition()<<endl;
            }
        }
        vector<GamePiece*> getPiece(){
            return this->gp;
        }
};

int main(){
    GameBoard *board = new GameBoard();
    board->addPiece(new GamePiece("Red","1"));
    board->addPiece(new GamePiece("Blue","4"));
    board->printPosition();
    GameBoard *copied = new GameBoard();
    for(auto elem : board->getPiece()){
        copied->addPiece(new GamePiece(elem->getColor(),elem->getPosition()));
    }
    cout<<"copied"<<endl;
    copied->printPosition();

}