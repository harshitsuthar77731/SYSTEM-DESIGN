#include <iostream>
#include <string>
#include <map>

using namespace std;

class Invoice {
    private :
        long long amount;
    public :
        Invoice(long long amount){
            this->amount = amount;
        }
         void generateInvoice(){
            cout<<"Invoice genrated";
        }
};

class EmailService{
    public :
     void sendEmailNotification(){
            cout<<"Sending Email Notification sent to user";
        }
};

class InvoiceRepository{
    public :
     void saveToDatabase(){
            cout<<"Invoice added to db";
        }
};


int main() {
    // Create an invoice
    Invoice invoice(100.0);
    
    // Generate the invoice
    invoice.generateInvoice();
    
    // Save to database using repository
    InvoiceRepository repository;
    repository.saveToDatabase();
    
    // Send email notification
    EmailService emailService;
    emailService.sendEmailNotification();
    
    return 0;
} 