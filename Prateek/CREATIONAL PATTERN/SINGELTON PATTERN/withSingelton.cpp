#include<iostream>
#include<string>

using namespace std;

class AppSettings{
    private :
        string dataBaseUrl;
        string apiKey;
        static AppSettings* instance;
        AppSettings(){
            dataBaseUrl = "234567890";
            apiKey = "123-123-2442";
        }
    public :
        static AppSettings* getInstance(){
            if(instance == nullptr){
                instance = new AppSettings();
            }
            return instance;
        }
        string getApiKey(){
            return this->apiKey;
        }
        string getDataBaseURL(){
            return this->apiKey;
        }
};
AppSettings* AppSettings::instance = nullptr;

int main(){
    AppSettings *setting1 =  AppSettings::getInstance();
    AppSettings *setting2 =  AppSettings::getInstance();
    // we are creating multiple copy even though we dont required it lead to us as more memory usage
    cout<<setting1->getApiKey()<<endl;
    cout<<setting2->getApiKey()<<endl;
    if(setting1!=setting2){
        cout<<"not equal"<<endl;
    }else{
        cout<<"equal"<<endl;
    }
}