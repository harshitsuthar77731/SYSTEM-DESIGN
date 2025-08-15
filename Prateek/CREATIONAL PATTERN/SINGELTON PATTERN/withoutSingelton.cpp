#include<iostream>
#include<string>

using namespace std;

class AppSettings{
    private :
        string dataBaseUrl;
        string apiKey;
    public :
        AppSettings(){
            dataBaseUrl = "234567890";
            apiKey = "123-123-2442";
        }
        string getApiKey(){
            return this->apiKey;
        }
        string getDataBaseURL(){
            return this->apiKey;
        }
};

int main(){
    AppSettings *setting1 = new AppSettings();
    AppSettings *setting2 = new AppSettings();
    // we are creating multiple copy even though we dont required it lead to us as more memory usage
    cout<<setting1->getApiKey()<<endl;
    cout<<setting2->getApiKey()<<endl;
    if(setting1!=setting2){
        cout<<"not equal"<<endl;
    }
}