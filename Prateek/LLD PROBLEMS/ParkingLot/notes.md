entity floor  :- done
entity vehicle :- done
entity parking manager :- done
entity priceCalculator :- done
entity parkingLot :- done
entity ticket :- done
entity spot :- done
entity admin controller
entity reservation system
entity gate




🚗 Parking Lot System – Problem Statement

Requirements

You are asked to design and implement a Parking Lot Management System. The system should be able to:
	1.	Basic Features
	•	The parking lot has multiple floors, and each floor has a fixed number of parking spots.
	•	Spots can be of different types: Compact, Large, Handicapped, Motorcycle.
	•	Vehicles can be of different types: Car, Truck, Bike, etc. Each type can only fit in specific spot types.
	2.	Core Functionalities
	•	Park Vehicle: Assign a free spot to a vehicle and generate a ticket.
	•	Unpark Vehicle: When a vehicle leaves, mark the spot as free and calculate parking charges.
	•	Check Availability: Show available spots per floor and spot type.
	•	Support multiple entry/exit gates with cameras to record license plate and issue tickets.
	3.	Advanced Features (if time permits)
	•	Pricing Strategy: Parking fees based on vehicle type + time spent.
	•	Reservation System: Allow reserving a spot in advance.
	•	Admin Dashboard: See overall stats (free/occupied spots, revenue, etc).

⸻

Constraints & Expectations
	•	The system should be Object-Oriented and extensible.
	•	Use proper Design Patterns (e.g., Strategy for pricing, Factory for vehicle creation, Singleton for ParkingLot).
	•	Make sure the design is thread-safe (multiple gates could assign spots simultaneously).
	•	Write clean, modular C++ code (not full production, but interview-quality).

⸻

Example Flow
	1.	A car enters through Gate 1 → system finds nearest available Compact spot on Floor 1 → assigns spot → issues ticket.
	2.	Another truck enters → only fits in a Large spot → assigned on Floor 2.
	3.	Car leaves after 3 hours → system calculates charges (₹20/hr for Car → ₹60) → frees spot.
	4.	Admin checks available spots and revenue.
