// legacy cade

#include<iostream>
#include<string>
using namespace std;

class NotificationService{
    public :
        virtual void send(string to, string subject, string body) = 0;
        virtual ~NotificationService() = default;
};

class EmailNotification : public NotificationService{
    public :
        void send(string to, string subject, string body){
            cout<<"Sending Mail to :"<<to<<endl;
            cout<<"Subject is : "<<subject<<endl;
            cout<<"Body is  :"<<body<<endl;
        }

};


// we cant use our interface here so it is hard to implement run time polymorphism by client by changing sender middleware like if we want to use sendgrid now
class SendGridMailService{
    public :
        void sendEmail(string title, string recipient, string content){
            cout<<"Sending mail via send grid"<<endl;
            cout<<"Sending Mail to :"<<recipient<<endl;
            cout<<"title is : "<<title<<endl;
            cout<<"content is  :"<<content<<endl;
        }
};


class SendGridAdapter : public NotificationService {
    private :
        shared_ptr<SendGridMailService> instance;
    public :
        SendGridAdapter(){
            instance = make_shared<SendGridMailService>();
        }
        void send(string to, string subject, string body){
            instance->sendEmail(subject,to,body);
        }

};

int main(){
    NotificationService *em = new EmailNotification();
    em->send("shantilal@gmail.com","Vacation","Vietnam Chale");
    NotificationService *sg = new SendGridAdapter();
    sg->send("shantilal@gmail.com","Vacation","Vietnam Chale");

}