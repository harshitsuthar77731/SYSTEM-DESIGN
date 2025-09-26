#include<iostream>
using namespace std;

class DirectionService;
class TransportationInterface {
    public :
        virtual void handle(DirectionService *context) = 0;
        virtual int eta() = 0;
        virtual string getDirection() = 0;
        virtual ~TransportationInterface() = default;
};

class DirectionService{
    private : 
        shared_ptr<TransportationInterface> mode;
    public :
        DirectionService(shared_ptr<TransportationInterface> mode) : mode(mode){};
        void setMode(shared_ptr<TransportationInterface> mode){
            this->mode = mode;
        }
        int getEta(){
            cout<<"Calculating ETA"<<endl;
            return mode->eta();
        }
        string getDirection() {
            cout<<"Optimizing Route"<<endl;
            return mode->getDirection();
        }
        void request(){
            mode->handle(this);
        }
};

class CYCLE : public TransportationInterface {
    public :
        void handle(DirectionService *context){
            cout<<"No more mode switch possible"<<endl;
        }
        int eta() override{
            return 8;
        };
        string getDirection() override{
            return "Take left than take right than take cycle path for 40 km\n";
        };
};

class CAR : public TransportationInterface {
    public :
        void handle(DirectionService *context){
            context->setMode(make_shared<CYCLE>());
            cout<<"Switching mode from car to cycle"<<endl;
        }
        int eta() override{
            return 3;
        };
        string getDirection() override{
            return "Take left than take right than straight for 30 km\n";
        };
};


class BUS : public TransportationInterface {
    public :
        void handle(DirectionService *context){
            context->setMode(make_shared<CAR>());
            cout<<"Switching mode from bus to car\n"<<endl;
        }
        int eta() override{
            return 4;
        };
        string getDirection() override{
            return "Take left than take right than straight for 40 km\n";
        };
};



int main(){
    shared_ptr<DirectionService> ds = make_shared<DirectionService>(make_shared<BUS>());
    cout<<ds->getDirection();
    cout<<ds->getEta();

    ds->request();
    cout<<ds->getDirection();
    cout<<ds->getEta();

    ds->request();
    cout<<ds->getDirection();
    cout<<ds->getEta();


    ds->request();
    cout<<ds->getDirection();
    cout<<ds->getEta();

}