#include<iostream>

using namespace std;
class Plane;

class TrafficMediator{
    public :
        virtual bool checkRunway() = 0;
        virtual void updateRunwayStatus(bool status) = 0;
        virtual void runWayStatusNotification() = 0;
        virtual void requestLanding() = 0;
        virtual void addFlight(shared_ptr<Plane> plane) = 0;
        virtual ~TrafficMediator() = default;
};

class Plane : public enable_shared_from_this<Plane>{
    private :
        string planeUUID;
        shared_ptr<TrafficMediator> Controller;
    public :
        Plane(string uuid,shared_ptr<TrafficMediator> Controller) : planeUUID(uuid),Controller(Controller){};
        void canLand(){
            Controller->runWayStatusNotification();
        }
        void requestLanding(){
            Controller->requestLanding();
        }
        void receiver(const string& msg){
            cout<<"Hi pilot of plane "<<this->getUUId()<<" "<<msg<<endl;
        }
        string getUUId(){
            return this->planeUUID;
        }
        

};
class AirTrafficController : public TrafficMediator{
    private : 
        shared_ptr<Plane> canland;
        bool runwayAvailable;
        vector<shared_ptr<Plane>> planeList;
    public :
        void addFlight(shared_ptr<Plane> plane){
            planeList.push_back(plane);
        }
        void updateRunwayStatus(bool status){
            this->runwayAvailable = status;
        }
        bool checkRunway(){
            return this->runwayAvailable;
        }
        void runWayStatusNotification(){
            if(checkRunway()){
                for(auto plane : planeList){
                    plane->receiver("You can land now");
                }
            }else{
                for(auto plane : planeList){
                    plane->receiver("You can't land now");
                }
            }
        }

        void requestLanding(){
              if(this->checkRunway()){
                for(auto plane : planeList){
                    canland = plane;
                    canland->receiver("You can land now");
                    planeList.erase(remove(planeList.begin(), planeList.end(), canland), planeList.end());
                    canland = nullptr;
                    break;
                }

            }
            updateRunwayStatus(false);
        }

};


int main(){
    shared_ptr<AirTrafficController> tm = make_shared<AirTrafficController>();
    shared_ptr<Plane> p1= make_shared<Plane>("1234",tm);
    shared_ptr<Plane> p2= make_shared<Plane>("1235",tm);
    shared_ptr<Plane> p3= make_shared<Plane>("1236",tm);
    shared_ptr<Plane> p4= make_shared<Plane>("1237",tm);
    tm->addFlight(p1);
    tm->addFlight(p2);
    tm->addFlight(p3);
    tm->addFlight(p4);
    tm->updateRunwayStatus(true);
    p1->canLand();
    p1->requestLanding();
    p2->canLand();
    tm->updateRunwayStatus(true);
    p2->canLand();
}