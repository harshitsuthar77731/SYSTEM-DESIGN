	
    
    •	The code correctly implements the Memento Design Pattern
	•	Purpose of the pattern is to capture and restore an object’s internal state without exposing its internal structure
	•	Useful for features like undo, rollback, versioning, or save points

Participants
	•	Originator: TextEditor is the object whose internal state (content) is being saved and restored
	•	Memento: Memento stores a snapshot of TextEditor’s content
	•	Caretaker: CareTaker manages the history of Memento snapshots and handles undo operations

TextEditor Responsibilities
	•	write(string): updates the internal content
	•	read(): returns current content
	•	makeSnapshot(): returns a Memento* holding the current content
	•	restoreCurrentState(string): resets content from a given string (used during undo)

Memento Responsibilities
	•	Constructor stores a snapshot of text passed from TextEditor
	•	readContent(): returns the saved text
	•	Does not allow modifying content once created (ensures immutability of snapshot)

CareTaker Responsibilities
	•	Uses stack<Memento*> to manage history of snapshots
	•	saveCurrentState(TextEditor&): pushes a new snapshot to history
	•	undo(TextEditor&): pops the last snapshot and restores the second last
	•	If stack becomes empty, it restores the editor to empty string

Design Details
	•	#pragma once used in headers to prevent multiple inclusion
	•	Proper separation of responsibilities across classes
	•	Forward declaration of Memento used in TextEditor.h
	•	Raw pointers used for Memento* (can be improved with smart pointers to avoid memory leaks)

Flow Summary
	•	User writes “Text1” → snapshot created and pushed
	•	User writes “Text2” → new snapshot created and pushed
	•	User triggers undo → latest snapshot popped, previous snapshot restored

Enhancement Suggestions
	•	Replace raw pointers with unique_ptr<Memento> or shared_ptr<Memento> for memory safety
	•	Add redo functionality by maintaining a second stack
	•	Implement snapshot cleanup (destructor) to delete unused Memento* if using raw pointers

Conclusion
	•	The implementation correctly demonstrates the Memento pattern
	•	State changes are captured via snapshots
	•	Undo functionality is enabled without exposing internal details of the TextEditor
	•	Design is modular and follows object-oriented principles