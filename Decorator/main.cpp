#include <iostream>
using namespace std;


class BasePizza { 
    public :
        virtual int cost() = 0;
        virtual ~BasePizza() = default;
};
// is a relation ship with pizza
class Margherita : public BasePizza{
    int cost() override{
        return 100;
    }
};
// is a relation ship with pizza

class VegDelight : public BasePizza{
    int cost() override{
        return 50;
    }
};
// is a relation ship with pizza

class FarmHouse : public BasePizza{
    int cost() override{
        return 70;
    }
};

// is a relationship and it's child will consist has a relationship
class ToppingDecorator : public BasePizza{
    protected : 
        BasePizza* bp;
    public : 
        ToppingDecorator(BasePizza* bp){
            this->bp = bp;
        }
};
// has a and is a relationship
class ExtraCheese : public ToppingDecorator{
    public : 
    //This means:
	// •	When an ExtraCheese object is created, it immediately calls ToppingDecorator(pizza) before the body of its own constructor (which is empty here).
	// •	That ensures the base class ToppingDecorator is fully initialized with the pizza object it wraps.

        ExtraCheese(BasePizza* pizza) : ToppingDecorator(pizza){}
        int cost() override{
            return bp->cost()+30;
        }
};

class ExtraOlive : public ToppingDecorator{
    public : 
        ExtraOlive(BasePizza* pizza) : ToppingDecorator(pizza){}
        int cost() override{
            return bp->cost()+60;
        }
};



int main(){

    BasePizza *VD = new VegDelight();
    BasePizza *FH = new FarmHouse();
    BasePizza *MG = new Margherita();
    cout<<"cost is "<<VD->cost()<<endl;
    cout<<"cost is "<<FH->cost()<<endl;
    cout<<"cost is "<<MG->cost()<<endl;
    BasePizza *EC = new ExtraCheese(VD);
    BasePizza *EO = new ExtraOlive(EC);
    cout<<"cost of veg delight and extra cheese is "<<EC->cost()<<endl;
    cout<<"cost of veg delight and extra cheese and extra olive is "<<EO->cost()<<endl;

}



