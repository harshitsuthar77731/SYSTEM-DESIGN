#include <iostream>
using namespace std;


class PaymentService{
    public :
        void pay(string paymentType){
            if(paymentType=="Credit Card"){
                cout<<"Paying Through Credit Card"<<endl;
            }else if(paymentType=="Debit Card"){
                cout<<"Paying Through Debit Card"<<endl;
            } if(paymentType=="UPI"){
                cout<<"Paying Through UPI"<<endl;
            } 
        }
};

int main(){
    PaymentService ps;
    ps.pay("Credit Card");
    ps.pay("Debit Card");
    ps.pay("UPI");
}