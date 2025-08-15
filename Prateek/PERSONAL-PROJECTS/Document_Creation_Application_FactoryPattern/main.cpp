#include<iostream>
#include<string>
#include<memory>
using namespace std;

enum File {DOCX,PDF};

class Document{
    public :
        virtual void open() = 0;
        virtual void save() = 0;
        virtual void close() = 0;
        virtual ~Document() = default;
};

class Pdf : public Document{
    public :
        void open() override{
            cout<<"Opening PDF document "<<endl;
        };
        void save() override{
            cout<<"Saving as .pdf"<<endl;
        };
        void close() override{
            cout<<"Closing document"<<endl;
        };
};

class Doc : public Document{
    public :
        void open() override{
            cout<<"Opening Word document "<<endl;
        };
        void save() override{
            cout<<"Saving as .docx"<<endl;
        };
        void close() override{
            cout<<"Closing document"<<endl;
        };
};




class DocumentFactory{
    private :
        
    public :
        shared_ptr<Document> createDoc(File type){
            switch (type)
            {
                case  DOCX:
                    return make_shared<Doc>();
                case  PDF:
                    return make_shared<Pdf>();
                default:
                    throw invalid_argument("Type not defined");
            }
        }
};

int main(){
    shared_ptr<DocumentFactory> df= make_shared<DocumentFactory>();
    auto file = df->createDoc(PDF);
    file->open();
    file->save();
    file->close();

    file = df->createDoc(DOCX);
    file->open();
    file->save();
    file->close();

}