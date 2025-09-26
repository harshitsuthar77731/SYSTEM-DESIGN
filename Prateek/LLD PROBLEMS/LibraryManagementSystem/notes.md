core entity
user _/
book _/
bookInventory _/
reservationSystem _/
libraryManager 
paymentService_/
notificationService _/
SearchService _/
MembershipPlan _/
LoanService _/





Problem Statement: Library Management System

Design a Library Management System that helps manage the day-to-day operations of a library, including book cataloging, user membership, and borrowing/returning books. The system should efficiently track available copies, issued books, reservations, and fines for late returns.

Core Requirements
	1.	Users & Roles
	•	Members can search books, borrow books, return books, reserve books, and view their borrowing history.
	•	Librarians/Admins can add/remove/update books, manage user memberships, and track overdue books.
	2.	Book Catalog & Inventory
	•	Store information about books (title, author, subject, ISBN, publication date, etc.).
	•	Each book can have multiple copies, each with a unique identifier (barcode or ID).
	•	Support searching books by title, author, subject, and publication date.
	3.	Book Borrowing & Returning
	•	A member can borrow multiple books (within a max limit, e.g., 5).
	•	A borrowed book must have a due date.
	•	On return, check for late submission and calculate fines if applicable.
	4.	Reservations
	•	If all copies of a book are issued, a member can place a reservation.
	•	When a reserved book becomes available, notify the member.
	5.	Fines & Payments
	•	Fine is charged for each day a book is returned late.
	•	System should track pending fines per member.
	6.	System Constraints
	•	Large catalog (millions of books).
	•	Support concurrent access by multiple members and librarians.
	•	Ensure consistency in book availability and reservations.