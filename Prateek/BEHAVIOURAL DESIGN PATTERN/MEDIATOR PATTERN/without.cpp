#include <iostream>
#include<string>
using namespace std;

class User{
    private :
        string name;
    public :
        User(string name) : name(name){};
        void sendMessage(string msg, User *to){
            cout<<getName()<<" "<<"sending"<<" "<<msg<<" to "<<to->getName()<<endl;
        }
        string getName(){
            return this->name;
        }
};


int main(){
    User *rahul = new User("Rahul");
    User *vijay = new User("Vijay");
    User *david = new User("David");
    rahul->sendMessage("How are you", vijay);
    david->sendMessage("How are you", vijay);
    rahul->sendMessage("How are you", david);
}