Suppose we have a weather station that records temperature and multiple devices 
(e.g., display units) want to show the latest temperature. Without using the observer 
pattern, the weather station would have to explicitly inform each device about the 
temperature change, which results in tight coupling between the station and devices.


Problems with current implementation(Bad Code) :-
The WeatherStation class is tightly coupled to the DisplayDevice class.
If we need multiple devices (e.g., mobile, tablet) to display the temperature, we need 
to modify the WeatherStation class, leading to poor scalability and flexibility.


Problem: There is a need to notify multiple objects about a change in state without 
tightly coupling them.
Solution: The Observer Pattern defines a one-to-many dependency. When one 
object (the Subject) changes its state, all its dependents (the Observers) are notified 
and updated automatically. This pattern is widely used for implementing distributed 
event-handling systems, also known as the publish-subscribe pattern.


Observer Pattern Benefits

● Loose Coupling: The subject (e.g., WeatherStation) doesn’t need to know 
about the specific observers. It just notifies them.
● Scalability: New observers (e.g., new display devices) can easily be added 
without changing the subject.
● Flexibility: Observers can be dynamically added or removed at runtime.


Use Case

● Event Listeners: GUI frameworks often use the Observer Pattern to 
implement event listeners for handling button clicks, input changes, etc.
● Stock Price Monitoring: When a stock price changes, multiple subscribers 
(like investors or systems) can be notified of the change.
● News Publishing Systems: News articles are published (subject), and 
subscribers (users) are notified whenever a new article is available.
● Social Media Notifications: Users can subscribe to updates from specific 
accounts, and when an account posts (subject), all followers (observers) are 
notified.
● Logging Systems: Different logging handlers can observe events and log 
them as needed, such as to the console, file, or remote server.