In certain situations, such as managing a database connection, logging, or 
configuration settings, you want to ensure that only one instance of a class is created 
throughout the application’s lifecycle. If multiple instances were created, it could lead 
to issues like:
● Inconsistent state: If multiple instances represent the same concept, they may 
hold different data.
● Resource conflicts: If multiple instances of a resource-heavy class are 
created, it can lead to performance degradation.



Singleton Design Pattern
The Singleton pattern is used when exactly one instance of a class is required to 
coordinate actions across the system.
When to Use
● Global resource management (e.g., managing database connections, 
logging).
● Configuration settings in applications that need to be shared.


Singleton Design Code
● Private Constructor: The constructor is private so that no other class can 
instantiate AppSettings directly.
● Singleton Access: The getInstance() method is used to access the single 
instance of the settings.
● Global Access: Any part of the application can access the settings using 
AppSettings.getInstance().


Thread Safety in Singleton DP
Multi-threading issues: Without thread safety, multiple instances of the Singleton 
class could be created in a multi-threaded environment.
Solutions:
○ Lazy Initialization with Synchronization: Synchronize the method that 
creates the instance.
○ Double-Checked Locking: Optimize the performance by only locking 
when necessary.
○ Bill Pugh Singleton Design: Uses an inner static helper class to ensure 
thread safety and lazy loading.





*********
Quick Rule of Thumb
	•	Static → Belongs to the class, same for all objects, or can run without an object.
	•	Non-static → Belongs to each object, different for each object, depends on object’s state.
*********