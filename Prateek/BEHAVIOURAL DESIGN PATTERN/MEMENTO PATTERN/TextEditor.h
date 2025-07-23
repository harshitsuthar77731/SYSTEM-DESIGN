#pragma once
#include<string>
#include "Memento.h"
using namespace std;

// this class will be responsible for storing current state of content and method
// will be used for read and write that state

class TextEditor {
    private : 
        string content;
    public :
        void write(string content){
            this->content = content;
        }
        string read(){
            return content;
        }
        // return current snapshot of state
        Memento* makeSnapshot(){
            return new Memento(content);
        }
        void restoreCurrentState(string text){
            this->content = text;
        }
};
