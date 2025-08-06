#include<iostream>
using namespace std;

class TextEditor{
    public :
        void boldText(){
            cout<<"This text is bold"<<endl;
        }
        void underlineText(){
            cout<<"This text is underline"<<endl;
        }
        void italicizeText(){
            cout<<"This text is italicize"<<endl;
        }
};

class BoldButton{
    private :
        TextEditor *editor;
    public:
        BoldButton(TextEditor *editor):editor(editor){};
        void onClick( ){
            editor->boldText();
        }
};

class ItalicButton{
    private :
        TextEditor *editor;
    public:
        ItalicButton(TextEditor *editor):editor(editor){};
        void onClick( ){
            editor->italicizeText();
        }
};

int main(){
    TextEditor *te = new TextEditor();
    BoldButton *bb = new BoldButton(te);
    ItalicButton *ib = new ItalicButton(te);
    bb->onClick();
    ib->onClick();
}