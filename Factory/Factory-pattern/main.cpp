#include<iostream>
#include<string>

using namespace std;


class Shape{
    public : 
        virtual void draw() = 0;
        virtual ~Shape() = default;

};

// Is a relat. with shape
class Circle : public Shape{
    public :
        void draw() override{
            cout<<"Circle"<<endl;
        }
};

// Is a relat. with shape
class Rectangle : public Shape{
    public : 
        void draw(){
            cout<<"Rectangle"<<endl;
        }
};

// has a shape factory object
class ShapeFactory {
    public : 
        Shape* getShape(string input){
            if(input == "Circle"){
                return new Circle();
            }else if(input == "Rectangle"){
                return new Rectangle();
            }else {
                return nullptr;
            }
        }
};


int main(){
    ShapeFactory* sf = new ShapeFactory();
    auto csp = sf->getShape("Circle");
    auto rsp = sf->getShape("Rectangle");
    csp->draw();
    rsp->draw();
}