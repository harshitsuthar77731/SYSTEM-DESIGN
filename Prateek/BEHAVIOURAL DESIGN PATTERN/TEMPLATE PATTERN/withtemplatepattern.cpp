#include<iostream>
#include<string>

using namespace std;


// abstract class
class ParseTemplate{
    public : 
        void openFile (){
            cout<<"opening file"<<endl;
        }
        void closeFile (){
            cout<<"closing file"<<endl;
        }
        virtual void parsePluggin(){};
        void parse(){
            openFile();
            parsePluggin();
            closeFile();
        }
};

class XML : public ParseTemplate{
    public :
        void parsePluggin() override{
            cout<<"parsing xml file"<<endl;
        }
};

class JSON : public ParseTemplate{
    public :
        void parsePluggin() override{
            cout<<"parsing json file"<<endl;
        }
};


int main(){
    XML xmlFile;
    JSON jsonFile;

    xmlFile.parse();
    jsonFile.parse();


}