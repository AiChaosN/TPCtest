#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Table {
private:
    std::ifstream file;
    std::vector<std::string> currentRecord;

    std::vector<std::string> splitLine(const std::string& line, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(line);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    Table(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    ~Table() {
        if (file.is_open()) {
            file.close();
        }
    }

    bool next() {
        std::string line;
        if (getline(file, line)) {
            currentRecord = splitLine(line, '|');
            return true;
        }
        return false;
    }

    const std::vector<std::string>& getCurrentRecord() const {
        return currentRecord;
    }
};

int main() {
    Table table("supplier.tbl");

    while (table.next()) {
        const auto& record = table.getCurrentRecord();
        for (const auto& field : record) {
            std::cout << field << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << "End of file" << std::endl;

    return 0;
}
