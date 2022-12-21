#include <string>
#include <fstream>

class Scanner {
private:
    std::ifstream file;

public:
    Scanner(const std::string &file_path);

    ~Scanner();

    uint16_t next();
};
