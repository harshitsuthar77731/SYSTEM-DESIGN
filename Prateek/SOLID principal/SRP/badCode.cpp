#include <iostream>
#include <string>
#include <map>

using namespace std;

class Invoice {
    private :
        long long amount;
    public :
        Invoice(long long amount){
            this->amount = amount;
        }
        void generateInvoice(){
            cout<<"Invoice genrated";
        }
        void addInvoiceToDB(){
            cout<<"Invoice added to db";
        }
        void sendEmailNotification(){
            cout<<"Sending Email Notification sent to user";
        }
};