#include<iostream>
#include<string>
#include<memory>
using namespace std;


class Button {
    public :
        virtual void render() = 0;
        virtual ~Button() = default;
};

class Scroll {
    public :
        virtual void scroll() = 0;
        virtual ~Scroll() = default;
};

class WindowScrollBAR : public Scroll{
    public :
        void scroll() override{
            cout<<"scrolling window scroll bar"<<endl;
        }
};
class WindowButton : public Button{
    public :
        void render() override{
            cout<<"window Button"<<endl;
        }
};

class MACScrollBAR : public Scroll{
    public :
        void scroll() override{
            cout<<"scrolling Mac scroll bar"<<endl;
        }
};
class MACButton : public Button{
    public :
        void render() override{
            cout<<"Mac Button"<<endl;
        }
};


class UIFactory{
    public :
        virtual shared_ptr<Button> createButton() = 0;
        virtual shared_ptr<Scroll> createScrollBar() = 0;
        virtual ~UIFactory() = default;
};


class WindowFactory : public UIFactory {
    public :
        shared_ptr<Button> createButton() override{
            return make_shared<WindowButton>();
        }
        shared_ptr<Scroll> createScrollBar() override{
            return make_shared<WindowScrollBAR>();
        }
};

class MacFactory : public UIFactory{
    public :
        shared_ptr<Button> createButton() override{
            return make_shared<MACButton>();
        }
        shared_ptr<Scroll> createScrollBar() override{
            return make_shared<MACScrollBAR>();
        }
};


class Application{
    private :
        shared_ptr<Button>button;
        shared_ptr<Scroll>scrollbar;
    public:
    Application(shared_ptr<UIFactory> type){
        this->button = type->createButton();
        this->scrollbar = type->createScrollBar();
    }
    void render(){
       this->button->render();
    }
    void scroll(){
        this->scrollbar->scroll();
    }
};

int main(){
    shared_ptr<Application> app = make_shared<Application>(make_shared<WindowFactory>());
    app->scroll();
    app->render();

}