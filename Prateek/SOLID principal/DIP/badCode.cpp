using namespace std;
#include <iostream>
#include<string>

class EmailService {
    public :
        void sendEmail(string msg){
            cout<<"sending email"<< " "<<msg<<endl;
        }
};
class SMSService {
    public :
        void sendSms(string msg){
            cout<<"sending sms"<< " "<<msg<<endl;
        }
};

class NotificationService{
    private :
        EmailService* es;
        SMSService* ss;
    public :
        NotificationService(){
            this->es = new EmailService();
            this->ss = new SMSService();
        }
        void notifyByEmail(string msg){
            es->sendEmail(msg);
        }
        void notifyBySMS(string msg){
            ss->sendSms(msg);
        }
};
