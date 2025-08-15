Purpose: Creational patterns are focused on object creation mechanisms, aiming 
to optimize the creation process while ensuring flexibility.
Goal: They abstract the instantiation process to make systems more flexible and 
reusable.
Problem They Solve: Prevent tight coupling between code and object creation logic, 
simplifying the management of new object creation, especially in complex systems.
Example:
● In a system where different types of documents (PDF, Word, Excel) are created, 
instead of using new everywhere, a Factory Pattern can centralize object 
creation.


Application: They are applied in scenarios where:
● You want to separate the instantiation process from usage.
● The exact type of object needed can vary depending on runtime conditions.

Creational Design Patterns (Layman Summary)
	•	They are ways to create objects in a clean, flexible manner.
	•	Focus is on how objects are created, not on what they do.

Main creational design patterns (in simple words):
	1.	Singleton – Only one coffee machine in the office, and everyone uses it. (One instance only)
	2.	Factory Method – You place an order for coffee, and the barista decides how to make it. (Subclass decides object type)
	3.	Abstract Factory – You enter a Starbucks, and depending on your mood (hot/cold), they use the right machine and ingredients. (Factory of factories)
	4.	Builder – You give a list of ingredients (milk, sugar, flavor) and the builder assembles your custom coffee step-by-step. (Step-by-step construction)
	5.	Prototype – You take an existing coffee and make a copy of it instead of starting from scratch. (Cloning existing objects)