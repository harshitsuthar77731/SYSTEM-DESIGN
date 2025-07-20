#include<iostream>
using namespace std;


class Readable{
    public :
        virtual void read() = 0;
        ~Readable() =default;
};
class Writable{
    public :
        virtual void write() = 0;
        ~Writable() =default;
};

class ReadableFile : public Readable{
    public : 
       void read(){
        cout<<"This method is for read"<<endl;
       }
};

class WritableFile : public Readable , public Writable{
    public : 
       void read(){
        cout<<"This method is for read"<<endl;
       }
       void write(){
        cout<<"This method is for write"<<endl;
       }
};

class ReadOnlyFile {
    public :
        void read(Readable* fileType){
            fileType->read();
        }
        
};

int main(){
    ReadableFile * rf = new ReadableFile();
    WritableFile * wf = new WritableFile();
    ReadOnlyFile *rof = new ReadOnlyFile();
    rof->read(rf);
    rof->read(wf);
    rf->read();
    wf->read();
    wf->write();


    return 0;
}