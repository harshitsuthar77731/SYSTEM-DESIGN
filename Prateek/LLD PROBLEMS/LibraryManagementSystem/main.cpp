#include<iostream>
#include <chrono>
#include <cmath>
using namespace std;
#include <chrono>
enum BOOKCATEGORY {PREMIUM, REGULAR, RARE};
enum ROLE {ADMIN, GUEST, MEMBER};
enum SEARCH {TITLE, AUTHOR, SUBJECT};

class Book{
    private : 
        int id,isbn;
        string title, author, subject;
        double price;
        BOOKCATEGORY category;
    public : 
        Book(int id, int isbn, string author, string subject, string title, double price, BOOKCATEGORY category) : id(id), isbn(isbn), author(author), subject(subject), title(title), price(price), category(category) {}
        int getId(){return this->id;}
        string getTitle(){return this->title;}
        string getAuthor(){return this->author;}
        string getSubject(){return this->subject;}
        BOOKCATEGORY getCategory(){return this->category;}

        int getIsbn(){return this->isbn;}
};

class BookInventory {
    private : 
        vector<shared_ptr<Book>> bookList;
        mutable std::mutex mtx;
    public :
        const vector<shared_ptr<Book>>&  getBookList() const{
            std::lock_guard<std::mutex> lock(mtx);
            return bookList;
        }
        void addBook(shared_ptr<Book> book){
            std::lock_guard<std::mutex> lock(mtx);
            auto it = find_if(bookList.begin(),bookList.end(),[&](const shared_ptr<Book>& b) {
                              return b->getIsbn() == book->getIsbn(); 
                          });
            if(it == bookList.end()){
                bookList.push_back(book);
                cout<<"Book added : " <<book->getTitle()<<endl;
            }else {
                cout<<"Book already exist : "<<book->getTitle()<<endl;
            }
        }
        void removeBook (int id){
            shared_ptr<Book> removeit;
            for(auto elem : bookList){
                if (elem->getId() == id){
                    removeit = elem;
                    break;
                }
            }
            bookList.erase(remove(bookList.begin(),bookList.end(),removeit),bookList.end());
        }
        BOOKCATEGORY getCategory(int id){
            for(auto elem : bookList){
                if (elem->getId() == id){
                    return elem->getCategory();
                }
            }
        }
    };

class User {
    private :
        string name;
        int uuid;
        ROLE role;
    public :
        User(string name, int uuid, ROLE role) : name(name),uuid(uuid),role(role){};
        string getName(){return this->name;}
        int getUuid(){return this->uuid;}
        ROLE getRole(){return this->role;}
};

class MembershipService{
    private : 
        unordered_map<int,ROLE> memberList;
        unordered_map<int,int> memberLimit;
        unordered_map<ROLE,int> roleLimit;
        unordered_map<ROLE,int> dayLimit;

        mutable std::mutex mtx;
    public :
        MembershipService(unordered_map<ROLE,int> &roleLimit) : roleLimit(roleLimit) {
            for (auto &[role,val] : roleLimit){
                dayLimit[role] = 7; // default
            }
        };
        void updateRole (int userId, ROLE role) {
            memberList[userId] = role;
            roleLimit[role] = userId;
        }
        void addMember(int uuid, ROLE role){
            std::lock_guard<std::mutex> lock(mtx);
            if(!memberList.count(uuid)){
                memberList[uuid] = role;
                memberLimit[uuid] = roleLimit[role];
            }
            else{cout<<"Member already exist \n";}
        }
        void removeMember(int uuid){
            std::lock_guard<std::mutex> lock(mtx);
            memberList.erase(uuid);
            memberLimit.erase(uuid);
        }
        int getLimit(int uuid){
            std::lock_guard<std::mutex> lock(mtx);
            if(!memberList.count(uuid)){ cout << "Member does not exist \n";
            return 0;}
            return memberLimit[uuid];
        }
        void updateDueDate(ROLE role,int day){
            dayLimit[role] = day;
        }
        int getDueDate(ROLE role){
            return dayLimit[role];
        }
        ROLE getRole(int uuid){
            if (!memberList.count(uuid)) {
                cout << "Member does not exist \n";
                return GUEST;   // default fallback
            }
            return memberList[uuid];
        }
};


class Loan {
    private : 
        int userId;
        shared_ptr<Book> book;
        std::chrono::system_clock::time_point dueDate;
    public :
        Loan(int userId, shared_ptr<Book> book,std::chrono::system_clock::time_point dueDate) : userId(userId),book(book),dueDate(dueDate) {};
        std::chrono::system_clock::time_point getDueDate(){
            return this->dueDate;
        }
        shared_ptr<Book> getBook(){
            return book;
        }
};


class LoanService {
    private :
        unordered_map<int,vector<shared_ptr<Loan>>> loans;
        mutable std::mutex mtx;
    public :
        void assignBook(int userId,shared_ptr<Book>book,std::chrono::system_clock::time_point dueDate){
            std::lock_guard<std::mutex> lock(mtx);
            loans[userId].push_back(make_shared<Loan>(userId,book,dueDate));
        }
        void returnBook(int userId,shared_ptr<Book>book){
            std::lock_guard<std::mutex> lock(mtx);
            auto& userLoans = loans[userId];
            userLoans.erase(
                remove_if(userLoans.begin(), userLoans.end(),[&](const shared_ptr<Loan>& l) { return l->getBook()->getId() == book->getId(); }),
                userLoans.end()
            );
        }
        const vector<shared_ptr<Loan>>& getLoans(int userId) const {

            static vector<shared_ptr<Loan>> empty;
            auto it = loans.find(userId);
            if(it != loans.end()) return it->second;
            return empty;
        }

};
class PaymentService{
    private :
        unordered_map<int,double> pendingFines;
        shared_ptr<LoanService> loanService;
        unordered_map<BOOKCATEGORY,double> fineList;
        unordered_map<BOOKCATEGORY,double> subscriptionCharge;
        shared_ptr<MembershipService> membership;
        mutable std::mutex mtx;
    public :
        PaymentService(shared_ptr<MembershipService> membership) : membership(membership) {};
        double calculateCharges(int uuid){
            vector<shared_ptr<Loan>> loans= loanService->getLoans(uuid);
            std::lock_guard<std::mutex> lock(mtx);
            double fineTillNow = 0;
            for(auto loan : loans){
                std::chrono::system_clock::time_point dueDate = loan->getDueDate();
                BOOKCATEGORY category = loan->getBook()->getCategory();

                if(pendingFines.count(uuid)){
                    fineTillNow+=pendingFines[uuid];
                }
                auto now =  std::chrono::system_clock::now();
                if(dueDate>now){
                    auto diff = dueDate - now;
                    auto secondsCount = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
                    double days = ceil(secondsCount / 86400.0);
                    fineTillNow+=days*subscriptionCharge[category];
                }
                
                if(now>dueDate){
                    auto diff = now - dueDate;
                    auto secondsCount =  std::chrono::duration_cast<std::chrono::seconds>(diff).count();
                    double days = ceil(secondsCount / 86400.0);
                    fineTillNow+=days*fineList[category];
                }
            }
            
            return fineTillNow;
        }
        
        double pendingFine (int userId){
            if(pendingFines.count(userId))
                return pendingFines[userId];
            return 0.0;
        }
        void updateFineList(BOOKCATEGORY category, double charge){
            std::lock_guard<std::mutex> lock(mtx);
            fineList[category] = charge;
        }
        void updateSubscriptionList(BOOKCATEGORY category, double charge){
            std::lock_guard<std::mutex> lock(mtx);
            subscriptionCharge[category] = charge;
        }
};




class Observer{
    public : 
        virtual void update(string txt) = 0;
        virtual ~Observer() = default;
};

class Mobile : public Observer{
        public :
            void update(string txt){
                cout<<"Hi book with title :- "<<txt<<" is available \n";
            }
};

class Subject{
    public :
        virtual void addObserver(string title, shared_ptr<Observer> obs) = 0;
        virtual void removeObserver(string title, shared_ptr<Observer> obs) = 0;
        virtual void notifyObserver(string title) = 0;
        virtual ~Subject() = default;
};

class NotificationService : public Subject {
    private :
        unordered_map<string , vector<shared_ptr<Observer>>> observerList;
        mutable std::mutex mtx;
    public : 
        void addObserver(string title, shared_ptr<Observer> obs) override {
            std::lock_guard<std::mutex> lock(mtx);
            auto& vectorList = observerList[title];
            for(auto &elem : vectorList){
                if(elem == obs){
                    cout<<"Observer Already exist\n";
                    return;
                }
            }
            vectorList.push_back(obs);
        };
        void removeObserver(string title, shared_ptr<Observer> obs) override {
            std::lock_guard<std::mutex> lock(mtx);
            if(observerList.count(title)){
                auto& vectorList = observerList[title];
                vectorList.erase(remove(vectorList.begin(),vectorList.end(),obs),vectorList.end());
            }
        };
        void notifyObserver(string title) override {
            if(observerList.count(title)){
                for(auto elem : observerList[title]){
                    elem->update(title);
                }
            }
        };
};

class ReservationService{
    private :   
        shared_ptr<Subject> notificationService;
        unordered_map<string,vector<pair<int,weak_ptr<Observer>>>> reserveList;
        mutable std::mutex mtx;
    public :
        ReservationService(shared_ptr<Subject> notificationService) : notificationService(notificationService) {};
        void reserveBook(string title,int userId, shared_ptr<Observer> obs){
            std::lock_guard<std::mutex> lock(mtx);
            auto &userList = reserveList[title];
            for(auto &elem : userList){
                if(elem.first == userId){
                    cout<<"User already reserved for that Book\n";
                    return;
                }
            }
            userList.push_back({userId,obs});
            notificationService->addObserver(title,obs);
        }
        void bookAvailable(string title){
            std::lock_guard<std::mutex> lock(mtx);
            notificationService->notifyObserver(title);
            auto &userList = reserveList[title];
            for(auto &elem : userList){
                if (auto sp = elem.second.lock()) {  // ✅ lock weak_ptr to check validity
                    notificationService->removeObserver(title, sp);
                }
            }
            reserveList.erase(title);
        }
};

class SearchService{
    private : 
        shared_ptr<BookInventory> inventory;
    public :
        SearchService(shared_ptr<BookInventory> inventory) : inventory(inventory) {};
        const vector<shared_ptr<Book>> search(SEARCH key, string value) const{
            auto& listOfBook = inventory->getBookList();
            vector<shared_ptr<Book>> bookList;
            switch (key)
            {
                case  TITLE:
                    for(auto &elem : listOfBook){
                        if(elem->getTitle() == value) bookList.push_back(elem);
                    }
                    break;
                case  AUTHOR:
                    for(auto &elem : listOfBook){
                        if(elem->getAuthor() == value) bookList.push_back(elem);
                    }
                    break;
                case  SUBJECT:
                    for(auto &elem : listOfBook){
                        if(elem->getSubject() == value) bookList.push_back(elem);
                    }
                    break;
                default:
                    cout<<"No search key defined for given input or no such book exist in inventory";
                    break;
            }
            return bookList;
        }
};

class LibraryManager{
    private :
        shared_ptr<PaymentService> paymentService;
        shared_ptr<LoanService> loanService;
        shared_ptr <ReservationService> reservationService;
        shared_ptr<BookInventory > bookInventory ;
        shared_ptr<SearchService> searchService;
        shared_ptr<MembershipService> membership;
    public :
        LibraryManager(shared_ptr<PaymentService> paymentService,shared_ptr<LoanService> loanService,shared_ptr <ReservationService> reservationService,shared_ptr<BookInventory > bookInventory ,shared_ptr<SearchService> searchService,shared_ptr<MembershipService>membership ) :paymentService(paymentService),loanService(loanService),reservationService(reservationService),bookInventory(bookInventory),searchService(searchService),membership(membership) {};
        const vector<shared_ptr<Book>> searchBook (SEARCH key, string value) {
            return searchService->search(key,value);
        }
        void borrowBook(int userId, int bookId){
            auto bookList = bookInventory->getBookList();
            for (auto book : bookList){
                if(book->getId() == bookId){
                    ROLE role = membership->getRole(userId);
                    int numberOfDays = membership->getDueDate(role);
                    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point dueDate = now + std::chrono::hours(24 * numberOfDays);
                    loanService->assignBook(userId,book,dueDate);
                    return;
                }
            }
            
        } 
        void returnBook (int userId, int bookId){
            auto bookList = bookInventory->getBookList();
            for (auto book : bookList){
                if(book->getId() == bookId){
                    loanService->returnBook(userId,book);
                    return;
                }
            }
        }
        void reserveBook (int userId, string title,shared_ptr<Observer>  obs){
                reservationService->reserveBook(title,userId,obs);
        }

        vector<shared_ptr<Loan>> borrowingHistory(int userId){
            return loanService->getLoans( userId);
        }
        double calculateCharges(int userId){
            paymentService->calculateCharges(userId);
        }
        // Admin Control
        void addBook (shared_ptr<Book>book){
            bookInventory->addBook(book);
        }
        void removeBook (int id) {
            bookInventory->removeBook(id);
        }
        void manageMembership(int userId, ROLE role){
            membership->updateRole(userId,role);
        }
        bool trackOverDue(int userId){
           paymentService->pendingFine(userId);
        }

};





int main(){

}