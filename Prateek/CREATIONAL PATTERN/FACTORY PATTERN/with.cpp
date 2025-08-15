#include<iostream>
#include<string>
#include<memory>


using namespace std;
enum VEHICLE { BUS, CAR };
class Transport{
    public : 
        virtual void drive() = 0;
        virtual ~Transport() = default;
};

class Car : public Transport{
    public :
        void drive() override{
            cout<<"Driving a car"<<endl;
        }
};
class Bus : public Transport{
    public :
        void drive() override{
            cout<<"Driving a Bus"<<endl;
        }
};

class VehicleFactory{
    public :
        shared_ptr<Transport> createVehicle(VEHICLE vehicle){
            switch (vehicle)
            {
                case CAR:
                    return make_shared<Car>();
                case BUS:
                    return make_shared<Bus>();
                default:
                    throw invalid_argument("Vehicle not defined yet");
            }
        }
};

int main(){
    shared_ptr<VehicleFactory>vf = make_shared<VehicleFactory>();
    shared_ptr<Transport> vehicle = vf->createVehicle(BUS);
    vehicle->drive();
    vehicle = vf->createVehicle(CAR);
    vehicle->drive();

}