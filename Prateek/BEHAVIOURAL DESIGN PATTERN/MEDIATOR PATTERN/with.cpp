#include<iostream>
#include<string>
using namespace std;
class User;

class ChatMediator{
    public :
        virtual void sendMessage(string msg,shared_ptr<User> sender) =0;
        virtual void addUser(shared_ptr<User> user) = 0;
        virtual ~ChatMediator() = default;
};

class User : public enable_shared_from_this<User>{
    private :
        string name;
        shared_ptr<ChatMediator> mediator;
    public :
        User(string name,shared_ptr<ChatMediator> mediator) : name(name),mediator(mediator){};
        void send(string msg){
            mediator->sendMessage(msg,shared_from_this());
        }
        void receive(string msg,shared_ptr<User> sender){
            cout<< getName()<< " you got Message :- "<<" "<<msg<<" from "<<sender->getName()<<endl;
        }
        string getName(){
            return this->name;
        }
};


class ChatRoom : public ChatMediator{
    private :
        vector<shared_ptr<User>> userList;
    public :
        void sendMessage(string msg,shared_ptr<User> sender) override{
            for(auto user : userList){
                if(user != sender){
                    user->receive(msg,sender);
                }
            }
        }
        void addUser(shared_ptr<User> user) override{
            userList.push_back(user);
        }
};



int main (){
    shared_ptr<ChatRoom> cm = make_shared<ChatRoom>();
    shared_ptr<User> harshit = make_shared<User> ("Harshit",cm);
    shared_ptr<User> tanu = make_shared<User> ("Tanu",cm);
    shared_ptr<User> david = make_shared<User> ("David",cm);
    cm->addUser(harshit);
    cm->addUser(tanu);
    cm->addUser(david);

    harshit->send("Hi everyone");
}