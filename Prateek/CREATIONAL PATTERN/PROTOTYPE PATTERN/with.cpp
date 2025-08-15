#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <typename T>
class Prototype{
    public :
    virtual T clone() = 0;
    virtual ~Prototype() = default;
};


class GamePiece : public Prototype<GamePiece*>{
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
        GamePiece* clone() override{
            return new GamePiece(this->color,this->position);
        };
};

class GameBoard : public Prototype<GameBoard*>{
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
        GameBoard* clone(){
            GameBoard *newBoard = new GameBoard;
            for(auto elem :gp){
                newBoard->addPiece(elem->clone());
            }
            return newBoard;
        };
};

int main(){
    GameBoard *board = new GameBoard();
    board->addPiece(new GamePiece("Red","1"));
    board->addPiece(new GamePiece("Blue","4"));
    board->printPosition();
    GameBoard *copied = board->clone();
    cout<<"copied"<<endl;
    copied->printPosition();

}