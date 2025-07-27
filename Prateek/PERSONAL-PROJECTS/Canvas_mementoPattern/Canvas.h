#pragma once
#include <iostream>        
#include <string>
#include <tuple>
#include "Memento.h"
using namespace std;
class Canvas{
    private : 
        string color , shape;
        int x,y;
    public :    
        void addShape(string color , string shape , int x , int y){
            this->color = color;
            this->shape = shape;
            this->x = x;
            this->y = y;
        }
        Memento* saveCurrentState(){
            return new Memento(color,shape,x,y);
        }
        void restorState(Memento * memento){
                const ShapeInfo& info = memento->getData();
                cout<<info.color << " "<<info.shape<<" "<<endl;
                this->color = info.color;
                this->shape = info.shape;
                this->x = info.x;
                this->y = info.y;
        }
        void getShape(){
            cout<<"current shape is"<<shape<<"and its color is" << color << "with dimension"<<x<< " "<<y<<endl; 
        }

};
