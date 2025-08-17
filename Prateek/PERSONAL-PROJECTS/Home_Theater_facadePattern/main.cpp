#include<iostream>
#include<string>
using namespace std;


class Amplifier{
    public :
        void turnOnAmplifier(){
            cout<<"Amplifier is turned on"<<endl;
        }
        void turnOffAmplifier(){
            cout<<"Amplifier is turned off"<<endl;
        }
};
class Light{
    public :
        void dimmingLight(){
            cout<<"Light is dimming"<<endl;
        }
        void turnOnLight(){
            cout<<"Turning on light"<<endl;
        }
};
class Screen{
    public :
        void lowerScreen(){
            cout<<"Screen is coming down"<<endl;
        }
        void raiseScreen(){
            cout<<"Screen is raising"<<endl;
        }
};
class PopcornMaker{
    public :
        void turnOnPopcornMaker(){
            cout<<"Pop corn maker is on"<<endl;
        }
        void turnOffPopcornMaker(){
            cout<<"Pop corn maker is off"<<endl;
        }
};
class Projector{
    public :
        void turnOnProjector(){
            cout<<"Projector is turned on"<<endl;
        }
        void turnOffProjector(){
            cout<<"Turning Off projector"<<endl;
        }
};
class DVDPlayer{
    public :
        void startDVD(string movie){
            cout<<"Playing movie "<<movie<<endl;
        }
        void stopPlaying(){
            cout<<"Stop Playing"<<endl;
        }
};

class HomeTheaterFacade{
    private :
        shared_ptr<Amplifier> amp;
        shared_ptr<DVDPlayer> dvdp;
        shared_ptr<Projector> proj;
        shared_ptr<PopcornMaker> popm;
        shared_ptr<Screen> scr;
        shared_ptr<Light> lit;
    public :
        HomeTheaterFacade(){
            amp = make_shared<Amplifier>();
            dvdp = make_shared<DVDPlayer>();
            proj = make_shared<Projector>();
            popm = make_shared<PopcornMaker>();
            scr = make_shared<Screen>();
            lit = make_shared<Light>();
        }
        void watchMovie(string movieName){
            lit->dimmingLight();
            scr->lowerScreen();
            proj->turnOnProjector();
            amp->turnOnAmplifier();
            dvdp->startDVD(movieName);
            popm->turnOnPopcornMaker();
        }
         void endMovie(){
            amp->turnOffAmplifier();
            dvdp->stopPlaying();
            proj->turnOffProjector();
            scr->raiseScreen();
            lit->turnOnLight();
            popm->turnOffPopcornMaker();

        }

};

int main(){
    shared_ptr<HomeTheaterFacade>ht = make_shared<HomeTheaterFacade>();
    ht->watchMovie("Inception");
    ht->endMovie();

}
