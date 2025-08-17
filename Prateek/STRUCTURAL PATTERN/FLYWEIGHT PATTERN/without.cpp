#include<iostream>
#include<string>
using namespace std;

class Bullet {
    private :
        string color;
        int x,y;
        int velocity;
    public :
        Bullet(string color,int x,int y,int velocity):color(color),x(x),y(y),velocity(velocity){
            cout<<"creating bullet at (" <<x<<","<<y<<")at velocity "<<velocity<< "and color is"<<color<<endl;
        };
};


int main(){
    // creating overhead 
    for(int i= 0;i<5;i++){
        new Bullet("red",i*10,i*12,20);
    }
     for(int i= 0;i<5;i++){
        new Bullet("Green",i*10,i*12,20);
    }
}