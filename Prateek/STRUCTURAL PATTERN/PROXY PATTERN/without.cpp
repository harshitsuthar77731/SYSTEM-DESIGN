#include<iostream>
#include<string>
using namespace std;

class Image{
    public :
        virtual void display()=0;
        virtual ~Image() = default;
};

class RealImage : public Image{
    private :
        string path;
    public :
        RealImage(string path){
            this->path = path;
            loadImage();
        }
        void loadImage(){
            cout<<"loading image from "<<path<<endl;
        }
        void display(){
            cout<<"Displaying Image "<<path<<endl;
        }
};

int main(){
    // issue with this 
    // 1 we are loading same image two time highly cpu intensive process
    // What we want is lazy loading when we want to display image than load image and if image already loaded than do caching of it  
    RealImage *ri1 = new RealImage("Dog.png");
    RealImage *ri2 = new RealImage("Dog.png");

    ri1->display();
    ri1->display();

}