#include<iostream>
using namespace std;

class DisplayDevice{
    public : 
        void displayTemp(int temp){
            cout<<"current temp is :- " << temp<<endl;
        }
};

class WeatherStation{
    private : 
       int temperature;
       DisplayDevice dd;
    public : 
        WeatherStation(DisplayDevice dd) : dd(dd){};
        void setTemp(int temp){
            this->temperature = temp;
            notify();
        }
        void notify(){
            dd.displayTemp(temperature);
        }
};

int main(){
    DisplayDevice mobile;
    WeatherStation ws(mobile);
    ws.setTemp(34);
    ws.setTemp(44);
    ws.setTemp(54);
    return 0;
}
