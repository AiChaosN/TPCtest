#include <iostream>
#include <fstream>  // 包含以使用 std::ifstream
#include <sstream>  // 包含以使用 std::istringstream
#include <vector>
#include <string>

// 定义一个结构体  模仿数据库建表
struct MyStruct {
    int id;
    std::string name;
};

// 声明模板函数，将字符串转换为T类型
template<typename T>
T convertToT(const std::string& value);

// 特化模板函数为 MyStruct 类型
template<>
MyStruct convertToT<MyStruct>(const std::string& value) {
    std::istringstream iss(value);
    MyStruct ms;
    iss >> ms.id;
    if (iss.fail()) {
        iss.clear();
        iss >> ms.name;
    }
    return ms;
}

// 定义一个模板类Table，用于存储数据
template<typename T>
class Table {
private:
    std::vector<std::vector<T>> data; // 二维数组来存储数据
    std::vector<std::string> columnNames; // 存储列名

public:
    // 构造函数
    Table() {}

    // 通过地址导入数据
    void importData(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "无法打开文件：" << path << std::endl;
            return;
        }

        std::string line;
        // 读取并解析数据行
        while (getline(file, line)) {
            std::istringstream iss(line);
            std::string value;
            std::vector<T> row;
            
            // 打印
            // std::cout << "line: " << line << std::endl;
            // 读取每个值直到行尾
            int i = 0;
            while (getline(iss, value, '|')) {
                i++;
                // 打印value
                // std::cout << value << std::endl;

                T t;
                if (i == 1) {
                    t.id = stoi(value);
                } else {
                    t.name = value;
                    i = 0;
                    row.push_back(t);
                }
            }

            // 将这一行数据添加到data中
            data.push_back(row);
        }

        file.close();
    }

    

    void addRow(const std::vector<T>& row) {
        data.push_back(row);
    }

    void setColumnNames(const std::vector<std::string>& names) {
        columnNames = names;
    }

    //表信息
    const std::vector<std::vector<T>>& getData() const {
        return data;
    }

    const std::vector<std::string>& getColumnNames() const {
        return columnNames;
    }


};

int main() {
    // 使用MyStruct作为模板参数来创建Table类的实例
    Table<MyStruct> myTable;

    // 添加列名
    myTable.setColumnNames({"ID", "Name"});

    // 导入数据
    myTable.importData("demo.tbl");

    // 获取数据
    const auto& data = myTable.getData();
    const auto& columnNames = myTable.getColumnNames();

    // 输出列名
    for (const auto& columnName : columnNames) {
        std::cout << columnName << "\t";
    }
    std::cout << std::endl;

    // 输出数据
    for (const auto& row : data) {
        for (const auto& item : row) {
            std::cout << item.id << "\t" << item.name << std::endl;
        }
    }

    return 0;
}

