#include <iostream>
#include <vector>
#include <string>

class Command {
public:
  Command() = default;
  Command(double& r) {
    com.push_back(*this);
  }
  ~Command() = default;
private:
  double x{ 0.0 };
  double y{ 0.0 };
  std::vector<Command> com;
};

int main() {
  Command GW;
}