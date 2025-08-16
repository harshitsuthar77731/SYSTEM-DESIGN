Adapter Pattern
The Adapter Pattern is a structural design pattern that 
allows objects with incompatible interfaces to work 
together.

Problem Statement
Imagine you are working on an e-commerce application that needs to send email 
notifications to customers. Currently, you are using your own in-house 
EmailNotificationService, but now you want to integrate a popular third-party email 
service like SendGrid. However, the interface for your in-house system and the SendGrid 
service are incompatible.
Let's see how the Adapter Pattern can solve this problem.



Adapter Pattern

● Problem: When two systems or components have incompatible interfaces, they 
cannot work together directly.
● Solution: The Adapter Pattern bridges the gap by converting the interface of 
one class into another that the client expects.
Real-world analogy:
● A power adapter that allows a device with a US power plug to fit and work with 
a European power socket


Adapter Pattern Examples

● Adapters in Software Frameworks: In GUI frameworks, adapters are used to 
convert legacy code into newer formats.
● Adapter in Java I/O: In Java, InputStreamReader works as an adapter to 
convert InputStream (byte-based) to Reader (character-based).
● Adapter in APIs: When integrating external libraries, you often need adapters 
to convert data formats or APIs to match your system's requirements.
The Adapter Pattern is a versatile solution to ensure incompatible interfaces work 
together seamlessly, making it invaluable in software integration and legacy system 
migration.


Adapter Pattern Benefits

● Reusability: You can reuse existing code even when its interface is not 
compatible with the current system.
● Flexibility: It helps integrate classes from different libraries or systems that 
were not designed to work together.
● Decoupling: The Adapter decouples the client from the specific implementation 
of the Adaptee.