#include<iostream>
#include<string>
#include<vector>

using namespace std;
class FileSystemComponent{
    public :
        virtual void showDetails()=0;
        virtual ~FileSystemComponent() = default;
};


class File : public FileSystemComponent{
    private : 
        string fileName;
    public :
        File(string name) : fileName(name){};
        void showDetails(){
            cout<<"File name : "<<fileName<<endl;
        }
};

class Folder : public FileSystemComponent{
    private :
        string folderName;
        vector<shared_ptr<FileSystemComponent>>list;
    public :
        Folder(string folderName):folderName(folderName){};
        void addFile(shared_ptr<FileSystemComponent> component){
            list.push_back(component);
        }
        void showDetails(){
            cout<<"Folder Name : "<<folderName<<endl;
            for(auto component : list){
                component->showDetails();
            }
        }
};

int main(){
    shared_ptr<FileSystemComponent> f1 = make_shared<File>("Blob.txt");
    shared_ptr<FileSystemComponent> f2 = make_shared<File>("Code.txt");
    shared_ptr<Folder> folder = make_shared<Folder>("Main Folder");
    folder->addFile(f1);
    folder->addFile(f2);
    shared_ptr<Folder> subFolder = make_shared<Folder>("Sub Folder");
    shared_ptr<FileSystemComponent> f3 = make_shared<File>("Master.txt");
    subFolder->addFile(f3);
    folder->addFile(subFolder);
    folder->showDetails();


}