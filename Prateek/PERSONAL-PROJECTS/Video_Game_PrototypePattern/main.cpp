#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Prototype{
    public :
    virtual T clone() = 0;
    virtual ~Prototype() = default;
};


class Character : public Prototype<Character*>{
    private :
        string name;
        int health;
        int attackPower;
        int defensePower;
        string specialAbilities;
    public :
        Character(string name,int health,int attackPower,int defensePower,string specialAbilities) : name(name),health(health),attackPower(attackPower),defensePower(defensePower),specialAbilities(specialAbilities){};
        void setName(string name){
            this->name = name;
        }
        void getInfo(){
             cout << "Character Info:\n";
            cout << "Name: " << name << "\n";
            cout << "Health: " << health << "\n";
            cout << "Attack Power: " << attackPower << "\n";
            cout << "Defense Power: " << defensePower << "\n";
            cout << "Special Abilities: " << specialAbilities << "\n";
        }
        Character* clone(){
            return new Character(name,health,attackPower,defensePower,specialAbilities);
        }
};
class GameRegistry {
    private:
        unordered_map<string,Character*> registry;
    public :
        void addRegistry(string type,Character* chr){
            registry[type] = chr;
        }
        Character* getClone(string type){
            if(registry.find(type)!=registry.end()){
                return registry[type]->clone();
            }else{
                throw invalid_argument("Character Type not defined");
            }
            
        }
};

int main(){
    GameRegistry registry;
registry.addRegistry("Warrior", new Character("Default Warrior", 100, 20, 10, "Sword Slash"));
registry.addRegistry("Archer", new Character("Default Archer", 80, 25, 5, "Arrow Rain"));
registry.addRegistry("Mage", new Character("Default Mage", 70, 30, 3, "Fireball"));
    Character* player1 = registry.getClone("Warrior");
    player1->setName("Harshit");
    player1->getInfo();
}