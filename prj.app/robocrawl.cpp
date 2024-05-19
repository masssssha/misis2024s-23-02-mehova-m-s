#include <iostream>
#include <vector>
#include <string>

class Command {
public:
  Command() = default;
  Command(const double& r1, const double& r2) : x(r1), y(r2) {};
  virtual ~Command() = default;
  virtual void Set(const double& a) = 0;
  void WriteTo() {
    std::cout << x << " " << y << std::endl;
  }
  double GetX() {
    return x;
  }
  double GetY() {
    return y;
  }
protected:
  double x{ 0.0 };
  double y{ 0.0 };
};

class GW : public Command {
public: 
  GW() = default;
  GW(const double& r1, const double& r2) : Command(r1, r2) {};
  void Set(const double& a) override {
    x -= a;
  }
};

class GE : public Command {
public:
  GE() = default;
  GE(const double& r1, const double& r2) : Command(r1, r2) {};
  void Set(const double& a) override {
    x += a;
  }
};

class GN : public Command {
public:
  GN() = default;
  GN(const double& r1, const double& r2) : Command(r1, r2) {};
  void Set(const double& a) override {
    y += a;
  }
};

class GS : public Command {
public:
  GS() = default;
  GS(const double& r1, const double& r2) : Command(r1, r2) {};
  void Set(const double& a) override {
    y -= a;
  }
};


int main() {
  double x(0), y(0);
  GW a(x, y);
  GS b(x, y);
  GN c(x, y);
  GE d(x, y);
  std::vector<Command*> vec;
  Command* p = &a;
  p->Set(1);
  p->Set(3);
  p->WriteTo();
  p = &b;
  p->Set(11);
  p->Set(2);
  p = &d;
  p->Set(3);
  p->WriteTo();
}