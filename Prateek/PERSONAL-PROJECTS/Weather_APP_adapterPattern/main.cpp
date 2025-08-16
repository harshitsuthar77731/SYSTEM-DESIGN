#include<iostream>
#include<string>
using namespace std;


class WeatherService{
    public :
        virtual void getTemperature() = 0;
        virtual void getHumidity() = 0;
        virtual void getWindSpeed() = 0;
        virtual ~WeatherService() = default;
};


class APIA {
    public :
        double getTemperatureCelsius(){return 33.4;};
        string getHumidityPer() {return "60%";};
        double getWindSpeedMetric() {return 60;};

};

class APIAAdapter : public WeatherService{
    private :
        unique_ptr<APIA> instance;
    public :
        APIAAdapter(){
            instance = make_unique<APIA>();
        }
        void getTemperature() override{
            cout<<"Temperature is :- "<<instance->getTemperatureCelsius()<<endl;
        };
        void getHumidity() override{
            
            cout<<"Humidity is :- "<<stod(instance->getHumidityPer().substr(0, instance->getHumidityPer().size() - 1))<<endl;
        };
        void getWindSpeed() override{
            cout<<"Speed is :- "<<instance->getWindSpeedMetric()<<endl;
        };
};


class APIB {
    public :
        double getTemperatureFahrenheit(){ return 98.4;};
        double getHumidityValue() {return 70.0;};
        double getWindSpeedMilesPerHour() {return 54;};
};

class APIBAdapter : public WeatherService{
    private :
        unique_ptr<APIB> instance;
    public :
        APIBAdapter(){
            instance = make_unique<APIB>();
        }
        void getTemperature() override{
            cout<<"Temperature is :- "<<(instance->getTemperatureFahrenheit()- 32)* 5.0/9.0<<endl;
        };
        void getHumidity() override{
            cout<<"Humidity is :- "<<instance->getHumidityValue()<<endl;
        };
        void getWindSpeed() override{
            cout<<"Speed is :- "<<instance->getWindSpeedMilesPerHour()* 1.60934<<endl;
        };
};

int main(){
    shared_ptr<APIAAdapter> apia = make_shared<APIAAdapter>();
    shared_ptr<APIBAdapter> apib = make_shared<APIBAdapter>();
    apia->getTemperature();
    apib->getTemperature();
    apia->getWindSpeed();
    apib->getWindSpeed();
    apia->getHumidity();
    apib->getHumidity();

}