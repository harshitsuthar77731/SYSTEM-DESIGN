Consider an example of a transportation service app where users can 
request different types of transport vehicles (e.g., Car, Bike, Bus). You 
might initially create separate classes for each type, and create instances

    Transport *car = new Car();
    Transport *bus = new Bus();

But as the system evolves, managing object creation directly like this can 
become complex, especially when adding new types of vehicles.

1. The client code (i.e., TransportService) is tightly coupled to concrete 
classes (Car, Bike, Bus).
2. Adding new transport types requires modifying client code.

Factory Design Pattern
The Factory Pattern helps centralize the creation logic and delegates the 
responsibility of creating objects to factory classes, which decide the specific 
class to instantiate. This allows the code to adhere to the Open/Closed 
Principle by letting new types of vehicles be added without modifying the 
existing code.


Factory Design Pattern
1. Factory Class: The TransportFactory class contains the logic to 
create different types of transport based on the input string. This abstracts 
the creation logic and makes it easier to add or change transport types.
2. Decoupling: The TransportService class (client) no longer needs to 
know the details of how Car, Bike, or Bus are created. It simply calls the 
factory method.
3. Flexibility: Adding a new transport type (e.g., Truck) only requires 
modifying the factory, not the client code.


Factory Design Benefits

Benefits of Factory Pattern:
1. Loose Coupling: The client is decoupled from the specifics of object 
creation.
2. Single Responsibility Principle: The factory class handles the 
responsibility of object creation.
3. Open/Closed Principle: We can easily add new transport types without 
changing the client code, making the system open to extension and closed 
to modification.


Real World Use Cases

● GUI Frameworks: When the type of button or widget to be created is 
determined at runtime based on the platform (e.g., Windows, macOS, Linux).
● Database Connectivity: When choosing different types of databases (e.g., 
SQL, NoSQL) based on configuration.
● Document Conversion Tools: Where the type of file (e.g., PDF, Word, HTML) 
to be created depends on user input or settings.
The Factory Design Pattern is a fundamental tool to reduce coupling and centralize 
object creation logic, especially in systems that need to support multiple types of 
objects.






1. Factory Pattern — Object Creation Problem
	•	Goal: Hide the complexity of creating objects and decide which class to instantiate based on input/configuration.
	•	When: You want to decouple the client from knowing which concrete class it is using.
	•	Key idea: “Give me the right object, I don’t care how you make it.”
	•	Example in your code:
	•	You pass VEHICLE::CAR to createVehicle().
	•	The factory chooses Car and gives it to you.
	•	The client just calls drive() — no new Car() anywhere outside the factory.

⸻

2. Strategy Pattern — Behavior Selection Problem
	•	Goal: Encapsulate interchangeable behaviors (algorithms) and choose between them at runtime.
	•	When: You want to change how something works without changing the object that uses it.
	•	Key idea: “I already have the object; I just want to change how it behaves.”
	•	Example:
	•	A Transport object might have a RouteStrategy (shortest path, fastest route, scenic route).
	•	You can swap the RouteStrategy while keeping the same Transport object.



    Why they seem similar:
	•	Both use interfaces/abstract classes.
	•	Both involve creating objects that share a common interface.
	•	In simple “toy” code, the factory’s output objects can look like strategy objects because both can be chosen at runtime.

Key difference in mental model:
	•	Factory → “Which object do I build?” (creation stage)
	•	Strategy → “Which algorithm/behavior do I use?” (execution stage)
