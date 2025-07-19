#include<iostream>
using namespace std;


// making payment method interface
class PaymentMehod{
    public : 
        virtual void pay(double amt) = 0;
        virtual ~PaymentMehod() = default;
};

class Debit : public PaymentMehod{
    public : 
        void pay(double amt){
            cout<<"Payment made through debit card"<<" "<<amt<<endl;
        }
};

class Credit : public PaymentMehod{
    public : 
        void pay(double amt){
            cout<<"Payment made through credit card"<<" "<<amt<<endl;;
        }
};

class Paypal : public PaymentMehod{
    public : 
        void pay(double amt){
            cout<<"Payment made through paypal"<<" "<<amt<<endl;;
        }
};

class PaymentProcessor{
    public : 
        void processPayment(PaymentMehod* pm,double amt){
            pm->pay(amt);
        }
};

int main(){

    PaymentProcessor * pmp = new PaymentProcessor();
    pmp->processPayment(new Debit(),300);
    pmp->processPayment(new Credit(),400);
    pmp->processPayment(new Paypal(),500);

}