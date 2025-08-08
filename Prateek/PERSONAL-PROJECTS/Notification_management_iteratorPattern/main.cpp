#include <string>
#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class Iterator{
    public : 
       virtual bool hasNext()= 0;
       virtual T next() = 0;
       virtual ~Iterator() = default;
};

class Notification {
    private :
        string title;
        string message;
        string timestamp;
    public : 
        Notification(string title, string message, string timestamp){
            this->message = message;
            this->timestamp = timestamp;
            this->title = title;
        }   
        void getNotification(){
            cout<<title<<" "<<message<<" On "<< timestamp<<endl;
        }
};

class NotificationCollection {
    private :
        vector<shared_ptr<Notification>> list;
    public :
        void addNotification(shared_ptr<Notification> nf){
            list.push_back(nf);
        }
        class NotificationIterator : public Iterator<shared_ptr<Notification>>{
            private :
                vector<shared_ptr<Notification>> innerlist;
                int position = 0;
            public :
                NotificationIterator(vector<shared_ptr<Notification>> list) : innerlist(list){};
                bool hasNext() override{
                    return position<innerlist.size();
                }
                shared_ptr<Notification> next() override{
                    return innerlist[position++];
                }
        };
        shared_ptr<NotificationIterator> createList(){
            return make_shared<NotificationIterator>(list);
        }
};


class FriendRequest : public Notification{
    public :
        FriendRequest( string user, string timestamp) : Notification("Friend Request",user+" sent you friend request",timestamp){};
        
};

class SystemAlert : public Notification{
    public :
        SystemAlert(string message, string timestamp) : Notification("System Alert",message,timestamp){};
};

int main(){
    shared_ptr<NotificationCollection> nc = make_shared<NotificationCollection>();
    nc->addNotification(make_shared<FriendRequest>("Harshit","10:45 AM"));
    nc->addNotification(make_shared<SystemAlert>("10 percent battery left","11:45 AM"));  
    auto itr = nc->createList();
    if (itr->hasNext()){
        itr->next()->getNotification();
    }
    if (itr->hasNext()){
        itr->next()->getNotification();
    }
    if (itr->hasNext()){
        itr->next()->getNotification();
    }
    

}