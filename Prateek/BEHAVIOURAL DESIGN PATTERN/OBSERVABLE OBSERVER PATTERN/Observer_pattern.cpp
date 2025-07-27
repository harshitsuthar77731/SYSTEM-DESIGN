#include<iostream>
#include<map>

using namespace std;

// making Observer interface
class Observer{
    public: 
        virtual void update(float temp){};
        virtual ~Observer() = default;
};

class Subject {
    public:
        virtual void addObserver(Observer* obs){};
        virtual void removeObserver(Observer* obs){};
        virtual void notifyObserver(){};
        virtual ~Subject() = default;
};

class WeatherStation : public Subject {
    private :
        float temperature;
        vector<Observer*>obsList;
    public :
        void addObserver(Observer* obs){
            obsList.push_back(obs);
        }
        void removeObserver(Observer* obs){
            obsList.erase(remove(obsList.begin(),obsList.end(),obs),obsList.end());
        }
        void notifyObserver(){
            for(auto obs : obsList){
                obs->update(temperature);
            }
        }
        void setTemp(float temp){
            this->temperature = temp;
            notifyObserver();
        }
};

class Mobile : public Observer{
    public :
        void update(float temp){
            cout<<"current temperature in Mobile is :- "<<temp<<endl;
        }
};

class Desktop : public Observer{
    public :
        void update(float temp){
            cout<<"current temperature in Desktop is :- "<<temp<<endl;
        }
};

class Tv : public Observer{
    public :
        void update(float temp){
            cout<<"current temperature in Tv is :- "<<temp<<endl;
        }
};

int main(){
    // create publisher
    WeatherStation ws;

    // create subscriber
    Mobile *mb = new Mobile();
    Desktop *dt = new Desktop();
    Tv *tv = new Tv();

    ws.addObserver(mb);
    ws.addObserver(tv);
    ws.addObserver(dt);
    ws.setTemp(34);
    cout<<endl;
    ws.removeObserver(dt);
    ws.setTemp(54);



}