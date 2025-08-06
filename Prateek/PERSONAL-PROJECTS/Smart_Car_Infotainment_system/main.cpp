#include<iostream>
#include<stack>
#include <tuple>
using namespace std;


class UserMemento{
    private : 
        string name;
        string lastVisitedScreen;
        string theme;
        int volumeLevel;
    public :
        UserMemento(string name,string lastVisitedScreen,string theme,int volumeLevel):name(name),lastVisitedScreen(lastVisitedScreen),theme(theme),volumeLevel(volumeLevel){};
        tuple<string,string,string,int> getStateParam() const {
            return make_tuple(name,lastVisitedScreen,theme,volumeLevel);
        }

};


class User{
    private :
        string name;
        string lastVisitedScreen;
        string theme;
        int volumeLevel;
    public :
       void setName(string name){
            this->name = name;
       }
       void setLastVisitedScreen(string lastVisitedScreen){
            this->lastVisitedScreen = lastVisitedScreen;
       }
       void setTheme(string theme){
            this->theme = theme;
       }
       void setVolumeLevel(int volumeLevel){
            this->volumeLevel = volumeLevel;
       }
       void setPreviousState(string name,string lastVisitedScreen,string theme,int volumeLevel){
            this->name = name;
            this->lastVisitedScreen =lastVisitedScreen;
            this->theme = theme;
            this->volumeLevel = volumeLevel;
       }
       shared_ptr<UserMemento> saveState(){
           return make_shared<UserMemento>(name,lastVisitedScreen,theme,volumeLevel);
       }
       tuple<string,string,string,int> getDetails() const {
            return make_tuple(name,lastVisitedScreen,theme,volumeLevel);
        }


};



class CareTaker{
    private :
        stack<shared_ptr<UserMemento>> history;
    public :
        void savePreference(shared_ptr<User> &user){
            history.push(user->saveState());
        }
        void restoState(shared_ptr<User> & user){
            history.pop();
            if(!history.empty()) {
                shared_ptr<UserMemento> previousState = history.top();
                history.pop();
                auto [namePrev, screenPrev, themePrev, volumePrev] = previousState->getStateParam();
                user->setPreviousState(namePrev,screenPrev,themePrev,volumePrev);
            }
        }
};



class RouteStrategy {
    public : 
        virtual string route() = 0;
        virtual ~RouteStrategy() = default;
};

class ScenicRoute : public RouteStrategy{
    public :
        string route() override{
            return "Currently on scenic Route";
        }
};
class FastestRoute : public RouteStrategy{
    public :
        string route() override{
            return "Currently on Fastest Route";
        }
};
class TollFreeRoute : public RouteStrategy{
    public :
        string route() override{
            return "Currently on Toll Free Route";
        }
};


class Route{
    public :
        string getRoute(shared_ptr<RouteStrategy>strategy){
            return strategy->route();
        }
};




class Command {
    public :
        virtual void execute(string input) = 0;
        virtual ~Command() = default;
};

class VoiceCommands{
    public : 
        void call(string number){
            cout<<"Calling on number "<<number<<endl;
        }
        void playMusic(string music){
            cout<<"Playing music "<<music<<endl;
        }
        void navigate(string location){
            cout<<"Navigating to location "<<location<<endl;
        }
};

class CallCommand : public Command{
    private :
        shared_ptr<VoiceCommands> voiceCommands;
    public :
        CallCommand(shared_ptr<VoiceCommands> voiceCommands) : voiceCommands(voiceCommands){};
        void execute(string input) override{
            voiceCommands->call(input);
        }
};
class PlayMusicCommand : public Command{
    private :
        shared_ptr<VoiceCommands> voiceCommands;
    public :
        PlayMusicCommand(shared_ptr<VoiceCommands> voiceCommands) : voiceCommands(voiceCommands){};
        void execute(string input) override{
            voiceCommands->playMusic(input);
        }
};
class NavigateCommand : public Command{
    private :
        shared_ptr<VoiceCommands> voiceCommands;
    public :
        NavigateCommand(shared_ptr<VoiceCommands> voiceCommands) : voiceCommands(voiceCommands){};
        void execute(string input) override{
            voiceCommands->navigate(input);
        }
};


class Button{
    private :
        shared_ptr<Command> currentCommand;
    public :
        Button( shared_ptr<Command> currentCommand) : currentCommand(currentCommand){};
        void click(string voiceInput){
            currentCommand->execute(voiceInput);
        }
};




class Observer {
    public : 
        virtual void update(string input) = 0;
        virtual ~Observer() = default;
};

class Subject {
    public : 
        virtual void addObserver(const shared_ptr<Observer>& obs) = 0;
        virtual void removeObserver(const shared_ptr<Observer>& obs) = 0;
        virtual void notify() = 0;
        virtual ~Subject() = default;
};

class Weather : public Subject{
    private : 
        string temperature;
        vector<shared_ptr<Observer>> arrayOfObserver;
    public :    
        void setTemperature(string temp){
            this->temperature = temp;
            notify();
        }
        void addObserver(const shared_ptr<Observer>& obs) override{
            arrayOfObserver.push_back(obs);
        }
        void removeObserver(const shared_ptr<Observer>& obs) override{
            arrayOfObserver.erase(remove(arrayOfObserver.begin(),arrayOfObserver.end(),obs),arrayOfObserver.end());
        }
        void notify() override{
            for(auto obs : arrayOfObserver){
                string input = "Current temperature is "+this->temperature;
                obs->update(input);
            }
        }
};
class Traffic : public Subject{
     private : 
        string trafficInfo;
        vector<shared_ptr<Observer>> arrayOfObserver;
    public :    
        void setTraffic(string input){
            this->trafficInfo = input;
            notify();
        }
        void addObserver(const shared_ptr<Observer>& obs) override{
            arrayOfObserver.push_back(obs);
        }
        void removeObserver(const shared_ptr<Observer>& obs) override{
            arrayOfObserver.erase(remove(arrayOfObserver.begin(),arrayOfObserver.end(),obs),arrayOfObserver.end());
        }
        void notify() override{
            for(auto obs : arrayOfObserver){
                string input = "Current traffic Info is "+this->trafficInfo;
                obs->update(input);
            }
        }
};
class Notification : public Subject{
     private : 
        string notification;
        vector<shared_ptr<Observer>> arrayOfObserver;
    public :    
        void setNotification(string input){
            this->notification = input;
            notify();
        }
        void addObserver(const shared_ptr<Observer>& obs) override{
            arrayOfObserver.push_back(obs);
        }
        void removeObserver(const shared_ptr<Observer>& obs) override{
            arrayOfObserver.erase(remove(arrayOfObserver.begin(),arrayOfObserver.end(),obs),arrayOfObserver.end());
        }
        void notify() override{
            for(auto obs : arrayOfObserver) {
                string input = "Current notification is "+this->notification;
                obs->update(input);
            }
        }
};


class SystemBootTemplate{
    public : 
        void Boot(){
            loadSystemConfiguration();
            connectToNetwork();
            loadTheLastUserSession();
            displayHomeScreen();
        }
        virtual void loadSystemConfiguration(){};
        virtual void connectToNetwork(){};
        virtual void loadTheLastUserSession(){};
        virtual void displayHomeScreen(){};
};



class Premium : public SystemBootTemplate , public Observer{
    private :
        shared_ptr<User> user; // done
        shared_ptr<CareTaker> caretakerOfUser;  // done
        shared_ptr<Route> route;  
        shared_ptr<Button> button1;  // done
        shared_ptr<Button> button2;  // done
        shared_ptr<Button> button3; // done 
        int currentVol;  // done
        string theme;  // done
        string lastVisitedScreen;  // done

    public : 
        Premium(){
            auto voice = make_shared<VoiceCommands>();
            user = make_shared<User>();
            caretakerOfUser = make_shared<CareTaker>();
            route = make_shared<Route>();
            button1 = make_shared<Button>(make_shared<CallCommand>(voice));
            button2 = make_shared<Button>(make_shared<PlayMusicCommand>(voice));
            button3 = make_shared<Button>(make_shared<NavigateCommand>(voice));
        }
        void loadSystemConfiguration(){
            cout<<"Loading system configuration"<<endl;
        }
        void connectToNetwork(){
            cout<<"Connected to bluetooth and synced with cloud"<<endl;
        }
        void loadTheLastUserSession(){
            if(user){
                auto [name, screen, theme, volume] = user->getDetails();
                cout<<"welcome "<<name<<endl;
                this->currentVol = volume;
                this->theme = theme;
                this->lastVisitedScreen = screen;
            }
        }
        void displayHomeScreen(){
            cout<<"Displaying the all functionality"<<endl;
        }
        void update(string input){
            cout<<input<<endl;
        }
        void createUser(  string name, string lastVisitedScreen,string theme,int volumeLevel){
            if (!user) user = make_shared<User>();
            if (!caretakerOfUser) caretakerOfUser = make_shared<CareTaker>();
           
            user->setName(name);
            user->setLastVisitedScreen(lastVisitedScreen);
            user->setVolumeLevel(volumeLevel);
            user->setTheme(theme);
            caretakerOfUser->savePreference(user);
        }
        void updateName( string name){
            user->setName(name);
            caretakerOfUser->savePreference(user);
        }
        void updateLastVisitedScreen( string lastVisitedScreen){
            user->setLastVisitedScreen(lastVisitedScreen);
            caretakerOfUser->savePreference(user);
        }
        void updateTheme(string theme){
            user->setTheme(theme);
            caretakerOfUser->savePreference(user);
        }
        void updateVolume(int volumeLevel){
            user->setVolumeLevel(volumeLevel);
            caretakerOfUser->savePreference(user);
        }
        void loadPreviousUser(){
            caretakerOfUser->restoState(user);
            loadTheLastUserSession();
        }
        void clickButton1(string input){
            button1->click(input);
        }
        void clickButton2(string input){
            button2->click(input);
        }

        void clickButton3(string input){
            button3->click(input);
        }
        void updateRoute(shared_ptr<RouteStrategy>strategy){
            cout<<route->getRoute(strategy)<<endl;
        }

};


int main() {
    cout << "===== BOOTING INFOTAINMENT SYSTEM =====" << endl;

    // Step 1: Create system instance
    shared_ptr<Premium> system = make_shared<Premium>();
    system->createUser("Harshit", "Music", "Dark", 70);

    // Step 2: Register system as observer
    shared_ptr<Weather> weather = make_shared<Weather>();
    shared_ptr<Traffic> traffic = make_shared<Traffic>();
    shared_ptr<Notification> notification = make_shared<Notification>();

    weather->addObserver(system);
    traffic->addObserver(system);
    notification->addObserver(system);

    // Step 3: Boot the system
    system->Boot();

    // Step 4: Create user
    cout << "\n===== SETTING USER PROFILE =====" << endl;
    system->createUser("Tanu", "Music", "Light", 50);
    system->loadTheLastUserSession();
    // Step 5: Use Voice Commands
    cout << "\n===== VOICE COMMAND TEST =====" << endl;
    system->clickButton1("9876543210");        // Call
    system->clickButton2("Chill Vibes");       // Play Music
    system->clickButton3("Connaught Place");   // Navigate

    // Step 6: Switch Navigation Strategy
    cout << "\n===== NAVIGATION STRATEGY SWITCH =====" << endl;
    system->updateRoute(make_shared<FastestRoute>());
    system->updateRoute(make_shared<ScenicRoute>());

    // Step 7: Real-Time Update Simulation
    cout << "\n===== SIMULATING LIVE UPDATES =====" << endl;
    weather->setTemperature("36°C");
    traffic->setTraffic("Heavy traffic near Airport");
    notification->setNotification("Low fuel warning");

    // Step 8: Simulate shutdown + restore session
    cout << "\n===== RESTORING PREVIOUS SESSION =====" << endl;
    system->loadPreviousUser();  // restore previous (volume 70)
    system->updateVolume(40);  // simulate state change

    return 0;
}