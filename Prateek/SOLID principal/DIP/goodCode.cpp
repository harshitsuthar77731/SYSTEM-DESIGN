#include <iostream>
#include<string>
#include<map>
using namespace std;



class NotificationChannel {
    public : 
        virtual ~NotificationChannel() = default;
        virtual void send(string msg) = 0;
};

class Email : public NotificationChannel {
    public :
        void send(string msg) override {
            cout<<"Message sent through Email"<<" "<<msg<<endl;
        }

};

class SMS : public NotificationChannel {
    public :
        void send(string msg) override {
            cout<<"Message sent through SMS"<<" "<<msg<<endl;
        }

};

class Whatsapp : public NotificationChannel {
    public :
        void send(string msg) override {
            cout<<"Message sent through Whatsapp"<<" "<<msg<<endl;
        }

};

class NotificationService {
    private :
        unordered_map<string,NotificationChannel*>notificationChannelMap;
    public :
        void setNotificationChannel(string channelName, NotificationChannel* ns){
            notificationChannelMap[channelName] = ns;
        }
        void sendNotification(string channelName , string msg){
            notificationChannelMap[channelName]->send(msg);
        }
};

int main(){

    NotificationService* ns = new NotificationService();
    ns->setNotificationChannel("SMS",new SMS());
    ns->setNotificationChannel("Email",new Email());
    ns->setNotificationChannel("Whatsapp",new Whatsapp());
    ns->sendNotification("SMS","Hello World");
    ns->sendNotification("Email","Hello World");
    ns->sendNotification("Whatsapp","Hello World");


}