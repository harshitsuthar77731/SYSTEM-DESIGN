#include<iostream>
#include<string>
#include<vector>

using namespace std;

class File{
    private : 
        string fileName;
    public :
        File(string name) : fileName(name){};
        void showDetails(){
            cout<<"File name : "<<fileName<<endl;
        }
};

class Folder{
    private :
        string folderName;
        // issue with that we can't add different type of class like folder because a folder can consist of folder
        vector<File*>list;
    public :
        Folder(string folderName):folderName(folderName){};
        void addFile(File* fl){
            list.push_back(fl);
        }
        void showDetails(){
            cout<<"Folder Name : "<<folderName<<endl;
            for(auto fl : list){
                fl->showDetails();
            }
        }
};

int main(){
    File *f1 = new File("Blob.txt");
    File *f2 = new File("Code.txt");
    Folder *folder = new Folder("Main Folder");
    folder->addFile(f1);
    folder->addFile(f2);
    folder->showDetails();

}