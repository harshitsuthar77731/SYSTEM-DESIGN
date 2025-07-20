#include<iostream>
using namespace std;

class File{
    public : 
        void write(){
            cout<<"This is write method"<<endl;
        }
        void read(){
            cout<<"This is read method"<<endl;
        }
};

class ReadOnlyFile : public File{
    public : 
        // we are force to write exception because of parent class
        void write(){
            throw invalid_argument("this method is not supported for this instance");
        }
};

class writeOnlyFile : public File{
    
} ;

int main() {

    ReadOnlyFile *rf = new ReadOnlyFile();
    rf->read();
    rf->write();
    return 0;
}