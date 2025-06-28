#include <iostream>
#include <string>
using namespace std;
// ---------- Step 1: Strategy Interface ----------
class DriveStrategy {
    public : 
        virtual string drive() = 0;
        virtual ~DriveStrategy() = default;
};

// ---------- Step 2: Concrete Drive Strategies if new required add in it---------- 

class NormalDrive : public DriveStrategy{
    public :
        string drive() override{
            return "Normal Drive ability";
        }
};

class SportsDrive : public DriveStrategy{
    public :
        string drive() override{
            return "Sports Drive ability";
        }
};

class OffRoadDrive : public DriveStrategy{
    public :
        string drive() override{
            return "Off road Drive ability";
        }
};

// ---------- Step 3: Vehicle Base Class using Strategy ----------

class Vehicle {
    protected :
        DriveStrategy* strategy;
    public :
        Vehicle(DriveStrategy* strat){
            strategy = strat;
        }
        virtual string drive(){
            return strategy->drive();
        }

        string start(){
            return "vehicle is started";
        }

        ~Vehicle() = default;
};

class GoodsVehicle : public Vehicle {
    public :
    // “While calling the GoodsVehicle constructor, I am explicitly calling the Vehicle base class constructor and telling it to initialize with the NormalDrive strategy.”
        GoodsVehicle() : Vehicle(new OffRoadDrive()) {
            cout<<"vehicle created"<<endl;
        };

};
class PassengerVehicle : public Vehicle{
    public :
    PassengerVehicle() : Vehicle(new NormalDrive()) {
            cout<<"vehicle created"<<endl;
        };
};
class SportsVehicle : public Vehicle{
    public :
    SportsVehicle() : Vehicle(new SportsDrive()) {
            cout<<"vehicle created"<<endl;
        };
};



int main(){
    
}