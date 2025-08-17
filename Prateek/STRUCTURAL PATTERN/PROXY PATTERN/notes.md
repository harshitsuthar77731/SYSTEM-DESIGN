Proxy Pattern
● Problem: Sometimes, direct access to an object might not be desirable due to 
reasons such as security, resource optimization, or controlled access.
● Solution: The Proxy Pattern provides a surrogate or placeholder for another 
object to control access to it


Proxy Pattern Motivation
Imagine a system where we want to load a heavy object like a large image from 
disk. It might take time to load the image, and we don’t want to load it until it’s 
necessary. Without using a proxy, the application would load the image every 
time it's needed, even if not displayed, wasting resources.


Proxy Design Pattern
● Virtual Proxy: Delays the creation of expensive objects until they are needed 
(lazy initialization).
● Protection Proxy: Controls access based on permissions.
Example
A large image loading in an application is expensive, so a virtual proxy is used to 
load the image only when it’s actually needed (on-demand).


Proxy Pattern Benefits
1. Lazy Initialization: Objects are loaded only when necessary, saving memory 
and CPU cycles.
2. Access Control: You can control access to the real object (e.g., based on user 
permissions).
3. Additional Behavior: Proxies can add additional functionalities like logging, 
access control, or caching without modifying the real object.
4. Separation of Concerns: The real object only deals with its core 
responsibilities, while the proxy handles ancillary operations like initialization or 
security