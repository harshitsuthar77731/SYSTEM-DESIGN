#include <iostream>
#include <string>
using namespace std;

class Meal{
    private :
        string mainItem; // mandatory
        string drink;
        string side;
        string dessert;
    public :    
        Meal(const string& mainItem, const string& drink,const string& side,const string& dessert) : mainItem(mainItem),drink(drink),side(side), dessert(dessert) {};
        void toString(){
            cout << "Main Item: " << mainItem << endl;
            cout << "Drink: " << drink << endl;
            cout << "Side: " << side << endl;
            cout << "Dessert: " << dessert << endl;
        }
        class MealBuilder{
            private :
                string mainItem; // mandatory
                string drink = "";
                string side = "";
                string dessert = "";
            public :
                MealBuilder(const string& mainItem) : mainItem(mainItem){};
                MealBuilder& setDrink(const string& drink){
                    this->drink = drink;
                    return *this;
                }
                MealBuilder& setSide(const string& side){
                    this->side = side;
                    return *this;
                }
                MealBuilder& setDessert(const string& dessert){
                    this->dessert = dessert;
                    return *this;
                }
                Meal* build(){
                    return new Meal(mainItem,drink,side,dessert);
                }
                
        };

};

int main(){
    Meal* happyMeal = Meal::MealBuilder("Burger").setDessert("Cake").build();
    happyMeal->toString();
}