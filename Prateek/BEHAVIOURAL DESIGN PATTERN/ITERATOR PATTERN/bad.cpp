#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Book {
    private :
        string title;
    public :
        Book(string title) : title(title) {};
        string getBook(){
            return title;
        }
};


class BookCollection{
    private : 
        vector<Book*>books;
    public :
        void addBook(Book* bookName){
            books.push_back(bookName);
        }
        vector<Book*> getBook(){
            return books;
        }
};

int main(){
    BookCollection* bc = new BookCollection();
    bc->addBook(new Book("C++"));
    bc->addBook(new Book("python"));
    bc->addBook(new Book("java script"));
    auto coll =  bc->getBook();
    for(auto itr : coll){
        cout<<"title :- "<<itr->getBook()<<endl;
    }

}
