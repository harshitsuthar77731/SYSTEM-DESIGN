High-Level module should not depend on low level module; both should depend on abstraction.

For example, consider a NotificationService (a high-level module) that directly depends on concrete implementations like EmailService and MessageService (low-level modules). If we need to introduce a new service such as WhatsAppService, we are forced to modify the NotificationService code to integrate it.

This creates tight coupling between the high-level and low-level modules, making the NotificationService harder to test, maintain, and extend. Most importantly, it violates the Dependency Inversion Principle, which states that:

High-level modules should not depend on low-level modules. Both should depend on abstractions.

Instead, NotificationService should depend on an abstraction (e.g., INotificationChannel), and each low-level module should implement this interface. This way, we can add new channels like WhatsAppService without changing existing high-level logic — promoting flexibility, testability, and adherence to SOLID principles.