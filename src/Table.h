#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Structs.h"
#include <unordered_map>
/*
 * Table.h
 * define template Table
    * this class is used to store data
    * @setColumnNames : set column names
    * @importData: import data
    * @addRow: add a row
    * @getData: get data
    * @getColumnNames: get column names
*/

// define template Table
template<typename T>
class Table {
private:
    std::vector<T> data;
    std::vector<std::string> columnNames;

    // hash map
    std::unordered_map<int, T> dataMap;
public:
    Table() {}

    // import data
    void importData(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "无法打开文件：" << path << std::endl;
            return;
        }

        std::string line;
        while (getline(file, line)) {
            T t = convertToT<T>(line);
            data.push_back(t);
        }
        file.close();
    }

    // add column names
    void setColumnNames(const std::vector<std::string>& names) {
        columnNames = names;
    }

    // get data
    const std::vector<T>& getData() const {
        return data;
    }

    // get column names
    const std::vector<std::string>& getColumnNames() const {
        return columnNames;
    }

    // key index
    const std::unordered_map<int, T> buildIndex() {
        for (int i = 0; i < data.size(); i++) {
            dataMap[i] = data[i];
        }
        return dataMap;
    }

    // build other index
    std::unordered_map<int, int> buildIndex(const std::string& columnName) {
        std::unordered_map<int, int> indexMap;
        for (int i = 0; i < data.size(); i++) {
            // 假设getFieldValue能够根据columnName从data[i]中获取对应的字段值
            int fieldValue = data[i].columnName;
            indexMap[fieldValue] = i;
        }
        return indexMap;
    }
};
