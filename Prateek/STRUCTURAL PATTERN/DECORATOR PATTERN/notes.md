Decorator Pattern
You need to add functionality to an object at runtime, but subclassing would lead to 
an explosion of subclasses or is impractical.


Decorator Pattern
Let’s say we have a simple Pizza ordering system. Initially, we just have plain pizza 
but now we want to add options such as cheese, olives, tomatoes and mushrooms 
without modifying the existing pizza class or creating multiple subclasses.
Let's use the Decorator Pattern using a Pizza making example where different 
toppings (like cheese, olives, tomatoes, etc.) can be dynamically added to the base 
pizza.


Decorator Pattern
Problem: In a system where you need to dynamically extend or add behavior to 
objects, inheritance can lead to inflexible and tightly coupled code.
Solution: The Decorator Pattern allows you to add new functionality to objects at 
runtime by wrapping them with decorator classes, providing flexibility
Real-world analogy:
● A pizza order where you start with a basic pizza and add toppings dynamically 
(e.g., cheese, pepperoni) without modifying the original pizza class.



Decorator Pattern
Flexible and Scalable: You can add as many toppings as needed by simply creating a 
decorator for each topping. No need for subclassing every combination.
Single Responsibility Principle: Each decorator class has one responsibility — to add a 
specific topping.
Open/Closed Principle: The BasicPizza class remains unchanged, and new features 
(toppings) can be added by creating new decorators.
Dynamically Changeable: Decorators can be added or removed dynamically at runtime.
Combinatorial Freedom: You can mix and match toppings in any order, making the system 
more flexible and reusable.



Decorator vs Inheritance
● Inheritance is static and applied at compile-time, leading to tight coupling 
between base and derived classes.
● Decorator Pattern provides a more flexible way to add or remove behavior at 
runtime without changing the underlying object.