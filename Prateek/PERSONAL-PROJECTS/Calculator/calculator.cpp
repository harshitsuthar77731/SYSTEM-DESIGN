#include <iostream>
#include <map>
#include <string>
using namespace std;

class Operation {
public:
  virtual ~Operation() = default;
  virtual int compute(const vector<double> &operands) = 0;
};

class AddOperation : public Operation {
public:
  int compute(const vector<double> &operands) override {
    double sum = 0;
    for (auto elem : operands) {
      sum += elem;
    }
    return sum;
  }
};

class MultiplyOperation : public Operation {
public:
  int compute(const vector<double> &operands) override {
    double mul = 1;
    for (auto elem : operands) {
      mul *= elem;
    }
    return mul;
  }
};
class SubtractOperation : public Operation {
public:
  int compute(const vector<double> &operands) override {
    if (operands.size() != 2)
      throw invalid_argument("Input element should be equal to 2");
    return operands[0] - operands[1];
  }
};
class DivideOperation : public Operation {
public:
  int compute(const vector<double> &operands) override {
    if (operands.size() != 2)
      throw invalid_argument("Input element should be equal to 2");
    return operands[0] / operands[1];
  }
};

class Calculator {
private:
  unordered_map<string, unique_ptr<Operation>> operationMap;

public:
  void addOperation(string OperationName, unique_ptr<Operation> op) {
    operationMap[OperationName] = std::move(op);
  }
  int compute(string OperationName, const vector<double> &operands) {
    if (operationMap.find(OperationName) != operationMap.end())
      return operationMap[OperationName]->compute(operands);
    else {
      throw invalid_argument("Operation you mentioned doesn't exist");
    }
  }
};

int main() {
  // making unique pointer to avoid memory leak
  try {
    Calculator calc;
    calc.addOperation("add", make_unique<AddOperation>());
    calc.addOperation("multiply", make_unique<MultiplyOperation>());
    calc.addOperation("divide", make_unique<DivideOperation>());

    vector<double> arg1 = {1, 2};
    vector<double> arg2 = {1, 2, 3, 4};

    cout << calc.compute("add", arg1) << endl;
    cout << calc.compute("multiply", arg2) << endl;
    cout << calc.compute("divide", arg1) << endl;

    cout << calc.compute("divide", arg2) << endl;
  } catch (const std::exception &e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}
