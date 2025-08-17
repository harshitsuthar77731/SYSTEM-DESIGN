#include<iostream>
#include<string>
using namespace std;

class UserDetails{
    public :
        void getUserDetails(string id){
            cout<<"User details for user user id :-"<<id<<"\n";
        }
};

class OrderDetails{
    public :
        void getOrderDetails(string id){
            cout<<"Order details for order id :-"<<id<<"\n";
        }
};

class PaymentDetails{
    public :
        void getPaymentDetails(string id){
            cout<<"Payment details with payment id :-"<<id<<"\n";
        }
};


int main(){
    UserDetails *ud = new UserDetails();
    OrderDetails *od = new OrderDetails();
    PaymentDetails *pd = new PaymentDetails();
    // tightly coupled
    ud->getUserDetails("123");
    od->getOrderDetails("144");
    pd->getPaymentDetails("356");

}