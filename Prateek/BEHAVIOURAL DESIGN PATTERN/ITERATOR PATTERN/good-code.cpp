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

class Book {
    private :
        string title;
    public :
        Book(string title) : title(title) {};
        string getBook(){
            return title;
        }
};


class BookCollection {
    private : 
        vector<shared_ptr<Book>>books;
        int position = 0;
    public :
        void addBook(shared_ptr<Book> bookName){
            books.push_back(bookName);
        }
        vector<shared_ptr<Book>> getBook(){
            return books;
        }
        class BookIterator : public Iterator<shared_ptr<Book>>{
            private : 
                int position = 0;
                vector<shared_ptr<Book>> list;
            public :
                BookIterator(vector<shared_ptr<Book>> books){
                    this->list = books;
                }
                bool hasNext() override{
                    return position<list.size();
                }
                shared_ptr<Book> next() override{
                    return list[position++];
                }
        };
        shared_ptr<BookIterator> createIterator(){
            return make_shared<BookIterator>(books);
        }
};

int main(){
    shared_ptr<BookCollection> bc = make_shared<BookCollection>();
    bc->addBook(make_shared<Book>("C++"));
    bc->addBook(make_shared<Book>("python"));
    bc->addBook(make_shared<Book>("java script"));
    auto itr =  bc->createIterator();
    if(itr->hasNext()){
        cout<<itr->next()->getBook()<<endl;
    }
    if(itr->hasNext()){
        cout<<itr->next()->getBook()<<endl;
    }

    if(itr->hasNext()){
        cout<<itr->next()->getBook()<<endl;
    }
}
