#include<iostream>
using namespace std;


// abstract class
class ReaderTemplate{
    public :
        void openFile(){
            cout<<"Opening File"<<endl;
        }
        virtual void fetchFile() = 0;
        virtual void formatFile() = 0;
        void writeFormattedFile(){
            cout<<"Writing Formatted File"<<endl;
        }
        void closeFile(){
            cout<<"Closing File"<<endl;
        }
        void readFile(){
            openFile();
            fetchFile();
            formatFile();
            writeFormattedFile();
            closeFile();
        }
        virtual ~ReaderTemplate()=default;
};


class PDF : public ReaderTemplate{
    public :
        void fetchFile() override{
            cout<<"Fetching PDF File"<<endl;
        }
        void formatFile() override{
            cout<<"Formatting PDF File"<<endl;
        }
        ~PDF()=default;

};

class EXCEL : public ReaderTemplate{
    public :
        void fetchFile() override{
            cout<<"Fetching EXCEL File"<<endl;
        }
        void formatFile() override{
            cout<<"Formatting EXCEL File"<<endl;
        }
        ~EXCEL()=default;

};

int main(){
    PDF pdfFIle;
    EXCEL excelFIle;
    pdfFIle.readFile();
    excelFIle.readFile();


}