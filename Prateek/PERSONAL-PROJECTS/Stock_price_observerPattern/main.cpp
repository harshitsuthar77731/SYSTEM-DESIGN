#include<iostream>
#include<string>
#include<vector>


using namespace std;


class Observer{
    public :
        virtual void update(float price,string nameOfStock){};
        virtual ~Observer() = default;
};

class Subject{
    public :
        virtual void addObserver(shared_ptr<Observer>){};
        virtual void removeObserver(shared_ptr<Observer>){};
        virtual void notifyObserver(){};
        virtual void updatePrice(float price){};

        virtual ~Subject() = default;
};

class Stock : public Subject{
    protected :
        float price;
        string NameOfStock;
        vector<shared_ptr<Observer>>observerList;
    public :
        Stock(string stockName) : NameOfStock(stockName){};
        void addObserver (shared_ptr<Observer> obs) override {
            observerList.push_back(obs);
        }
        void removeObserver(shared_ptr<Observer> obs) override {
            observerList.erase(remove(observerList.begin(),observerList.end(),obs),observerList.end());
        }
        void notifyObserver() override {
            for(auto obs : observerList){
                obs->update(price,NameOfStock);
            }
        }
        void updatePrice(float price) override {
            this->price = price;
            notifyObserver();
        }
};
class Apple : public Stock{
    public :
        Apple(string nameOfStock) : Stock(nameOfStock) {}
};

class Tesla : public Stock{
    public :
        Tesla(string nameOfStock) : Stock(nameOfStock) {}
};

class MobileApp : public Observer{
    public :
        void update(float price,string nameOfStock) override {
            cout<<"Price of the "<<nameOfStock<<" is "<< price<<endl;
        }
};

class TradingBot : public Observer{
    public :
        void update(float price,string nameOfStock) override{
            cout<<"Buying the stock of "<<nameOfStock<<" at "<< price<<endl;
        }
};


class WebDashboard : public Observer{
    public :
        void update(float price,string nameOfStock) override{
            cout<<"log :- Current "<<nameOfStock<<" at "<< price<<endl;
        }
};



int main(){
    shared_ptr<Apple> appleStock = make_shared< Apple>("Apple");
    shared_ptr<Tesla> teslaStock = make_shared< Tesla>("Tesla");
    shared_ptr<TradingBot> tb = make_shared< TradingBot>();
    shared_ptr<WebDashboard>wd = make_shared< WebDashboard>();
    shared_ptr<MobileApp> ma = make_shared< MobileApp>();

    appleStock->addObserver(tb);
    appleStock->addObserver(wd);

    teslaStock->addObserver(tb);
    teslaStock->addObserver(wd);
    teslaStock->addObserver(ma);

    teslaStock->updatePrice(34);
    appleStock->updatePrice(54);

    teslaStock->removeObserver(wd);
    teslaStock->updatePrice(74);

    
    return 0;
}