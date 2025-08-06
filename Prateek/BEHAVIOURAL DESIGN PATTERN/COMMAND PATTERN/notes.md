Problem statement
Imagine you're developing a basic text editor with buttons for bold, italic, and 
underline text formatting. 
Without the Command Pattern, the buttons directly interact with the TextEditor
class, and you’d end up hardcoding behavior into the UI classes, making them tightly 
coupled.

Requirement
In a text editor, instead of hardcoding what each button (like Bold, Italic, Underline, etc.) does, we use the Command Pattern to encapsulate each action as a separate command object. This way, buttons are just invokers that trigger commands, without knowing how they’re executed.



Problem Without Command Pattern (code)
● Each button class is tightly coupled with the TextEditor. If the action 
changes, all button classes need to be modified.
● It's harder to extend with new commands or add functionality such as 
undo/redo or logging.

By introducing the Command Pattern, we can decouple the actions (bold, italic, 
underline) from the UI components (buttons), making the design more flexible and 
maintainable. The buttons no longer need to know about the editor directly but 
instead work with generic Command objects.


Structure:
● Command: Interface for executing operations.
● Invoker: Sends the command.
● Receiver: Performs the operation.



● Decoupling of Invoker and Receiver: The button (invoker) doesn't know the 
details of the TextEditor (receiver), making the system more flexible and 
reusable.
● Command History and Undo: Commands can be logged for undo/redo 
functionality.
● Task Queuing: Commands can be stored in a queue and executed later, 
making it useful for task scheduling.
● Extensibility: New commands can be added easily without modifying existing 
code. For example, adding a ChangeColorCommand only requires creating a 
new command class.



GUI Applications:
● Commands can be associated with buttons, menus, and keyboard shortcuts in 
applications like text editors, spreadsheets, or drawing software.
Task Scheduling:
● Commands can be placed in a queue and executed later, useful in batch 
processing or deferred task execution.
Undo/Redo Functionality:
● Commands can be stored and rolled back to provide undo and redo 
capabilities, especially in applications like IDEs, word processors, or graphics 
software.
Macro Recording:
● Actions performed by the user can be recorded as a series of commands, 
which can then be played back as macros.



Leyman :-

•	Earlier Approach:
I was tightly coupling the Button class with a specific action (e.g., BoldButton, ItalicButton, etc.).
This meant adding a new button class every time a new action or formatting type was introduced — violating the Open/Closed Principle.
	•	Now with Command Pattern:
	•	I’ve created a common interface (Command) with an execute() method.
	•	Each formatting action (Bold, Italic, Underline) is encapsulated in a separate Command class (e.g., BoldCommand, ItalicCommand).
	•	The Button class is generic — it takes any Command object and calls execute() when clicked.
	•	This way, I can assign different commands to the same Button class, achieving full decoupling between the button and the action.
	•	Benefits I Now Understand:
	•	Follows Open/Closed Principle — new commands can be added without changing existing code.
	•	Encourages loose coupling — Button doesn’t care what action it triggers.
	•	Enables advanced features like Undo/Redo, macro commands, and dynamic command assignment.
	•	Real-World Analogy:
Just like a remote control button can be programmed to control any device,
my Button can now trigger any formatting logic through a pluggable Command.