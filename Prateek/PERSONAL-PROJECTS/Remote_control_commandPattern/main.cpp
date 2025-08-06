#include<iostream>
#include<map>
#include<vector>
enum class ButtonSlot {
    Button1,
    Button2,
    Button3,
    Button4
};

using namespace std;

class SmartLight{
    public :
        void turnOnLight(){
            cout<<"Light are turn on"<<endl;
        }
        void turnOFFLight(){
            cout<<"Light are turn off"<<endl;
        }
};
class SmartFan{
    public :
        void turnOnFan(){
            cout<<"Fan are turn on"<<endl;
        }
        void turnOFFFan(){
            cout<<"Fan are turn off"<<endl;
        }
};
class SmartSpeaker{
    public :
        void turnOnSpeaker(){
            cout<<"Speaker are turn on"<<endl;
        }
        void turnOFFSpeaker(){
            cout<<"Speaker are turn off"<<endl;
        }
};
class SmartAC{
    public :
        void turnOnAC(){
            cout<<"AC are turn on"<<endl;
        }
        void turnOFFAC(){
            cout<<"AC are turn off"<<endl;
        }
        void temperatureDown(){
            cout<<"AC temperature is increased"<<endl;
        }
        void temperatureUp(){
            cout<<"AC temperature is increased"<<endl;
        }
};

class smartGarage{
    public :
        void openGarage (){
            cout<<"Garage shutter is opened"<<endl;
        }
        void closeGarage(){
            cout<<"Garage shutter is closed"<<endl;
        }
};





class Command{
    public :
        virtual void execute() = 0;
        virtual ~Command() = default;
};


class OnAc : public Command{
    private :
        shared_ptr<SmartAC> ac;
    public :
        OnAc( shared_ptr<SmartAC> ac) : ac(ac){};
        void execute() override{
            ac->turnOnAC();
        }
    
};
class OFFAc : public Command{
    private :
        shared_ptr<SmartAC> ac;
    public :
        OFFAc( shared_ptr<SmartAC> ac) : ac(ac){};
        void execute() override{
            ac->turnOFFAC();
        }
};
class IncreaseAc : public Command{
    private :
        shared_ptr<SmartAC> ac;
    public :
        IncreaseAc( shared_ptr<SmartAC> ac) : ac(ac){};
        void execute() override{
            ac->temperatureUp();
        }
};
class DecreaseAc : public Command{
    private :
        shared_ptr<SmartAC> ac;
    public :
        DecreaseAc( shared_ptr<SmartAC> ac) : ac(ac){};
        void execute() override{
            ac->temperatureDown();
        }
};
class OpenGarage : public Command{
    private :
        shared_ptr<smartGarage> garage;
    public :
        OpenGarage( shared_ptr<smartGarage> garage) : garage(garage){};
        void execute() override{
            garage->openGarage();
        }
};

class CloseGarage : public Command{
       private :
        shared_ptr<smartGarage> garage;
    public :
        CloseGarage( shared_ptr<smartGarage> garage) : garage(garage){};
        void execute() override{
            garage->closeGarage();
        }
};

class Button {
    private :
        shared_ptr<Command> cd;
    public :
        Button(shared_ptr<Command> cd) : cd(cd){};
        void click(){
            cd->execute();
        }
};

class Remote{
    private :
        unordered_map<ButtonSlot,shared_ptr<Button>>buttonMap;
    public :
        void setButton(ButtonSlot buttonName , shared_ptr<Button>bt){
            buttonMap[buttonName] = bt;
        }
        void clickButton(ButtonSlot buttonName ){
            if(buttonMap.count(buttonName)>0)
                buttonMap[buttonName]->click();
            else 
                cout<<"Button not assigned"<<endl;
        }
};

int main(){
    shared_ptr<smartGarage>garage = make_shared<smartGarage>();
    shared_ptr<SmartAC>airConditioner = make_shared<SmartAC>();
    shared_ptr<Command>turnOnAcCommand = make_shared<OnAc>(airConditioner);
    shared_ptr<Command>turnOffAcCommand = make_shared<OFFAc>(airConditioner);
    shared_ptr<Command>increaseAcCommand = make_shared<IncreaseAc>(airConditioner);
    shared_ptr<Command>decreaseAcCommand = make_shared<DecreaseAc>(airConditioner);
    shared_ptr<Command>openGarageCommand = make_shared<OpenGarage>(garage);
    shared_ptr<Command>closeGarageCommand = make_shared<CloseGarage>(garage);


    shared_ptr<Button>turnOnAcButton = make_shared<Button>(turnOnAcCommand);
    shared_ptr<Button>turnOffAcButton = make_shared<Button>(turnOffAcCommand);
    shared_ptr<Button>increaseAcButton = make_shared<Button>(increaseAcCommand);
    shared_ptr<Button>decreaseAcButton = make_shared<Button>(decreaseAcCommand);
    shared_ptr<Button>openGarageButton = make_shared<Button>(openGarageCommand);
    shared_ptr<Button>closeGarageButton = make_shared<Button>(closeGarageCommand);
    
    shared_ptr<Remote>remoteController = make_shared<Remote>();

    remoteController->setButton(ButtonSlot::Button1,turnOnAcButton);
    remoteController->setButton(ButtonSlot::Button2,turnOffAcButton);
    remoteController->setButton(ButtonSlot::Button3,openGarageButton);


    remoteController->clickButton(ButtonSlot::Button1);
    remoteController->clickButton(ButtonSlot::Button2);
    remoteController->clickButton(ButtonSlot::Button3);
    remoteController->clickButton(ButtonSlot::Button4);

}