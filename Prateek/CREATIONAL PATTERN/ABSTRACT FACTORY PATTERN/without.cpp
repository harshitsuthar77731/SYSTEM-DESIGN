#include<iostream>
#include<string>
#include<memory>
using namespace std;

class WindowScrollBAR{
    public :
        void scroll(){
            cout<<"scrolling window scroll bar"<<endl;
        }
};
class WindowButton{
    public :
        void render(){
            cout<<"window Button"<<endl;
        }
};

class MACScrollBAR{
    public :
        void scroll(){
            cout<<"scrolling Mac scroll bar"<<endl;
        }
};
class MACButton{
    public :
        void render(){
            cout<<"Mac Button"<<endl;
        }
};



int main(){
    WindowScrollBAR *ws = new WindowScrollBAR();
    WindowButton *wb = new WindowButton();
}