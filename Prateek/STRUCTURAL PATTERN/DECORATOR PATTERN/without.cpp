#include<iostream>
#include<string>
using namespace std;

// if there are 100 combination then we have to make 100 classes which is  not scalable

class Pizza{
    public :
        virtual string getDescription() = 0;
        virtual double getPrice() = 0;
        virtual ~Pizza() = default;

};

class BasicPizza : public Pizza{
    public :
        string getDescription(){return "Basic pizza";}; 
        double getPrice(){return 5;}; 
};

class CheesePizza : public BasicPizza{
    public :
        string getDescription(){
            return BasicPizza::getDescription()+" ,Cheese";
        }; 
        double getPrice(){
            return BasicPizza::getPrice()+1;
        }; 
};

class CheeseOlivePizza : public CheesePizza{
    public :
        string getDescription(){
            return CheesePizza::getDescription()+" ,olive";
        }; 
        double getPrice(){
            return CheesePizza::getPrice()+.5;
        }; 
};



int main(){
    Pizza *cheeseOlivePizza = new CheeseOlivePizza();
     cout<<cheeseOlivePizza->getDescription()<<endl;
     cout<<cheeseOlivePizza->getPrice()<<endl;

}