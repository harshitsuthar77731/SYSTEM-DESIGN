Your code builds different versions of shapes (circle, rectangle) depending on the theme chosen (modern/classic). This lets you easily extend the design without modifying existing logic — which is the whole point of the Abstract Factory Pattern.




For smart Pointer

Swap Variable* :-  unique_ptr<Variable>
Swap new Variable() :- make_unique<Variable>()

benefit:- 
 
| **Feature**              | **Raw Pointer (`*`)**         | **Smart Pointer (`unique_ptr`, `shared_ptr`)**         |
|--------------------------|-------------------------------|--------------------------------------------------------|
| Manual memory management | ✅ Required (`delete`)         | ❌ Not needed — managed automatically                   |
| Risk of memory leaks     | ❗️ High                        | ✅ Low                                                  |
| Ownership tracking       | ❌ No                          | ✅ Yes (especially with `shared_ptr`)                  |
| Copyable                 | ✅ Yes                         | ❌ `unique_ptr` can’t be copied                        |