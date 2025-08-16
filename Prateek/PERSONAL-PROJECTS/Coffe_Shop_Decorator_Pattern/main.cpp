#include<iostream>
#include<string>
using namespace std;


class Coffee{
    public :
        virtual string getDescription()const = 0;
        virtual double getPrice()const = 0;
        virtual ~Coffee() = default;

};

class BasicCoffee : public Coffee{
    public :
        string getDescription() const override{return "Basic Coffee";}; 
        double getPrice() const override{return 5;}; 
};

class CoffeeDecorator : public Coffee{
    protected :
        shared_ptr<Coffee> instance ;
    public :
        CoffeeDecorator(shared_ptr<Coffee> instance) : instance(instance) {}
        string getDescription() const override {return "";};
        double getPrice()  const override{return 0;};
};

class MilkDecorator : public CoffeeDecorator{

    public :
    MilkDecorator(shared_ptr<Coffee> instance) : CoffeeDecorator(instance){};
    string getDescription() const override {
        return instance->getDescription()+" ,Milk";
    };
    double getPrice()  const override{
        return instance->getPrice()+.5;
    };
};
class SugarDecorator : public CoffeeDecorator{
    public :
    SugarDecorator(shared_ptr<Coffee> instance) : CoffeeDecorator(instance){};
    string getDescription()  const override{
        return instance->getDescription()+" ,Sugar";
    };
    double getPrice()  const override{
        return instance->getPrice()+2;
    };
};


int main(){
    shared_ptr<Coffee> coffee = make_shared<BasicCoffee>();
    coffee = make_shared<MilkDecorator>(coffee);
    coffee = make_shared<SugarDecorator>(coffee);
    cout<<coffee->getDescription()<<endl;
    cout<<coffee->getPrice()<<endl;
}
