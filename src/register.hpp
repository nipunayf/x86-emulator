#include <fstream>
#include <string>

class Register {
  private:
    std::string name;

  public:
    uint32_t value;
    Register(const std::string &name, uint32_t value);
    Register() = default;
};
