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

class APIGateWay{
    private :
        shared_ptr<UserDetails> ud;
        shared_ptr<OrderDetails> od;
        shared_ptr<PaymentDetails> pd;
    public :
        APIGateWay(){
            ud = make_shared<UserDetails>();
            od = make_shared<OrderDetails>();
            pd = make_shared<PaymentDetails>();
        }
        // task
        void getFullOrderDetails(string userId,string orderId, string paymentId){
            ud->getUserDetails(userId);
            od->getOrderDetails(orderId);
            pd->getPaymentDetails(paymentId);
        }

};


int main(){
    shared_ptr<APIGateWay> apiGateway = make_shared<APIGateWay>();
    apiGateway->getFullOrderDetails("123","456","789");
}