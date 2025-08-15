#include <iostream>
#include <string>
using namespace std;

// House class represents the final product to be built
class House {
private:
  // Mandatory & optional attributes of the house
  string foundation;
  string structure;
  string roof;
  bool hasGarage;
  bool hasSwimmingPool;
  bool hasGarden;

public:
  // Constructor for House - initializes all attributes
  House(string foundation, string structure, string roof,
        bool hasGarage, bool hasSwimmingPool, bool hasGarden) {
    this->foundation = foundation;   // mandatory attribute
    this->structure = structure;     // mandatory attribute
    this->roof = roof;               // mandatory attribute
    this->hasGarage = hasGarage;     // optional
    this->hasSwimmingPool = hasSwimmingPool; // optional
    this->hasGarden = hasGarden;     // optional
  }

  // Utility method to display the house details
  void toString() {
    cout << "Foundation: " << foundation << "\n"
         << "Structure: " << structure << "\n"
         << "Roof: " << roof << "\n"
         << "Has Garage: " << (hasGarage ? "Yes" : "No") << "\n"
         << "Has Swimming Pool: " << (hasSwimmingPool ? "Yes" : "No") << "\n"
         << "Has Garden: " << (hasGarden ? "Yes" : "No") << endl;
  }

  // Nested Builder class to construct House objects
  class HouseBuilder {
  private:
    // Same attributes as House, but with default values for optional ones
    string foundation; // mandatory
    string structure;  // mandatory
    string roof;       // mandatory
    bool hasGarage = false;         // optional default
    bool hasSwimmingPool = false;   // optional default
    bool hasGarden = false;         // optional default

  public:
    // Constructor for mandatory fields
    HouseBuilder(string foundation, string structure, string roof) {
      this->foundation = foundation;
      this->structure = structure;
      this->roof = roof;
    }

    // Optional setters - return reference for method chaining
    HouseBuilder &setGarage(bool hasGarage) {
      this->hasGarage = hasGarage;
      return *this; // enables chaining
    }
    HouseBuilder &setSwimmingPool(bool hasSwimmingPool) {
      this->hasSwimmingPool = hasSwimmingPool;
      return *this;
    }
    HouseBuilder &setGarden(bool hasGarden) {
      this->hasGarden = hasGarden;
      return *this;
    }

    // Final step - create a House object with collected parameters
    House *build() {
      return new House(foundation, structure, roof,
                       hasGarage, hasSwimmingPool, hasGarden);
    }
  };
};

int main() {
  // Create a House using Builder pattern
  // Mandatory parameters in constructor + optional ones using chainable setters
  House *hs = House::HouseBuilder("Concrete", "Steel", "RCC")
                  .setGarage(true) // optional
                  .build();        // builds the final object

  // Print the details of the constructed House
  hs->toString();
}