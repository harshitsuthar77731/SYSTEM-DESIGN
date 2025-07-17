#include <iostream>
#include <string>
#include <map>

using namespace std;

class PaymentMethod{
    public : 
        virtual void pay () = 0;
        virtual ~PaymentMethod() = default;
};

class Card : public PaymentMethod {
    protected :
        string cardId;
        string cardHolderName;
    public :
        Card(string cardId , string cardHolderName){
            this->cardId = cardId;
            this->cardHolderName = cardHolderName;
        }
};

class Debit : public Card{
    public : 
        Debit(string cardId , string cardHolderName) : Card(cardId,cardHolderName){
            
        }
        void pay() override{
            cout<<"Payment received from Debit card with following credentials "<<this->cardId<<" "<<this->cardHolderName<<endl;
        }
};

class Credit : public Card{
    public : 
        Credit(string cardId , string cardHolderName) : Card(cardId,cardHolderName){
            
        }
        void pay() override{
            cout<<"Payment received from Credit card with following credentials "<<this->cardId<<" "<<this->cardHolderName<<endl;
        }
};

class UPI : public PaymentMethod{
    protected : 
        string upiID;
    public : 
        UPI (string id) : upiID(id){}; //initializer list
        void pay() override{
            cout<<"Payment received from UPI with following credentials "<<this->upiID<<endl;
        }
};


class PaymentService{
    private : 
        unordered_map<string, PaymentMethod*>paymentMethods;
    public :
       void addPayment(string name , PaymentMethod* pm){
            paymentMethods[name] = pm;
       }
       void makePayment(string name ){
            if(paymentMethods.find(name)!=paymentMethods.end()){
                paymentMethods[name]->pay();
            }
       }
       ~PaymentService(){
            for(auto it = paymentMethods.begin();it!=paymentMethods.end();it++){
                delete it->second;
            }
    }
};


int main(){

    PaymentService *ps = new PaymentService();
    ps->addPayment("Debit1234",new Debit( "1234","Harshit"));
    ps->addPayment("Credit1234",new Credit( "1234","Harshit"));
    ps->addPayment("UPI1234",new UPI( "UPI1234"));
    ps->makePayment("Debit1234");
    ps->makePayment("Credit1234");
    ps->makePayment("UPI1234");

    return 0;
}