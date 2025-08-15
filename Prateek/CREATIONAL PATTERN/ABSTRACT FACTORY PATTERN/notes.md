Motivation

Consider an application that needs to support multiple UI themes (e.g., Windows, 
macOS). Each theme has its own set of UI components such as buttons, scrollbars, 
and windows. The challenge is to create an architecture that allows switching 
between these themes without changing the client code that uses the UI 
components.
Without the Abstract Factory Pattern, the client code would be tightly coupled with 
the concrete implementations of buttons, scrollbars, etc., and switching between 
themes would require modifying the client code.

Problems in Code

1. Tight coupling: The client code is tightly coupled to specific implementations of UI 
components (WindowsButton, WindowsScrollBar).
2. Hard to extend: If we want to add support for macOS UI components, we would 
need to modify the client code to create instances of MacOSButton and 
MacOSScrollBar


Abstract Factory Pattern

Problem It Solves: Provides an interface for creating families of related objects without specifying their 
concrete classes.
Structure:
● Abstract Factory: Interface for creating abstract products.
● Concrete Factory: Implements the abstract factory and creates concrete products.
Using the Abstract Factory Pattern, you create interfaces for each product (e.g., Button, ScrollBar, Window) 
and provide a family of concrete implementations for each theme (e.g., WindowsButton, MacOSButton, etc.). 
The Abstract Factory provides a way to create a suite of related objects without knowing the exact type of 
objects that will be created.



Factory vs Abstract Factory

Factory Method: Defines a method in the base class but lets subclasses override it 
to specify the type of objects that will be created.
○ Example: A DocumentFactory subclass that creates either PDF or 
Word documents.
Abstract Factory: Provides an interface for creating families of related or dependent 
objects without specifying their concrete classes.
○ Example: A GUIFactory that creates related objects like buttons, 
checkboxes, and text fields depending on the operating system (Windows 
or Mac).