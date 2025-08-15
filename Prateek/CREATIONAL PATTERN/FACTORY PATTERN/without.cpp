#include<iostream>
#include<string>

using namespace std;

class Transport{
    public : 
        virtual void drive() = 0;
        virtual ~Transport() = default;
};

class Car : public Transport{
    public :
        void drive(){
            cout<<"Driving a car";
        }
};
class Bus : public Transport{
    public :
        void drive(){
            cout<<"Driving a Bus";
        }
};

int main(){
    Transport *car = new Car();
    Transport *bus = new Bus();
    car->drive();
    bus->drive();

}