Composite Pattern
Problem: When building systems like a file directory, which consist of both 
individual items (files) and groups of items (directories), managing these with 
standard object hierarchies can become complex.
Solution: The Composite Pattern allows you to treat individual objects and 
compositions of objects uniformly by representing part-whole hierarchies.


Composite Pattern
● In a file system, both File and Directory can be treated as components. A 
directory can contain both files and other directories, forming a recursive tree 
structure.