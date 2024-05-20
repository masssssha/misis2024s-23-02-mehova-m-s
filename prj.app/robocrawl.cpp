#include <iostream>
#include <vector>
#include <string>

class Coord {
public:
  Coord() = default;
  void WriteTo() {
    std::cout << x << " " << y << std::endl;
  }
  Coord(const double& r1, const double& r2) : x(r1), y(r2) {};
  double x{ 0 };
  double y{ 0 };
};

class Command {
public:
  Command() = default;
  Command(const double& a, const double& b) {
    n.x = a;
    n.y = b;
  };
  virtual ~Command() = default;
  virtual Coord GO(Coord& a) = 0;
protected:
  Coord n{ 0, 0 };
};

class GW : public Command {
public: 
  GW() = default;
  GW(const double& a) : Command(a, 0) {};
  Coord GO(Coord& a) override {
    a.x -= n.x;
    return a;
  }
};

class GE : public Command {
public:
  GE() = default;
  GE(const double& a) : Command(a, 0) {};
  Coord GO(Coord& a) override {
    a.x += n.x;
    return a;
  }
};

class GN : public Command {
public:
  GN() = default;
  GN(const double& b) : Command(0, b) {};
  Coord GO(Coord& a) override {
    a.y += n.y;
    return a;
  }
};

class GS : public Command {
public:
  GS() = default;
  GS(const double& b) : Command(0, b) {};
  Coord GO(Coord& a) override {
    a.y -= n.y;
    return a;
  }
};


int main() {
  std::vector<std::unique_ptr<Command>> vec;
  Coord n(10, 10);
  double a(1), b(2), c(10), d(12);
  vec.emplace_back(new GW(a));
  GS* ptr2 = new GS(c);
  vec.emplace_back(ptr2);
  GN* ptr3 = new GN(b);
  vec.emplace_back(ptr3);
  GE* ptr4 = new GE((a + b));
  vec.emplace_back(ptr4);
  GW* ptr5 = new GW((c + a + b));
  vec.emplace_back(ptr5);
  for (int i = 0; i < vec.size(); i++) {
    n = vec[i]->GO(n);
    n.WriteTo();
  }
}