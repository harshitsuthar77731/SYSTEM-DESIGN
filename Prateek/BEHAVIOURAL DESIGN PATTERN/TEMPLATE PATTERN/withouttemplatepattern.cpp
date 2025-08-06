#include <iostream>
using namespace std;

class XML{
    public :
        void parse(){
            openFile();
            cout<<"parsing XML file"<<endl;
            closeFile();
        }
        void openFile(){
            cout<<"Opening File"<<endl;
        }
        void closeFile(){
            cout<<"Closing File"<<endl;
        }
};


class JSON{
    public :
        void parse(){
            openFile();
            cout<<"parsing JSON file"<<endl;
            closeFile();
        }
        void openFile(){
            cout<<"Opening File"<<endl;
        }
        void closeFile(){
            cout<<"Closing File"<<endl;
        }
};


int main(){
    XML xmlFile;
    JSON jsonFile;

    xmlFile.parse();
    jsonFile.parse();


}