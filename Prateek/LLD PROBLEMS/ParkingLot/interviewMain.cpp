#include <iostream>
#include <map>
#include <memory>
#include <chrono>
#include <stdexcept>
using namespace std;
using namespace std::chrono;

enum SpotType { COMPACT, LARGE, MOTORCYCLE };

class Vehicle {
public:
    virtual SpotType getType() = 0;
    virtual string getNumber() = 0;
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
    string number;
public:
    Car(string n): number(n) {}
    SpotType getType() override { return COMPACT; }
    string getNumber() override { return number; }
};

class Bike : public Vehicle {
    string number;
public:
    Bike(string n): number(n) {}
    SpotType getType() override { return MOTORCYCLE; }
    string getNumber() override { return number; }
};

class Spot {
    int id; SpotType type; bool free;
public:
    Spot(int id, SpotType t): id(id), type(t), free(true) {}
    bool isFree() { return free; }
    void occupy() { free = false; }
    void release() { free = true; }
    SpotType getType() { return type; }
    int getId() { return id; }
};

class Ticket {
    string vehicleNo;
    time_point<system_clock> entry;
    int spotId;
public:
    Ticket(string v, int s): vehicleNo(v), spotId(s) {
        entry = system_clock::now();
    }
    double calculatePrice() {
        auto exit = system_clock::now();
        auto hours = duration_cast<hours>(exit - entry).count() + 1;
        return hours * 20.0; // flat 20/hr
    }
    string getVehicleNo() { return vehicleNo; }
    int getSpotId() { return spotId; }
};

class ParkingLot {
    map<int, shared_ptr<Spot>> spots;
public:
    ParkingLot() {
        spots[1] = make_shared<Spot>(1, COMPACT);
        spots[2] = make_shared<Spot>(2, MOTORCYCLE);
    }
    shared_ptr<Spot> findSpot(SpotType t) {
        for (auto &p : spots)
            if (p.second->isFree() && p.second->getType() == t)
                return p.second;
        throw runtime_error("No spot available");
    }
    void releaseSpot(int id) { spots[id]->release(); }
};

class ParkingManager {
    shared_ptr<ParkingLot> lot;
    double revenue = 0.0;
public:
    ParkingManager(shared_ptr<ParkingLot> l): lot(l) {}
    shared_ptr<Ticket> park(shared_ptr<Vehicle> v) {
        auto spot = lot->findSpot(v->getType());
        spot->occupy();
        return make_shared<Ticket>(v->getNumber(), spot->getId());
    }
    void unpark(shared_ptr<Ticket> t) {
        double price = t->calculatePrice();
        revenue += price;
        lot->releaseSpot(t->getSpotId());
        cout << "Vehicle " << t->getVehicleNo()
             << " exited. Charge: " << price << "\n";
    }
    double getRevenue() { return revenue; }
};

int main() {
    auto lot = make_shared<ParkingLot>();
    ParkingManager manager(lot);

    auto car = make_shared<Car>("KA01AB1234");
    auto ticket = manager.park(car);
    cout << "Car parked at spot " << ticket->getSpotId() << "\n";

    manager.unpark(ticket);
    cout << "Total revenue: " << manager.getRevenue() << "\n";
}