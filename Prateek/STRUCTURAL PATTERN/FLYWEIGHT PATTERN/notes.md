Flyweight Pattern Motivation
In game development, especially in scenarios like shooting games where numerous 
identical bullets are fired, memory and performance can quickly become an issue if 
each bullet object stores redundant data. Using the Flyweight Pattern, we can 
reduce memory overhead by sharing intrinsic properties of bullets (like appearance) 
while maintaining unique extrinsic properties (like position and velocity).

![alt text](<Screenshot 2025-08-17 at 9.24.38 PM.png>)
if there are 10000 bullet fired and one object of bullet equal to 4kb so it will take around 500MB of memory only for bullet and so we have to do something about intrinsic(common for all) data like image or color
if we use extrinsic data it is around 8*10000 bytes which is around 80 kb and image data as common so net is less than 1 MB means from 500 mb to less than 1 mb of memory



Flyweight Pattern Solution
In this refactor, the Bullet class contains only extrinsic data(which are not common) like position and velocity. The 
intrinsic data like color is stored in a BulletType class, which is shared across all Bullet
objects. This allows us to manage a large number of bullets efficiently


Flyweight Pattern

Problem: Creating many identical or similar objects in memory-heavy applications 
can lead to excessive memory consumption.
Solution: By sharing the common state among multiple objects (the flyweights), the 
pattern reduces the memory footprint.
Example Problem:
● Consider a graphics system rendering a large number of trees in a forest, 
where each tree shares the same image but may vary by position or size.
The Flyweight Pattern is a structural pattern used to minimize memory usage by sharing as 
much data as possible with similar objects. It separates the intrinsic state (shared) from the 
extrinsic state (non-shared).
Purpose: To optimize resource usage in applications that need to handle a large number of 
similar objects by reusing common parts of their data.
When to Use:
● When you need to create a large number of objects, and they share a lot of common 
data.
● Ideal for memory-constrained applications where the object creation cost is high


Flyweight Pattern Structure

● Flyweight: The shared object that stores intrinsic state (common data).
● Concrete Flyweight: Implements the flyweight interface and shares the intrinsic state.
● Flyweight Factory: Manages and creates flyweight objects, ensuring that objects with 
the same intrinsic state are reused.
● Client: Holds and manages the extrinsic state (unique information) and delegates 
behavior to the flyweight.


Flyweight Pattern Structure

● Flyweight: The shared object that stores intrinsic state (common data).
● Concrete Flyweight: Implements the flyweight interface and shares the intrinsic state.
● Flyweight Factory: Manages and creates flyweight objects, ensuring that objects with 
the same intrinsic state are reused.
● Client: Holds and manages the extrinsic state (unique information) and delegates 
behavior to the flyweight.



Flyweight Pattern Example
Scenario: A program that needs to render a large number of trees in a forest.
○ Intrinsic State: Tree type, shape, texture, and color (shared across trees).
○ Extrinsic State: Tree position and size (unique per tree).
Without Flyweight: Each tree object would store all properties, leading to high memory 
usage. 
With Flyweight: The tree objects share common properties, and only the unique properties 
(position and size) are stored separately.