#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

enum LOGLEVEL {INFO,WARN,ERROR,DEBUG};
string levelToString(LOGLEVEL level) {
    switch (level) {
        case INFO: return "INFO";
        case WARN: return "WARN";
        case ERROR: return "ERROR";
        case DEBUG: return "DEBUG";
    }
    return "UNKNOWN";
}
class Log {
    public :
        string message;
        time_t timeStamp;
        LOGLEVEL level;
        Log(string message,time_t timeStamp, LOGLEVEL level) : message(message),timeStamp(timeStamp) , level(level) {};
};

class LogFormatter {
public:
    virtual ~LogFormatter() = default;
    virtual string format(shared_ptr<Log> log) = 0;
};

class PlainTextFormatter : public LogFormatter {
public:
    string format(shared_ptr<Log> log) override {
        ostringstream oss;
        tm tm_struct;
        localtime_r(&log->timeStamp, &tm_struct);
        oss << "[" << put_time(&tm_struct, "%Y-%m-%d %H:%M:%S") << "] "
            << levelToString(log->level) << ": " << log->message;
        return oss.str();
    }
};

class JsonFormatter : public LogFormatter {
public:
    string format(shared_ptr<Log> log) override {
        ostringstream oss;
        tm tm_struct;
        localtime_r(&log->timeStamp, &tm_struct);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_struct);
        oss << "{"
            << "\"timeStamp\": \"" << buffer << "\", "
            << "\"level\": \"" << levelToString(log->level) << "\", "
            << "\"message\": \"" << log->message << "\""
            << "}";
        return oss.str();
    }
};


class LogAppender {
    public :    
        virtual void append(shared_ptr<Log> log) {};
        virtual ~LogAppender() = default;
};

class ConsoleAppender : public LogAppender{
    private :
        shared_ptr<LogFormatter> formatter;
    public :
        ConsoleAppender(shared_ptr<LogFormatter> formatter) : formatter(formatter) {};
        void append(shared_ptr<Log> log){
            cout<<formatter->format(log)<<endl;
        }
};
class FileAppender : public LogAppender{
    private :
        shared_ptr<LogFormatter> formatter;
        string fileName;
    public :
        FileAppender(shared_ptr<LogFormatter> formatter,string fileName) : formatter(formatter),fileName(fileName) {};
        void append(shared_ptr<Log> log){
            ofstream outFile(fileName, ios::app); // open file in append mode
            if (!outFile) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }
            outFile << formatter->format(log) << endl;
            outFile.close(); // optional as destructor closes file
        }
};

class LogHandler{
    protected :
        vector<shared_ptr<LogAppender>> list;
        shared_ptr<LogHandler> next = nullptr;
    public :
        void attach(shared_ptr<LogAppender> appender){
            list.push_back(appender);
        }
        void detach(shared_ptr<LogAppender> appender){
            list.erase(remove(list.begin(),list.end(),appender),list.end());
        }
        void setNext(shared_ptr<LogHandler> nxt){
            next = nxt;
        }
        virtual bool canHandle(shared_ptr<Log> log)  =0;
        void notify(shared_ptr<Log> log){
            for(auto obs : list){
                obs->append(log);
            }
        }
};

class DebugHandler : public LogHandler{
    public :
        bool canHandle(shared_ptr<Log> log)  {
           if(log->level == DEBUG){
                return true;
            } else if(next) {
                return next->canHandle(log);
            }
            return false;
        };
};
class InfoHandler : public LogHandler{
    public :
        bool canHandle(shared_ptr<Log> log)  {
           if(log->level == INFO){
                return true;
            } else if(next) {
                return next->canHandle(log);
            }
            return false;
        };
};
class ErrorHandler : public LogHandler{
    public :
        bool canHandle(shared_ptr<Log> log)  {
           if(log->level == ERROR){
                return true;
            } else if(next) {
                return next->canHandle(log);
            }
            return false;
        };
};


class Logger {
    private :
        static shared_ptr<Logger> instance;
        shared_ptr<LogHandler> handleChain;
        Logger() {};
    public :
        static shared_ptr<Logger> getInstance(){
            if(!instance) {
                instance = shared_ptr<Logger>(new Logger());
            }
            return instance;
        }
        shared_ptr<Log> log(LOGLEVEL level,string message) {
            return make_shared<Log>(message ,time(nullptr),level);
        }
        void setHandlerChain(shared_ptr<LogHandler> handler) {
            handleChain = handler;
        }
        void Info(string message){
            auto log = this->log(INFO,message);
            if(handleChain->canHandle(log)){
                handleChain->notify(log);
            }
        }
        void Debug(string message){
            auto log = this->log(DEBUG,message);
            if(handleChain->canHandle(log)){
                handleChain->notify(log);
            }
        }
};
 shared_ptr<Logger> Logger::instance = nullptr;

 int main() {
    auto debugHandler = make_shared<DebugHandler>();
    auto infoHandler = make_shared<InfoHandler>();
    auto errorHandler = make_shared<ErrorHandler>();

    debugHandler->setNext(infoHandler);
    infoHandler->setNext(errorHandler);

    auto consoleAppender = make_shared<ConsoleAppender>(make_shared<PlainTextFormatter>());
    auto fileAppender = make_shared<FileAppender>(make_shared<JsonFormatter>(), "logs.txt");

    debugHandler->attach(consoleAppender);
    errorHandler->attach(fileAppender);

    auto logger = Logger::getInstance();
    logger->setHandlerChain(debugHandler);

    logger->Debug("Debug message");
    logger->Info("Info message");
    logger->Debug("Another debug message");
}