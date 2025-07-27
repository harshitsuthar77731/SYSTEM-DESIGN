#include<iostream>
using namespace std;

class RendererStrategy{
    public :
        virtual string render(const string& text)=0 ;
        virtual ~RendererStrategy() = default;
};

class FlexiText{
    private :
        string inputString;
    public :
        void setString(string text){
            this->inputString = text;
        }
        string getString(shared_ptr<RendererStrategy>strategy){
            return strategy->render(inputString);
        }
};

class PlainText : public RendererStrategy{
    public :
        string render(const string& inputText) override{
            return inputText;
        }
};
class BoldText : public RendererStrategy{
    public :

    string render(const string& inputText) override{
        return "**"+inputText+"**";
    }
};
class HTMLText : public RendererStrategy{
    public :

    string render(const string& inputText) override{
        return "<b>"+inputText+"<b>";
    }
};
class UpperCaseText : public RendererStrategy{
    public :
    string render(const string& inputText) override{
        string modified =inputText;
        transform(modified.begin(), modified.end(), modified.begin(), ::toupper);
        return modified;
    }
};


int main(){
    shared_ptr<FlexiText> ft = make_shared<FlexiText>();
    ft->setString("Hello, World!");
    cout<<ft->getString(make_shared<PlainText> ())<<endl;
    cout<<ft->getString(make_shared<BoldText> ())<<endl;
    cout<<ft->getString(make_shared<HTMLText> ())<<endl;
    cout<<ft->getString(make_shared<UpperCaseText> ())<<endl;

}