#include <iostream>        
#include <string>
#include <tuple>
#include "Canvas.h"
#include "CareTaker.h"

int main(){
    Canvas canvas;
    CareTaker ct;
    canvas.addShape("Red","Circle",1,2);
    ct.saveCurrentSnapshot(canvas);
    canvas.getShape();

    canvas.addShape("Blue","Square",3,2);
    ct.saveCurrentSnapshot(canvas);
    canvas.getShape();


    ct.undo(canvas);
    canvas.getShape();

    
    return 0;
}
