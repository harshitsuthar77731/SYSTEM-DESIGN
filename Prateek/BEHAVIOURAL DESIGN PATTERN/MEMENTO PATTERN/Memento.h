#pragma once
#include<string>
using namespace std;


// Snapshot
class Memento{
    private : 
        string content;
    public :
        Memento(string text) : content(text) {}; //initialization list
        string readContent(){
            return content;
        }
};
