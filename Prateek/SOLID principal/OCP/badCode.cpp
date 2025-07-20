#include<iostream>
using namespace std;


class PaymentMethod{
    public : 
        void PaymentProcessor(string paymentType, double amt){
            if(paymentType == "Credit"){
                cout<<"payment made through credit card"<<" "<<amt;
            }else if(paymentType == "UPI"){
                cout<<"payment made through UPI card"<<" "<<amt;
            }else if(paymentType == "debit"){
                cout<<"payment made through debit card"<<" "<<amt;
            }else if(paymentType == "paypal"){
                cout<<"payment made through paypal card"<<" "<<amt;
            }else{
                throw invalid_argument("method not supported");
            }
        }
};