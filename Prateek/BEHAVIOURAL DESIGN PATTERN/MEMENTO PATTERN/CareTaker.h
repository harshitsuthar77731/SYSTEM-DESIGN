#pragma once
#include<string>
#include "Memento.h"
#include "TextEditor.h"
#include<stack>
using namespace std;
// maintaining snapshot
class CareTaker{
    private :
        stack<Memento*> history;
    public :
        void saveCurrentState(TextEditor& editor){
            history.push(editor.makeSnapshot());
        }
        void undo(TextEditor& editor){
            if(!history.empty()){
                history.pop();
                if(!history.empty()){
                    editor.restoreCurrentState(history.top()->readContent());
                }else{
                    editor.restoreCurrentState("");
                }
            }else{
                editor.restoreCurrentState("");
            }
        }
};

