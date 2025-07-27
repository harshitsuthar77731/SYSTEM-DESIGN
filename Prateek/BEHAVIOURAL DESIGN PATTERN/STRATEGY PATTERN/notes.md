MOTIVATION Behind this pattern

Let's consider a simple payment system where users can pay using different methods like credit cards or PayPal. Without the Strategy Pattern, you might use if-else conditions to handle the different payment methods, leading to less maintainable and flexible code.


Problem without strategy 
● The PaymentService class has multiple responsibilities (deciding the 
payment type and processing it).
● Adding a new payment method requires modifying the PaymentService
class.
● The use of if-else conditions can make the code harder to maintain as more 
payment types are added.
With the Strategy Pattern, the logic for each payment type is encapsulated in separate strategy 
classes, and the PaymentService (context class) delegates the task of payment processing to one 
of these strategies at runtime.


Problem: Hardcoded algorithms in classes lead to:
○ Code duplication.
○ Increased maintenance complexity when switching between algorithms.
○ Violation of Open/Closed Principle: Modifications are required every 
time a new algorithm is introduced.
Solution: The Strategy Pattern decouples the algorithm implementation from the 
client, allowing easy switching of algorithms without altering the client code



Strategy Pattern Structure
Context: The client class that uses a strategy to perform an operation.
Strategy Interface: Defines the operations that all concrete strategies must 
implement.
Concrete Strategy: Implements the actual algorithms, interchangeable based on the 
context.



When to Use the Strategy Pattern:
● When multiple algorithms need to be used interchangeably.
● To avoid conditional statements (if-else or switch-case) in the client 
code.
● When a class has multiple behaviors, which can vary independently.