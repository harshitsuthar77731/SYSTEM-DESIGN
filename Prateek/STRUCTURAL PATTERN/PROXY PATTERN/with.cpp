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


class ProxyImage : public Image{
    private :
        string path;
        unique_ptr<RealImage> instance;
    public :
        ProxyImage(string path):path(path){};
        void display(){
            if(instance == nullptr){
                instance = make_unique<RealImage>(path);
            }
            instance->display();
        }
};


int main(){
    // here we are caching and doing lazy loading 
    Image *ri1 = new ProxyImage("Dog.png");
    Image *ri2 = new ProxyImage("Dog.png");

    ri1->display();
    ri1->display();
    ri2->display();

    delete ri1;
    delete ri2;


}