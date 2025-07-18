#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>


using namespace std;




class Vehicle{
    public : 
        virtual string type() = 0;
        virtual ~Vehicle() = default;
};
class Car : public Vehicle{
    public : 
        string type(){
            return "Car";
        };
};
class Truck : public Vehicle{
    public : 
        string type(){
            return "Truck";
        };
};
class Bike : public Vehicle{
    public : 
        string type(){
            return "Bike";
        };
};
class CreateParkingLot {
    protected : 
        vector<vector<int>>parkingVector;
        map<string,pair<int,int>>parkingId;
        map<pair<int,int>,Vehicle*>parkingVehicle;

        string generateID() {
            static int counter = 1;
            return "ID" + to_string(counter++);
        }

    public : 
        void create_parking_lot(string ParkID, int floor,int slot){
            for(int i = 0;i<floor;i++){
                vector<int>v;
                for(int j = 0;j<slot;j++){
                    if(j==0) v.push_back(1);
                    else if(j<=2)v.push_back(2);
                    else v.push_back(3);
                }
                parkingVector.push_back(v);
            }
        }
        string park_vehicle(string vehicelType , string regNo, string color){
            
        }

};