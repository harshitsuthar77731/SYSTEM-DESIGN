#include <iostream>
#include <string>
#include "CareTaker.h"
#include "TextEditor.h"

using namespace std;






int main(){
    TextEditor te;
    CareTaker ct;
    te.write("Text1");
    ct.saveCurrentState(te);
    cout<<te.read()<<endl;
    te.write("Text2");
    ct.saveCurrentState(te);
    cout<<te.read()<<endl;
    ct.undo(te);
    cout<<te.read()<<endl;

}