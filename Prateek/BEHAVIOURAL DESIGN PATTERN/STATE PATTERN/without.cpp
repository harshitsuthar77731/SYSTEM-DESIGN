#include <string>
#include <vector>
#include <iostream>
using namespace std;

enum TransportationMode {
    BUS,
    CAR,
    CYCLE,
    WALK
}; 

class DirectionService{
    private :
        TransportationMode mode;
    public :
        DirectionService(TransportationMode mode) : mode(mode){};
        void setMode(TransportationMode mode){
            this->mode = mode;
        }
        void eta(){
            switch(mode){
                case BUS:
                    cout<<"will take 2 days"<<endl;
                    break;
                case CAR:
                    cout<<"will take 1 days"<<endl;
                    break;
                case CYCLE:
                    cout<<"will take 4 days"<<endl;
                    break;
                case WALK:
                    cout<<"will take 10 days"<<endl;
                    break;
            }
        }
};

int main(){
    DirectionService *obj = new DirectionService(BUS);
    obj->eta();
    obj->setMode(CYCLE);
    obj->eta();
}