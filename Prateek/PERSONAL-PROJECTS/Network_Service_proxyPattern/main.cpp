#include<iostream>
#include<string>
using namespace std;

class NetworkService{
    public :
        virtual void displayInfo() = 0;
        virtual ~NetworkService() = default;
};

class RealNetworkService : public NetworkService{
    private :
        string apiPath;
        string Info;
    public :    
        RealNetworkService(string path){
            this->apiPath = path;
            loadApi();
        }
        void loadApi(){
            cout<<"loading api info from path:- "<<apiPath<<endl;
            this->Info = "Information from "+apiPath;
        }
        void displayInfo(){
            cout<<Info<<endl;
        }
};

class ProxyNetworkService : public NetworkService {
    private : 
        string apiPath;
        unique_ptr<RealNetworkService>instance;
    public :
        ProxyNetworkService(string path) : apiPath(path){};
        void displayInfo(){
            if(instance==nullptr){
                instance = make_unique<RealNetworkService>(apiPath);
            }
            instance->displayInfo();
        }
};

int main(){
    NetworkService *call1 = new ProxyNetworkService("XYZ");
    NetworkService *call2 = new ProxyNetworkService("ABC");
    call1->displayInfo();
    call1->displayInfo();
    call2->displayInfo();
    call2->displayInfo();
    delete call1;
    delete call2;

}