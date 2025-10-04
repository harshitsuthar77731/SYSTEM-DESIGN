#include <iostream>
using namespace std;

enum CATEGORY { BEVERAGES, SNACKS, CHOCOLATE };

class VendingMachine;

class PaymentStrategyInterface {
    public:
        virtual void processPayment(VendingMachine *vm, double) {};
        virtual ~PaymentStrategyInterface() = default;
};

class UPI : public PaymentStrategyInterface {
    public:
        void processPayment(VendingMachine *vm, double amt) override;
};

class Cash : public PaymentStrategyInterface {
    public:
        void processPayment(VendingMachine *vm ,double amt) override ;
};




class Product {
    private:
        int id;
        double price;
        CATEGORY category;
        string name;

    public:
        Product(int id, string name, CATEGORY cat, double price) : id(id), name(name), category(cat), price(price) {}
        string getName() { return this->name; }
        CATEGORY getCategory() { return this->category; }
        double getPrice() { return this->price; }
        int getId() { return this->id; }
};

class ProductInventory {
    private : 
        unordered_map<CATEGORY,vector<shared_ptr<Product>>>inventory;
    public :
        void addProduct(shared_ptr<Product> prod){
            if (!inventory.count(prod->getCategory())) inventory[prod->getCategory()] = {};
            for(auto p : inventory[prod->getCategory()]){
                if(p->getId()==prod->getId()){
                    cout<<"Product Already exist \n";
                    return;
                }
            }
            inventory[prod->getCategory()].push_back(prod);
        }
        void removeProduct(shared_ptr<Product> prod){
            inventory[prod->getCategory()];
            if(inventory.count(prod->getCategory())){
                auto &list = inventory[prod->getCategory()];
                list.erase(remove_if(list.begin(), list.end(),[&](auto &p){ return p->getId() == prod->getId(); }),list.end());
                return;
            }
            cout<<"Product Category Don't exist \n";
            return;
        }
        double getPrice(int id){
            for(auto &[cat,list] : inventory){
                for(auto p : list){
                    if(p->getId()==id){
                        return p->getPrice();
                    }
                }
            }
            return 0;
        }
        shared_ptr<Product> getProductById(int id){
            for(auto &[cat,list] : inventory){
                for(auto p : list){
                    if(p->getId()==id){
                        return p;
                    }
                }
            }
            return nullptr;
        }
        const vector<shared_ptr<Product>> getByCategory(CATEGORY cat) const{
            vector<shared_ptr<Product>> empty;
            auto it = inventory.find(cat);
            if(it != inventory.end()){
                return it->second;
            }
            return empty;
        }
};

class DisplayService {
    private : 
        shared_ptr<ProductInventory> inventory;
    public :
        DisplayService(shared_ptr<ProductInventory> inventory) : inventory(inventory) {};
        void displayByCategory(CATEGORY cat){
            auto lis  = inventory->getByCategory(cat);
            cout<<"Displaying for Category " <<cat<<endl;
            for(auto elem : lis){
                cout<<"Name of product "<<elem->getName()<<" id :- "<<elem->getId()<<" price :- "<<elem->getPrice()<<endl;
            }
        }
};

class State {
    public :
        virtual void insertCoin(VendingMachine *vm, double amt) {};
        virtual void selectProduct(VendingMachine *vm, int id) {};
        virtual void enter(VendingMachine *vm) {};
        virtual void cancel(VendingMachine *vm) {};
        virtual ~State() = default;
};

class IdleState  ;
class HasMoneyState ;
class DispensingState ;


class IdleState : public State {
    public :
        void insertCoin(VendingMachine *vm, double amt) override;
        void selectProduct(VendingMachine *vm, int id) override;
        void cancel(VendingMachine *vm) override;
        void enter(VendingMachine *vm) override;
};
class HasMoneyState : public State {
    public :
        void insertCoin(VendingMachine *vm, double amt) override;
        void selectProduct(VendingMachine *vm, int id) override;
        void cancel(VendingMachine *vm) override;
        void enter(VendingMachine *vm) override;
};
class DispensingState : public State {
    public :
        void insertCoin(VendingMachine *vm, double amt) override;
        void selectProduct(VendingMachine *vm, int id) override;
        void enter(VendingMachine *vm) override;
        void cancel(VendingMachine *vm) override;
};


class VendingMachine {
    private :
        double money = 0;
        int selectedProduct = -1;
        shared_ptr<State> state;
        shared_ptr<PaymentStrategyInterface> paymentStrategy;
        shared_ptr<ProductInventory>inventory;
        shared_ptr<DisplayService> display;

    public :
        VendingMachine(){
            this->state = make_shared<IdleState>();
            this->inventory = make_shared<ProductInventory>();
            this->display = make_shared<DisplayService>(this->inventory);
        }
        void setPaymentStrategy(shared_ptr<PaymentStrategyInterface>newPaymentState){
            this->paymentStrategy = newPaymentState;
        }
        void setState(shared_ptr<State>state){
            this->state = state;
        }
        void addMoney(double amt){
            this->money+=amt;
        }
        void insertCoin(double amt) {
            state->insertCoin(this,amt);
        }
        void processPayment(double amt){
            this->paymentStrategy->processPayment(this,amt);
        }
        void selectProduct( int id) {
            state->selectProduct(this,id);
        }
        void cancel() {
            state->cancel(this);
        }
        void enter() {
            state->enter(this);
        }
        void selectGivenProduct(int id){
            this->selectedProduct = id;
        }
        void deductMoney(double amt){
            this->money-=amt;
        }
        bool hasEnough(int id){
            double price = inventory->getPrice(id);
            if(price<=this->money){
                return true;
            }
            return false;
        }
        void completeTransaction(){
            auto prod = inventory->getProductById(this->selectedProduct);
            this->money-=prod->getPrice();
            inventory->removeProduct(prod);
            cout<<"Here is your ordered product and remaining money "<<this->money<<endl;
            this->money = 0;
        }
        void refund(){
            cout<<"Refunding money "<<this->money<<endl;
            this->money = 0;
            this->selectedProduct = -1;
            return;
        }
        void displayProduct(CATEGORY cat){
            this->display->displayByCategory(cat);
        }
        void addProduct(shared_ptr<Product> prod){
            this->inventory->addProduct(prod);
        }
};



        void IdleState :: insertCoin(VendingMachine *vm, double amt) {
            vm->addMoney(amt);
            vm->setState(make_shared<HasMoneyState>());
        }
        void IdleState :: selectProduct(VendingMachine *vm, int id) {
            cout<<"Currently in idle state in first insert coin \n";
        }
        void IdleState :: cancel(VendingMachine *vm) {
            cout<<"Currently in idle state in no product to cancel \n";
        }
        void IdleState :: enter(VendingMachine *vm) {
            cout<<"Currently in idle state can't enter \n";
        }

        void  HasMoneyState :: insertCoin(VendingMachine *vm, double amt) {
            vm->addMoney(amt);
        }
        void HasMoneyState :: selectProduct(VendingMachine *vm, int id) {
            if(vm->hasEnough(id)){
                vm->setState(make_shared<DispensingState>());
                vm->selectGivenProduct(id);
            }else{
                cout<<"Not Enough money insert more coin "<<endl;
            }
        }
        void HasMoneyState :: cancel(VendingMachine *vm) {
            cout<<"Cancelling transaction"<<endl;
            vm->setState(make_shared<IdleState>());
            vm->refund();
            return;
        }
        void HasMoneyState :: enter(VendingMachine *vm) {
            cout<<"Currently in check money state can't enter \n";
        }

        void  DispensingState :: insertCoin(VendingMachine *vm, double amt) {
            cout<<"In dispensing state cannot insert coin"<<endl;
        }
        void DispensingState :: selectProduct(VendingMachine *vm, int id) {
            cout<<"Product already selected"<<endl;
        }
        void DispensingState :: enter(VendingMachine *vm) {
            vm->completeTransaction();
            vm->setState(make_shared<IdleState>());
        }
        void DispensingState :: cancel(VendingMachine *vm) {
            cout<<"Cancelling transaction"<<endl;
            vm->setState(make_shared<IdleState>());
            vm->refund();
            return;
        }


void UPI :: processPayment(VendingMachine *vm, double amt) {
            cout<<"Processing payment through UPI\n";
            vm->insertCoin(amt);
        }
void Cash :: processPayment(VendingMachine *vm, double amt) {
            cout<<"Processing payment through Cash\n";
            vm->insertCoin(amt);
        }




int main() {
    // Create Vending Machine
    auto vm = make_shared<VendingMachine>();

    // Add products
    auto coke = make_shared<Product>(1, "Coke", BEVERAGES, 40.0);
    auto pepsi = make_shared<Product>(2, "Pepsi", BEVERAGES, 35.0);
    auto chips = make_shared<Product>(3, "Lays Chips", SNACKS, 25.0);
    auto dairyMilk = make_shared<Product>(4, "Dairy Milk", CHOCOLATE, 50.0);

    vm->addProduct(coke);
    vm->addProduct(pepsi);
    vm->addProduct(chips);
    vm->addProduct(dairyMilk);

    // Display all products category-wise
    cout << "\n=== Displaying Products ===\n";
    vm->displayProduct(BEVERAGES);
    vm->displayProduct(SNACKS);
    vm->displayProduct(CHOCOLATE);

    // Select payment strategy (UPI)
    vm->setPaymentStrategy(make_shared<UPI>());
    cout << "\n=== Starting Transaction with UPI ===\n";

    // Try to buy Dairy Milk
    cout << "Inserting ₹30 first...\n";
    vm->processPayment(30); // Not enough
    vm->selectProduct(4);   // Should say not enough money

    cout << "Inserting ₹30 more...\n";
    vm->processPayment(30); // Now total = 60
    vm->selectProduct(4);   // Should trigger dispensing

    cout << "\n=== Entering Dispensing State ===\n";
    vm->enter();            // Completes transaction

    cout << "\n=== Trying Refund After Completion (Should Reset) ===\n";
    vm->refund();           // Should refund 0

    // Try Cash payment next
    vm->setPaymentStrategy(make_shared<Cash>());
    cout << "\n=== Starting Transaction with Cash ===\n";
    vm->processPayment(50); // Insert enough for Lays
    vm->selectProduct(3);
    vm->enter();

    // Try cancel mid-way
    cout << "\n=== Testing Cancel Flow ===\n";
    vm->processPayment(20);
    vm->cancel();           // Should refund and reset

    cout << "\n=== Test Completed Successfully ===\n";
    return 0;
}