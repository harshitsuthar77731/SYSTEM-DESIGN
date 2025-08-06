#include<iostream>
using namespace std;

// interface for command


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


class Command{
    public :
        virtual void execute() = 0;
        virtual ~Command() = default; 
};


class BoldCommand : public Command{
    private :
        shared_ptr<TextEditor>editor;
    public :
        BoldCommand(shared_ptr<TextEditor>te) : editor(te){};
        void execute() override{
            editor->boldText();
        }
};

class ItalicCommand : public Command{
    private :
        shared_ptr<TextEditor>editor;
    public :
        ItalicCommand(shared_ptr<TextEditor>te) : editor(te){};
        void execute() override{
            editor->italicizeText();
        }
};

class UnderlineCommand : public Command{
    private :
        shared_ptr<TextEditor>editor;
    public :
        UnderlineCommand(shared_ptr<TextEditor>te) : editor(te){};
        void execute() override{
            editor->underlineText();
        }
};

class Button{
    private :   
        shared_ptr<Command> cd;
    public :
        Button(shared_ptr<Command>cd) : cd(cd){};
        void click(){
            cd->execute();
        }
};

int main(){
    shared_ptr<TextEditor> editor = make_shared<TextEditor>();
    shared_ptr<BoldCommand> bc = make_shared<BoldCommand>(editor);
    shared_ptr<ItalicCommand> ic = make_shared<ItalicCommand>(editor);
    shared_ptr<UnderlineCommand> uc = make_shared<UnderlineCommand>(editor);

    shared_ptr<Button> boldButton = make_shared<Button>(bc);
    shared_ptr<Button> italicButton = make_shared<Button>(ic);
    shared_ptr<Button> underlineButton = make_shared<Button>(uc);

    boldButton->click();
    italicButton->click();
    underlineButton->click();
}
