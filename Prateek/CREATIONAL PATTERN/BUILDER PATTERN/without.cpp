#include<iostream>
#include<string>

using namespace std;


class House {
    private :
        string foundation;
        string structure;
        string roof;
        bool hasGarage;
        bool hasSwimmingPool;
        bool hasGarden;
    public :
        House(string foundation,string structure,string roof,bool hasGarage,bool hasSwimmingPool,bool hasGarden){
            this->foundation = foundation;// mandatory
            this->structure = structure;// mandatory
            this->roof = roof;// mandatory
            this->hasGarage = hasGarage;
            this->hasSwimmingPool = hasSwimmingPool;
            this->hasGarden = hasGarden;
        }
        void toString(){
           cout << "Foundation: " << foundation << "\n"
         << "Structure: " << structure << "\n"
         << "Roof: " << roof << "\n"
         << "Has Garage: " << (hasGarage ? "Yes" : "No") << "\n"
         << "Has Swimming Pool: " << (hasSwimmingPool ? "Yes" : "No") << "\n"
         << "Has Garden: " << (hasGarden ? "Yes" : "No") << endl;
        }
};
int main(){
    House *hs = new House("concrete","brick","rcc",true,false,true);
    hs->toString();
}