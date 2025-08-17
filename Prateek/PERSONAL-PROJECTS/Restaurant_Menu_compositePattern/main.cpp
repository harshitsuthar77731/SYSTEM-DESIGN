#include<iostream>
#include<string>
#include<vector>

using namespace std;


class MenuSystemComponent{
    public :
        virtual void showInfo()=0;
        virtual ~MenuSystemComponent() = default;
};

class Item : public MenuSystemComponent{
    private :
        string itemName;
        int price;
    public :
        Item(string itemName,int price) :itemName(itemName),price(price){};
        void showInfo() override{
            cout<<"Item: "<<itemName<<" - "<<"$"<<price<<endl;
        }
};

class Menu : public MenuSystemComponent{
    private :
        string folderName;
        vector<shared_ptr<MenuSystemComponent>>list;
    public : 
        Menu(string folderName) :folderName(folderName){};
        void addComponent(shared_ptr<MenuSystemComponent> comp){
            if(find(list.begin(), list.end(), comp) == list.end()) {
                list.push_back(comp); // add only if not found
            }
        }; 
        void removeComponent(shared_ptr<MenuSystemComponent> comp){
             auto it = find(list.begin(), list.end(), comp);
             if(it!=list.end()){
                list.erase(it);
             }
        }
        void showInfo() override{
            cout<<"Menu : "<< folderName<<endl;
            for(auto elem : list){
                elem->showInfo();
            }
        }
};


int main(){
    shared_ptr<Menu> mainMenu = make_shared<Menu>("Main");
    shared_ptr<Menu> dinnerMenu = make_shared<Menu>("Dinner Menu");
    shared_ptr<Menu> starterMenu = make_shared<Menu>("Starters");
    shared_ptr<Menu> mainCourseMenu = make_shared<Menu>("Main course");
    shared_ptr<Menu> drinkMenu = make_shared<Menu>("Drink");
    dinnerMenu->addComponent(starterMenu);
    dinnerMenu->addComponent(mainCourseMenu);
    dinnerMenu->addComponent(drinkMenu);
    shared_ptr<Menu> dessertMenu = make_shared<Menu>("Dessert Menu");
    mainMenu->addComponent(dinnerMenu);
    mainMenu->addComponent(dessertMenu);
    shared_ptr<Item> item1 = make_shared<Item>("Soup",5);
    shared_ptr<Item> item2 = make_shared<Item>("Salad",7);
    shared_ptr<Item> item3 = make_shared<Item>("Pasta",12);
    shared_ptr<Item> item4 = make_shared<Item>("Pizza",15);
    shared_ptr<Item> item5 = make_shared<Item>("Coffee",3);
    shared_ptr<Item> item6 = make_shared<Item>("Juice",4);
    shared_ptr<Item> item7 = make_shared<Item>("Ice Cream",6);
    shared_ptr<Item> item8 = make_shared<Item>("Cake",8);
    starterMenu->addComponent(item1);
    starterMenu->addComponent(item2);
    mainCourseMenu->addComponent(item3);
    mainCourseMenu->addComponent(item4);
    drinkMenu->addComponent(item5);
    drinkMenu->addComponent(item6);
    dessertMenu->addComponent(item7);
    dessertMenu->addComponent(item8);
    mainMenu->showInfo();
    dessertMenu->removeComponent(item8);
    mainMenu->showInfo();

}