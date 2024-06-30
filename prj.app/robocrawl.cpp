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
  Coord(const double& r1) : x(r1), y(0) {};
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
  Coord GO(Coord& a) final {
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
  std::string command;
  while (std::cin >> command) {
    if (command == "GO") {
      double co_x(0);
      std::cin >> co_x;
      Coord n(co_x);
      for (int i = 0; i < vec.size(); i++) {
        n = vec[i]->GO(n);
      }
      n.WriteTo();
    }
    if (command == "GW") {
      double oper(0);
      std::cin >> oper;
      vec.emplace_back(new GW(oper));
    }
    if (command == "GN") {
      double oper(0);
      std::cin >> oper;
      vec.emplace_back(new GN(oper));
    }
    if (command == "GS") {
      double oper(0);
      std::cin >> oper;
      vec.emplace_back(new GS(oper));
    }
    if (command == "GE") {
      double oper(0);
      std::cin >> oper;
      vec.emplace_back(new GE(oper));
    }
    if (command == "RE") {
      int oper(0);
      std::cin >> oper;
      if (oper > vec.size()) {
        std::cout << "ERROR" << std::endl;
      }
      else {
        vec.resize(vec.size() - oper);
      }
    }
  }
}