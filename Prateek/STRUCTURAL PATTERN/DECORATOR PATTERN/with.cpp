#include<iostream>
#include<string>
using namespace std;


class Pizza{
    public :
        virtual string getDescription()const = 0;
        virtual double getPrice()const = 0;
        virtual ~Pizza() = default;

};

class BasicPizza : public Pizza{
    public :
        string getDescription() const override{return "Basic pizza";}; 
        double getPrice() const override{return 5;}; 
};

class PizzaDecorator : public Pizza{
    protected :
        shared_ptr<Pizza> instance ;
    public :
        PizzaDecorator(shared_ptr<Pizza> instance) : instance(instance) {}
        string getDescription() const override {return "";};
        double getPrice()  const override{return 0;};
};

class OliveDecorator : public PizzaDecorator{

    public :
    OliveDecorator(shared_ptr<Pizza> instance) : PizzaDecorator(instance){};
    string getDescription() const override {
        return instance->getDescription()+" ,Olive";
    };
    double getPrice()  const override{
        return instance->getPrice()+.5;
    };
};
class CheeseDecorator : public PizzaDecorator{
    public :
    CheeseDecorator(shared_ptr<Pizza> instance) : PizzaDecorator(instance){};
    string getDescription()  const override{
        return instance->getDescription()+" ,Cheese";
    };
    double getPrice()  const override{
        return instance->getPrice()+2;
    };
};


int main(){
    shared_ptr<Pizza> pizza = make_shared<BasicPizza>();
    pizza = make_shared<OliveDecorator>(pizza);
    pizza = make_shared<CheeseDecorator>(pizza);
    cout<<pizza->getDescription()<<endl;
    cout<<pizza->getPrice()<<endl;
}
