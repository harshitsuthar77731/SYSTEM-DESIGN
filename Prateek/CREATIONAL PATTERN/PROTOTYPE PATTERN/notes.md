Problem
Consider a board game where you need to save the current state of the game at 
various checkpoints. Instead of manually creating new board objects and copying all 
the pieces or their states (which could be costly if the board is large and has many 
game pieces), we can use the Prototype Pattern to clone the board.
We will use the prototype pattern allows us to make a copy of the current board, 
including all its pieces and their states, without the need for deeply recreating each 
part of the board.

Solution
The Prototype Pattern can be extremely useful in a board game when you 
want to save the current state of the game (including the board layout and the 
position of pieces) for undo/redo functionality, checkpoints, or simply making a 
copy of the board for a new player.
● Each piece or game element can provide its own clone method, allowing the 
entire board to be easily cloned with all its current state.
By using the Prototype pattern, we decouple the complexity of cloning the board from 
the client, ensuring that each object knows how to clone itself, making the system 
flexible and easier to maintain.


Shallow vs Deep Copy
Shallow Copy: Creates a new object but does not clone the objects that the original object refers 
to.
Deep Copy: Clones the original object and all the objects it refers to (nested objects)
Example:
● Shallow Copy: Cloning an object with references to other objects (only the outer object is copied).
● Deep Copy: Cloning the entire object graph, including any objects the original refers to.


Benefits
Simplifies Object Creation: Instead of manually copying each object, the clone method 
in each object simplifies the creation of copies.
● Avoids Subclassing: The pattern relies on delegation to the clone method, allowing the 
class itself to handle object creation, avoiding the need for subclassing.
● Shallow or Deep Copy: Depending on the use case, you can either implement a shallow 
copy (copying references) or a deep copy (cloning objects) based on the specific 
requirements.
● Efficient Creation: When creating objects with a complex structure or when performance 
is a concern, the Prototype pattern allows you to efficiently replicate objects.
● Consistency: Ensures that all properties of the object are consistently copied, avoiding 
errors associated with manual copying.


Use Cases
● Use Cases:
○ Cloning large objects where construction is costly (e.g., deep configuration settings).
○ When system resources (time, memory) are limited and re-creating objects is expensive.