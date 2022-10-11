#include <iostream>
#include <map>
#include <vector>

constexpr char kComma = ',';
constexpr int kRows = 0;

class Fisher {
public:
    void parseFile(std::string filename);
    double getQuantile(int row, int col);
private:
    std::map<int, std::vector<double>> fisherTable_;
};

// int main() {
//     Fisher f;
//     f.parseFile("table.csv");
//     std::cout << f.getQuantile(4, 160);
// }