#include<iostream>
using namespace std;
class MediaService;
class Stop;
class Play;
class Pause;

class MediaMode{
    public :
        virtual void currentState() = 0;
        virtual void handlePlay(MediaService *context) = 0;
        virtual void handlePause(MediaService *context) = 0;
        virtual void handleStop(MediaService *context) = 0;
        virtual ~MediaMode() =default;
};

class MediaService{
    private :
        shared_ptr<MediaMode> mode;
    public :
        MediaService(shared_ptr<MediaMode> mode) : mode(mode) {};
        void setMode(shared_ptr<MediaMode> mode){
            this->mode = mode;
        }
        void requestPlay(){
            mode->handlePlay(this);
        }
        void requestStop(){
            mode->handleStop(this);
        }
        void requestPause(){
            mode->handlePause(this);
        }
        void state(){
            mode->currentState();
        }
};

class Play : public MediaMode{
    public :
        void handlePlay(MediaService *context) override;
        void currentState() override;
        void handlePause(MediaService *context) override;
        void handleStop(MediaService *context) override;
};

class Stop : public MediaMode{
    public :
        void currentState() override;
        void handlePlay(MediaService *context) override;
        void handlePause(MediaService *context) override;
        void handleStop(MediaService *context) override;
};

class Pause : public MediaMode{
    public :
        void currentState() override;
        void handlePlay(MediaService *context) override;
        void handlePause(MediaService *context) override;
        void handleStop(MediaService *context) override;
};

        void Play::currentState(){
            cout<<"Playing"<<endl;
        }
        void Play::handlePlay(MediaService *context){
            cout<<"Already playing"<<endl;
        }
        void Play::handlePause(MediaService *context){
            cout<<"Pause the playback"<<endl;
            context->setMode(make_shared<Pause>());
        }
        void Play::handleStop(MediaService *context){
            cout<<"Stop playback and reset position"<<endl;
            context->setMode(make_shared<Stop>());
        }



        void Stop::currentState(){
            cout<<"Stopped"<<endl;
        }
        void Stop::handlePlay(MediaService *context){
            cout<<"Start playing from beginning"<<endl;
            context->setMode(make_shared<Play>());

        }
        void Stop::handlePause(MediaService *context){
            cout<< "Cannot pause when already stopped"<<endl;
        }
        void Stop::handleStop(MediaService *context){
            cout<<"Already stopped"<<endl;

        }








        void Pause::currentState(){
            cout<<"Paused"<<endl;
        }
        void Pause::handlePlay(MediaService *context){
            cout<<"Resume playback"<<endl;
            context->setMode(make_shared<Play>());
        }
        void Pause::handlePause(MediaService *context){
            cout<<"Already paused"<<endl;
        }
        void Pause::handleStop(MediaService *context){
            cout<<"Stop playback and reset position"<<endl;
            context->setMode(make_shared<Stop>());
        }









int main(){
    shared_ptr<MediaService> ms = make_shared<MediaService>(make_shared<Play>());
    ms->requestPlay();
    ms->requestPause();
    ms->requestStop();
    ms->state();

    

}

