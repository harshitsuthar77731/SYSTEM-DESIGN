#include<iostream>
using namespace std;

class PaymentStrategy {
    public :
        virtual void processPayment() = 0;
        virtual ~PaymentStrategy() = default;
};

class PaymentService{
    public :
        void pay(shared_ptr<PaymentStrategy> strategy){
            strategy->processPayment();
        }
};
 
class UPI : public PaymentStrategy{
    public :
        void processPayment() override{
            cout<<"paying through upi"<<endl;
        }
};

class CreditCard : public PaymentStrategy{
    public :
        void processPayment() override{
            cout<<"paying through credit card"<<endl;
        }
};
class DebitCard : public PaymentStrategy{
    public :
        void processPayment() override{
            cout<<"paying through debit card"<<endl;
        }
};

int main(){

    shared_ptr<PaymentService>ps = make_shared<PaymentService> ();
    ps->pay(make_shared<CreditCard>());
    ps->pay(make_shared<DebitCard>());
    ps->pay(make_shared<UPI>());


    return 0;
}