We want to build a chat system with multiple participants where each user can send messages to all other users. If users send messages to each other directly, the complexity increases as more users are added. Each user must know about every other user, creating a complex web of communication and dependencies.

Problems
● As more users are added, each user needs to manage direct communication 
with all others, leading to high coupling.
● If a new communication rule is introduced (e.g., message logging), it would 
need to be added to all users.

Mediator Pattern

Problem: Objects in a system need to communicate, but direct communication leads to tight 
coupling and complexity.
Solution: The Mediator Pattern introduces a mediator object that handles all 
communication between objects, reducing direct dependencies and coupling.
In our chat app, by introducing a Mediator object, we will decouple the users from knowing 
about each other directly. The Mediator handles all communication, and the users 
(colleagues) only interact with the Mediator. This simplifies the interaction and reduces 
dependencies.



1. ChatMediator Interface: Declares the sendMessage method, which all mediators must 
implement.
2. Concrete Mediator:
○ The ChatRoom class implements the ChatMediator interface. It holds a list of users and 
handles message broadcasting.
3. User Class:
○ Each User object represents a participant in the chat. When a user sends a message, the 
sendMessage method in the ChatRoom mediator is called, which distributes the message 
to all users except the sender.
4. Communication:
○ Users interact only with the ChatRoom (mediator), which facilitates communication between 
them, removing direct dependencies between individual users



Air Traffic Control:
Airplanes communicate through a central control tower (mediator) instead of coordinating directly 
with each other.
GUI Component Coordination:
In GUI applications, multiple UI components may need to interact. For example, when a dropdown 
changes, it may trigger updates to text fields, buttons, etc. A mediator can handle this interaction 
logic instead of having the components know about each other directly.
Workflow Systems:
In a business process management system, a mediator can coordinate various activities across 
multiple systems or departments.