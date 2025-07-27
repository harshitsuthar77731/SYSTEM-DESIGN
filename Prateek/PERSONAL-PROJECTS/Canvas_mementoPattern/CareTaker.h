#pragma once
#include <iostream>        
#include <string>
#include <tuple>
#include <stack>
#include "Memento.h"
#include "Canvas.h"
using namespace std;

class CareTaker{
    private : 
        stack<Memento*>history;
    public : 
        void saveCurrentSnapshot(Canvas &canvas){
            history.push(canvas.saveCurrentState());
        }
        void undo(Canvas &canvas){
            if(!history.empty()){
                history.pop();
                if(!history.empty()){
                    canvas.restorState(history.top());
                }
            }
        }

};