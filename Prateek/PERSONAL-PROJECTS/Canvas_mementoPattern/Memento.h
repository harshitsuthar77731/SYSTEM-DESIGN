#pragma once
#include <iostream>        
#include <string>
#include <tuple>
using namespace std;
     struct ShapeInfo {
            string color;
            string shape;
            int x, y;
        };
class Memento{
    private : 
        string color , shape;
        int x,y;
    public :
        Memento(string color , string shape , int x , int y) : color(color),shape(shape),x(x),y(y){};
        ShapeInfo getData(){
            return {color,shape,x,y};
        }

};