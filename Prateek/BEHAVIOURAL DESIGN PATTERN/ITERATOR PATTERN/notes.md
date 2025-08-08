Suppose you have a collection, such as an array or list, and you need to provide a mechanism for accessing its elements. Without the iterator pattern, the client code needs to understand how the collection is structured, and different collections would require different methods to traverse them.


PROBLEM  :- 
Problem: How to access elements in a collection without exposing its internal representation.
Solution: The Iterator Pattern provides a way to traverse a collection without revealing its underlying structure, offering a uniform interface for traversal.
Structure:
● Iterator: Interface for traversing a collection.
● Collection: Holds the elements and provides an iterator.

Iterator Pattern Benefits
1. Separation of Concerns: The traversal logic is separated from the collection itself, allowing you to change one without affecting the other.
2. Uniform Interface: The same interface (Iterator) is used to traverse different types of collections, making the code more flexible.
3. Simplified Client Code: The client doesn’t need to know the underlying data structure, reducing coupling and making the code easier to maintain.
4. Multiple Traversal Strategies: You can implement multiple types of iterators (e.g., forward, backward, filtered) without changing the collection.


USE CASE :- 

1. Java Collections Framework:
○ The Java Collections Framework (e.g., ArrayList, HashSet) uses the iterator pattern to provide a common interface (Iterator) for traversing different types of collections.
2. Database Cursors:
○ In database programming, cursors are used to iterate over result sets. The iterator pattern can abstract this traversal, making it easier to work with data from a database without exposing the underlying query mechanism.
3. Tree Traversals:
○ In tree data structures, the iterator pattern can be used to traverse nodes using different strategies like depth-first or breadth-first, without exposing the tree's internal structure.
4. File Systems:
○ File systems can use the iterator pattern to traverse directories and files without exposing the internal details of how files and folders are stored.


DrawBack :-
1. Additional Complexity: Implementing the iterator pattern can add extra layers of abstraction, 
especially for small or simple collections where direct traversal is sufficient.
2. Increased Overhead: For small collections or when the structure is unlikely to change, the 
overhead of creating iterators may not be justified.