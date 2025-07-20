#include <iostream>
using namespace std;

class Printer {
  public:
  virtual ~Printer() = default;
  virtual void print() = 0;
};

class Scanner {
  public:

  virtual ~Scanner() = default;
  virtual void scan() = 0;
};
class Copier {
  public:

  virtual ~Copier() = default;
  virtual void copy() = 0;
};

class SimplePrinter : public Printer {
public:
  void print() { cout << "printing data"; }
};

class MultiPurposePrinter : public Scanner, public Printer, public Copier {
public:
  void scan() { cout << "Scanning document"; }
  void print() { cout << "Printing document"; }
  void copy() { cout << "Copy document"; }
};

int main () {
    SimplePrinter *sp =new SimplePrinter();
    MultiPurposePrinter *mp =new MultiPurposePrinter();
    sp->print();
    mp->copy();
    mp->print();
    mp->scan();



}