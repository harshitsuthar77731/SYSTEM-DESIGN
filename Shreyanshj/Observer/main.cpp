#include <bits/stdc++.h>
#include <vector>
#include <map>
#include<iostream>

using namespace std;

class Observer {
    public :
       virtual void update(int valueofproduct) = 0;
       virtual void setValue(int newPrice) = 0;
       virtual void getData() = 0;
       virtual ~Observer() = default;
};

class Observable {
    protected :
        unordered_map<Observer*,int> obsMap;
        int valueOfProduct = 0;
    public :
        void add(Observer* obs){
            auto it = obsMap.find(obs);
            if(it==obsMap.end()){
                obsMap[obs] = 0;
                cout<<"Observer added to list"<<endl;
            }
        }
        void remove(Observer* obs){
            auto it = obsMap.find(obs);
            if(it!=obsMap.end()){
                obsMap.erase(obs);
                cout<<"Observer removed from list"<<endl;
                
            }else{
                cout<<"No observer in list"<<endl;
            }
        }
        void notify(){
            for(const auto& it : obsMap){
                Observer*  obsPtr = it.first;
                obsPtr->update(valueOfProduct);
            }
        }
        void setData(int updatedVal){
            valueOfProduct = updatedVal;
            for(const auto& it : obsMap){
                Observer*  obsPtr = it.first;
                obsPtr->setValue(updatedVal);
            }
            notify();

            
        }
        int getData(){
            return valueOfProduct;
        }
        ~Observable(){};
};




class Phone : public Observer{
    protected :
        Observable* obs;
        int newPrice = 0;
    public :
        Phone(Observable* obs){
            this->obs = obs;
        }
        void update(int valueofproduct) override{
            cout<<"Phone is notified "<<valueofproduct<<endl;
        }
        void setValue(int newPrice) override{
            this->newPrice = newPrice;
        }
        void getData() override{
            cout<<"Value Of product is"<<" "<<obs->getData()<<endl;
        }
};


class TvDisplay : public Observer{
    protected :
        Observable* obs;
        int newPrice = 0;
    public :
        TvDisplay(Observable* obs){
            this->obs = obs;
        }
        void update(int valueofproduct) override{
            cout<<"Tv is notified "<<valueofproduct<<endl;
        }
        void setValue(int newPrice) override{
            this->newPrice = newPrice;
        }
        void getData() override{
            cout<<"Value Of product is"<<" "<<obs->getData()<<endl;
        }
};



int main(){
    Observable* observableObj = new Observable();
    observableObj->setData(23);
    Observer* pn = new Phone(observableObj);
    Observer* td = new TvDisplay(observableObj);
    observableObj->add(pn);
    observableObj->add(td);
    observableObj->notify();
        pn->getData();
        td->getData();
    observableObj->setData(45);
    pn->getData();
    td->getData();
    observableObj->notify();
    delete pn;
    delete td;
    delete observableObj;
    return 0;

}