#include <iostream>
#include <map>

using namespace std;

enum SpotType {COMPACT,LARGE,MOTORCYCLE};

class Vehicle{
    public :
        virtual int getVehicleNumber() = 0;
        virtual SpotType getVehicleType() = 0;
        virtual ~Vehicle() = default;
};

class Car : public Vehicle{
    private :
        int vehicleNumber;
        SpotType spotType = COMPACT;
    public :    
        Car(int vehicleNumber) : vehicleNumber(vehicleNumber) {};
        int getVehicleNumber() override{ return this->vehicleNumber;};
        SpotType getVehicleType() override{ return this->spotType;};
};

class Bike : public Vehicle{
    private :
        int vehicleNumber;
        SpotType spotType = MOTORCYCLE;
    public :    
        Bike(int vehicleNumber) : vehicleNumber(vehicleNumber) {};
        int getVehicleNumber() override{ return this->vehicleNumber;};
        SpotType getVehicleType() override{ return this->spotType;};
};

class Truck : public Vehicle{
    private :
        int vehicleNumber;
        SpotType spotType = LARGE;
    public :    
        Truck(int vehicleNumber) : vehicleNumber(vehicleNumber) {};
        int getVehicleNumber() override{ return this->vehicleNumber;};
        SpotType getVehicleType() override{ return this->spotType;};
};

class VehicleFactory {
    public :
        shared_ptr<Vehicle> createVehicle(SpotType type,int number){
            switch (type)
            {
            case COMPACT:
                return make_shared<Car>(number);
                break;
            case LARGE:
                return make_shared<Truck>(number);
                break;
            case MOTORCYCLE:
                return make_shared<Bike>(number);
                break;
            default:
                throw invalid_argument("No spot type defined for creation as you mentioned\n");
                break;
            }
        }   
};

class Spot{
    private : 
        int spotId;
        SpotType type;
        bool isOccupied = false;
    public :
        Spot(int spotId, SpotType type) :spotId(spotId) ,type(type){};
        bool getStatus(){
            return this->isOccupied;
        }
        void occupy(){
            this->isOccupied = true;
        }
        void release(){
            this->isOccupied = false;
        }
        int getSpotId(){
            return this->spotId;
        }
        SpotType getSpotType(){
            return this->type;
        }
};

class Floor{
    private :
        unordered_map<SpotType,int> spotList;
        int floorNumber;
        unordered_map<SpotType,unordered_map<int,shared_ptr<Spot>>> spotIdList;
    public :
        Floor(int floorNumber , unordered_map<SpotType,int> spotAndQuantity): floorNumber(floorNumber) {
            this->spotList = spotAndQuantity;
            int id = 0;
            for(auto &[key,val] : spotAndQuantity){
                for(int i = 0;i<val;i++){
                    shared_ptr<Spot> spot = make_shared<Spot>(id,key);
                    spotIdList[key][id] = spot;
                    id++;
                }
            }
        };
        const unordered_map<SpotType,int>&  getFloorList() const{
            return spotList;
        }
        bool isSpotAvailable(SpotType type){
            if(spotList.count(type)){
                if(spotList[type]>0){
                    return true;
                }return false;
            }else{
                throw invalid_argument("No spot with this type exist at this floor");
            }
        }
        int getFLoorNumber(){
            return this->floorNumber;
        }
        int occupySpot(SpotType type){
            spotList[type]--;
            for(auto &[key,val] : spotIdList[type]){
                if(!val->getStatus()){
                    val->occupy();
                    return val->getSpotId();
                }
            }
            return -1;
        }
        void freeSpot(SpotType type, int id){
            if(spotIdList.count(type)){
                if(spotIdList[type].count(id)){
                    if(spotIdList[type][id]->getStatus()){
                        spotIdList[type][id]->release();
                        spotList[type]++;
                    }else{
                        throw invalid_argument("No spot occupied / exist with this type and id\n");
                    }
                }else{
                    throw invalid_argument("No spot exist with this type of id\n");
                }
            }else{
                    throw invalid_argument("No spot exist with this type\n");
                }
        }
};

class ParkingLot{
    private :
        ParkingLot() {} // private constructor
        ParkingLot(const ParkingLot&) = delete;
        ParkingLot& operator=(const ParkingLot&) = delete;
        int maxFloor = 1;
        map<int , shared_ptr<Floor>>floorList;
    public :
         static ParkingLot& getInstance() {
            static ParkingLot instance;  // created once, thread-safe in C++11+
            return instance;
        }
        bool addFloor(shared_ptr<Floor> floor){
            if(floorList.count(floor->getFLoorNumber())){
                throw invalid_argument("This Floor already exist\n");
            }else{
                if(floor->getFLoorNumber()>maxFloor){
                    throw invalid_argument("No Intermediate Floor available to support that floor\n");
                }else{
                    floorList[floor->getFLoorNumber()] = floor;
                    maxFloor++;
                    return true;
                }
            }
        }
        void availableSpots(){
            for(auto &[key,val] : floorList){
                int floorNumber = key;
                cout<<"On floor number :- " << floorNumber<<endl;
                for(auto &[type,available] : val->getFloorList()){
                    cout<<"For Spot Type "<<type<<" availability :- "<<available<<endl;
                }
            }
        }
        std::tuple<int,int> occupyNearestFloor(SpotType type){
            for(auto &[key,val] : floorList){
                int floorNumber = key;
                if(val->isSpotAvailable(type)){
                    int spotId = val->occupySpot(type);
                    return {spotId,floorNumber};
                }
            }
            throw runtime_error("No Spot Exist at any floor\n");
            return {-1,-1};
        }
        bool releaseSpot(SpotType type, int id,int floorNumber){
            if(floorList.count(floorNumber)){
                shared_ptr<Floor>& floor = floorList.at(floorNumber);
                floorList[floorNumber]->freeSpot(type,id);
                return true;
            }
            return false;
        }
        void removeFloor(int floorNumber){
            if(floorNumber==maxFloor-1){
                floorList.erase(floorNumber);
            }else{
                throw invalid_argument("You can't remove intermediate Floor\n");
            }
        }
        const shared_ptr<Floor>& getFloor(int floorNumber) const{
            if(floorList.count(floorNumber)){
                return floorList.at(floorNumber);
            }else{
                throw invalid_argument("No floor number exist with this number\n");
            }
        }   

};

class Ticket{
    private : 
        static int counter;
        int ticketId;
        int spotId;
        int floor;
        int vehicleNumber;
        SpotType spotType;
        std::chrono::system_clock::time_point entryTime;
    public :
        Ticket(int spotId,int floor,int vehicleNumber,SpotType spotType,std::chrono::system_clock::time_point entryTime) :spotId(spotId),floor(floor),vehicleNumber(vehicleNumber),spotType(spotType),entryTime(entryTime) {
            ticketId = counter;
            counter++;
        }
        int getId(){
            return this->ticketId;
        }
        int getVehicleNumber(){
            return this->vehicleNumber;
        }
        int getFloorNumber(){
            return this->floor;
        }
        int getSpotId(){
            return this->spotId;
        }
        SpotType getSpotType(){
            return this->spotType;
        }
        std::chrono::system_clock::time_point getEntryTime(){
            return this->entryTime;
        }

};
int Ticket::counter = 0;

class PriceCalculator{
    private :
        unordered_map<SpotType,double> priceList;
    public :
        PriceCalculator(unordered_map<SpotType,double> priceList) : priceList(priceList){};
        int getHourDifferenceRoundedUp(std::chrono::system_clock::time_point start,std::chrono::system_clock::time_point end) {
        using namespace std::chrono;
            auto diff = duration_cast<minutes>(end - start).count(); // total minutes
            int hours = diff / 60;
            if (diff % 60 != 0) { // if leftover minutes, round up
                hours += 1;
            }
            return hours;
        }
        double calculatePrice(SpotType type, std::chrono::system_clock::time_point entryTime,std::chrono::system_clock::time_point exitTime){
            if(!priceList.count(type)){
                throw invalid_argument("No spot type exist in price list");
            }else{
                return getHourDifferenceRoundedUp(entryTime,exitTime)*priceList[type];
            }
        }
};


class ParkingManager{
    private : 
        ParkingLot& parkingLot;
        shared_ptr<PriceCalculator> priceCalculator;
        double netRevenue = 0;
    public :
        ParkingManager(unordered_map<SpotType,double> priceList): parkingLot(ParkingLot::getInstance()) {
            priceCalculator = make_shared<PriceCalculator>(priceList);
        }
        shared_ptr<Ticket> getSpot(shared_ptr<Vehicle> vehicle,std::chrono::system_clock::time_point entryTime){
            auto [spotId, floorNumber] = parkingLot.occupyNearestFloor(vehicle->getVehicleType());
            if(spotId!=-1){
                // (int spotId,int floor,int vehicleNumber,SpotType spotType,std::chrono::system_clock::time_point entryTime
                shared_ptr<Ticket> ticket = make_shared<Ticket>(spotId,floorNumber,vehicle->getVehicleNumber(),vehicle->getVehicleType(),entryTime);
                return ticket;
            }else{
                throw runtime_error("No spot Available\n");
            }
        }
        double freeSpot(shared_ptr<Ticket> ticket,std::chrono::system_clock::time_point exitTime ){
            double revenue = priceCalculator->calculatePrice(ticket->getSpotType(),ticket->getEntryTime(),exitTime);
            if(parkingLot.releaseSpot(ticket->getSpotType(),ticket->getSpotId(),ticket->getFloorNumber())){
                this->netRevenue+=revenue;
                return revenue;
            }else{
                throw runtime_error("No floor number exist with this number\n");
            }
        }
        ParkingLot& getParkingLot(){
            return this->parkingLot;
        }

};
#include <thread>
#include <chrono>

int main() {
    try {
        // Setup price list
        unordered_map<SpotType,double> priceList = {
            {COMPACT, 50.0},
            {LARGE, 100.0},
            {MOTORCYCLE, 30.0}
        };

        // Setup floors
        auto floor1 = make_shared<Floor>(1, unordered_map<SpotType,int>{{COMPACT,2},{MOTORCYCLE,1}});
        auto floor2 = make_shared<Floor>(2, unordered_map<SpotType,int>{{LARGE,1}});

         // Manager
        ParkingManager manager(priceList);

        ParkingLot& lot = manager.getParkingLot();
        lot.addFloor(floor1);
        lot.addFloor(floor2);

       

        // Create vehicles
        auto car1 = make_shared<Car>(101);
        auto bike1 = make_shared<Bike>(202);

        // Car enters
        auto entryTimeCar = chrono::system_clock::now();
        auto ticketCar = manager.getSpot(car1, entryTimeCar);

        // Bike enters
        auto entryTimeBike = chrono::system_clock::now();
        auto ticketBike = manager.getSpot(bike1, entryTimeBike);

        // Show available spots
        lot.availableSpots();

        // Sleep 2h10m simulated (for price testing)
        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulation shortcut
        auto exitTimeCar = entryTimeCar + std::chrono::minutes(130);
        auto exitTimeBike = entryTimeBike + std::chrono::minutes(45);

        // Free spots
        double revenueCar = manager.freeSpot(ticketCar, exitTimeCar);
        double revenueBike = manager.freeSpot(ticketBike, exitTimeBike);

        cout << "Car Revenue: " << revenueCar << endl;
        cout << "Bike Revenue: " << revenueBike << endl;

        lot.availableSpots();

    } catch(const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
