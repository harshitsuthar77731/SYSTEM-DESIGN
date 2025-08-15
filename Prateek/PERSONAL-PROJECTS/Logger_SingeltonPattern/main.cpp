#include<iostream>     // For input-output operations (cout)
#include<string>       // For using std::string
#include <memory>      // For smart pointers (std::unique_ptr)
#include <mutex>       // For std::mutex and std::lock_guard (thread-safety)
using namespace std;

// Global mutex for thread safety in getInstance()
mutex mtx;

class Logger {
    private:
        // Static unique_ptr to hold the single instance of Logger
        static unique_ptr<Logger> instance;

        // Private constructor so that object can't be created from outside
        Logger() {};

    public:
        // Delete copy constructor to prevent copying the singleton instance
        Logger(const Logger&) = delete;

        // Delete assignment operator to prevent assigning the singleton instance
        Logger& operator=(const Logger&) = delete;

        // Static method to get the singleton instance
        static Logger* getInstance() {
            // First check without locking (improves performance if already created)
            if (instance == nullptr) { 
                // Lock mutex to prevent race condition in multithreaded scenarios
                lock_guard<mutex> lock(mtx);

                // Double-check inside the lock to avoid creating multiple instances
                if (instance == nullptr) { 
                    // Create the singleton instance (calling private constructor is allowed here)
                    instance = unique_ptr<Logger>(new Logger);
                }
            }

            // Return raw pointer (unique_ptr manages lifetime internally)
            return instance.get();
        }

        // Method to log informational messages
        void logInfo(string input) {
            cout << "[INFO] " << input << endl;
        }

        // Method to log warning messages
        void logWarning(string input) {
            cout << "[WARNING] " << input << endl;
        }

        // Method to log error messages
        void logError(string input) {
            cout << "[ERROR] " << input << endl;
        }
};

// Initialize the static unique_ptr with nullptr
unique_ptr<Logger> Logger::instance = nullptr;

int main() {
    // Get singleton instance
    Logger* log1 = Logger::getInstance();
    Logger* log2 = Logger::getInstance();

    // Log a message
    log1->logInfo("Application started");

    // Both log1 and log2 point to the same instance
}