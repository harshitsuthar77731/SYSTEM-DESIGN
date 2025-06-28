// Your current code violates the Strategy Principle because:
// 	•	Drive behavior is hardcoded in each subclass, causing code duplication
// 	•	There’s no reusability, as the same logic (like "sports vehicle") is repeated
// 	•	It’s tightly coupled, making it hard to extend or change behavior without modifying or duplicating classes
// 	•	You cannot change drive behavior at runtime, which limits flexibility

// Using the Strategy Pattern solves all this by separating behavior into independent, reusable classes that can be plugged in dynamically.


#include <string>
#include <iostream>
using namespace std;

class Vehicle {
public: 
    virtual string drive() {
        return "simple drivebility";
    }
    virtual ~Vehicle() = default;
};

class sportsVehicle : public Vehicle{
    public: 
        string drive() override{
            return "sports vehicle";
        }
};

class passengerVehicle : public Vehicle{
};

class goodsVehicle : public Vehicle{
    public: 
        string drive() override{
            return "sports vehicle";
        }
};


int main(){
    Vehicle *gv = new goodsVehicle();
    Vehicle *sv = new sportsVehicle();
    Vehicle *pv = new passengerVehicle();

    cout<<gv->drive()<<endl<<pv->drive()<<endl<<sv->drive();

    delete gv;
    delete sv;
    delete pv;
    return 0;

}