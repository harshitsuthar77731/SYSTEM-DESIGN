

•	State Pattern:
	•	Allow an object to change its behavior when its internal state changes.
	•	Behavior appears to change at runtime.
•	Strategy Pattern:
	•	Define a family of interchangeable algorithms, encapsulate each one, and make them interchangeable by the client.



Strategy:
“Tell me how to go — I’ll follow that mode.”
	•	You switch between car, bus, cycle by your choice.
State:
“Let the system decide based on conditions.”
	•	Car runs out of fuel → system automatically switches to walking.



✅ When to Use
•	Use State Pattern when:
	•	You want an object to alter behavior when its internal state changes.
	•	You want state transitions to be handled internally (not by client).
•	Use Strategy Pattern when:
	•	You need to swap algorithms or logic dynamically.
	•	Client should have control over which strategy is used.