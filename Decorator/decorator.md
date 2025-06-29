
| Concept                 | Implementation in Your Code                                                      |
|-------------------------|----------------------------------------------------------------------------------|
| Component Interface     | `BasePizza` is the abstract interface with `cost()`                             |
| Concrete Components     | `Margherita`, `VegDelight`, and `FarmHouse` implement `BasePizza`              |
| Decorator Abstract Class| `ToppingDecorator` inherits from `BasePizza` and stores a `BasePizza*`         |
| Concrete Decorators     | `ExtraCheese` and `ExtraOlive` inherit `ToppingDecorator` and override `cost()`|
| Dynamic Composition     | In `main()`, you wrap pizzas with decorators dynamically at runtime             |

This is exactly what the Decorator pattern is about:
	•	✅ Wrapping objects
	•	✅ Adding behavior without modifying the original class
	•	✅ Doing it dynamically at runtime