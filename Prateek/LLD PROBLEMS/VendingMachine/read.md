Requirements

entity
	Product
	ProductInventory
	PaymentMethod (Strategy)
	MoneyService 
	VendingService (State)
	DisplayService







Core Functionalities
	1.	The vending machine should:
	•	Display available products with prices.
	•	Accept money in valid denominations (coins/notes).
	•	Allow the user to select a product.
	•	Dispense the product if sufficient balance is provided.
	•	Return balance if the inserted amount > product price.
	•	Cancel transaction and refund money.

Constraints
	•	The machine has limited inventory for each product.
	•	Only specific denominations are accepted (e.g., 1, 5, 10, 20, 50, 100).
	•	Machine should not dispense if:
	•	Product is out of stock.
	•	Inserted money < product price.
	•	Machine cannot return change.

Extended Features (Optional if time permits)
	•	Support multiple payment methods (cash, card, UPI).
	•	Refill/maintain stock and cash by an admin.
	•	Display running status (e.g., “Out of Service”, “Refilling”).
	•	Handle concurrency (multiple users trying to buy).

⸻

Object-Oriented Expectations
	•	Use State Design Pattern (Idle, HasMoney, Dispense, ReturnChange, etc.).
	•	Use classes for Product, Inventory, Payment, VendingMachine.
	•	Ensure encapsulation of machine states and operations.
	•	Keep it extensible for future features (like adding new payment methods).