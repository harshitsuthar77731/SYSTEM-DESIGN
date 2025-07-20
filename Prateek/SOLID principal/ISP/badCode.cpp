#include <iostream>
using namespace std;

class Machine {
public:
  virtual ~Machine() = default;
  virtual void scan() = 0;
  virtual void print() = 0;
  virtual void copy() = 0;
};

class SimplePrinter : public Machine {
public:
  void scan() { cout << "Scanning document"; }
  void print() { throw invalid_argument("Printing not supported"); }
  void copy() { throw invalid_argument("Copy not supported"); }
};

class MultiPurposeMachine : public Machine {
public:
  void scan() { cout << "Scanning document"; }
  void print() { cout << "Printing document"; }
  void copy() { cout << "Copy document"; }
};

