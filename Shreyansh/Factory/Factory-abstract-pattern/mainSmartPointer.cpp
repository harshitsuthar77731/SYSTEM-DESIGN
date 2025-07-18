#include<iostream>
#include<string>
#include <memory>
using  namespace std;

class Shape{
    public :
        virtual void draw() = 0;
        virtual ~Shape() = default;
 };


class ModernCircle : public Shape{
    public : 
        void draw() override{
            cout<<"Modern Circle"<<endl;
        }
};

class ModernRectangle : public Shape{
    public : 
        void draw() override{
            cout<<"Modern Rectangle"<<endl;
        }
};

class ClassicCircle : public Shape{
    public : 
        void draw() override{
            cout<<"Classic Circle"<<endl;
        }
};
class ClassicRectangle : public Shape{
    public : 
        void draw() override{
            cout<<"Classic Rectangle"<<endl;
        }
};


class Factory2 {
    public : 
        virtual unique_ptr<Shape> getShape(string input) = 0;
        virtual ~Factory2() = default;
};

class ModernShape : public Factory2{
    public : 
        unique_ptr<Shape> getShape  (string input)override{
            if(input == "Circle"){
                return make_unique<ModernCircle>();
            }else if(input == "Rectangle"){
                return make_unique<ModernRectangle>();
            }else 
                return nullptr;
        }
};

class ClassicShape : public Factory2{
    public : 
        unique_ptr<Shape> getShape(string input) override{
            if(input == "Circle"){
                return make_unique<ClassicCircle>();
            }else if(input == "Rectangle"){
                return make_unique<ClassicRectangle>();
            }else 
                return nullptr;
        }
};


class Factory1 {
    public : 
        unique_ptr<Factory2> getTypeOfUi(string input){
            if(input == "Modern"){
                return make_unique<ModernShape>();
            }else if(input == "Classic"){
                return make_unique<ModernShape>();
            }else {
                return nullptr;
            }
        }
};


int main(){
    auto f1 = new Factory1();
    auto f2MUI = f1->getTypeOfUi("Modern");
    auto f2CUI = f1->getTypeOfUi("Classic");
    f2MUI->getShape("Circle")->draw();
    f2MUI->getShape("Rectangle")->draw();
    f2CUI->getShape("Circle")->draw();
    f2CUI->getShape("Rectangle")->draw();
}

