#include "Table.h"
#include "Structs.h"

#include "q.h"

void myTest1() {
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
        std::cout << row.id << "\t" << row.name << std::endl;
    }
    
}

//nationTable
void myTest2() {
    // 使用Nation作为模板参数来创建Table类的实例
    Table<Nation> nationTable;
    // 添加列名
    nationTable.setColumnNames({"N_NATIONKEY", "N_NAME", "N_REGIONKEY", "N_COMMENT"});
    // 导入数据
    nationTable.importData("nation.tbl");

    // 获取数据
    const auto& data = nationTable.getData();
    const auto& columnNames = nationTable.getColumnNames();
    // 输出列名
    for (const auto& columnName : columnNames) {
        std::cout << columnName << "\t";
    }
    std::cout << std::endl;

    std::cout << "data.size() = " << data.size() << std::endl;
    // 输出数据
    for (const auto& row : data) {
        std::cout << row.N_NATIONKEY << "\t" << row.N_NAME << "\t" << row.N_REGIONKEY << "\t" << row.N_COMMENT << std::endl;
    }
}

void myTest3() {
    std::string row = "20|alan|";
    MyStruct ms = convertToT<MyStruct>(row);
    std::cout << ms.id << "\t" << ms.name << std::endl;

    std::string row2 = "0|ALGERIA|0| haggle. carefully final deposits detect slyly agai|";
    Nation n = convertToT<Nation>(row2);
    std::cout << n.N_NATIONKEY << "\t" << n.N_NAME << "\t" << n.N_REGIONKEY << "\t" << n.N_COMMENT << std::endl;
}

//CustomerTable
void myTest4() {
    // 使用MyStruct作为模板参数来创建Table类的实例
    Table<Customer> CustomerTable;
    // 添加列名
    CustomerTable.setColumnNames({"C_CUSTKEY", "C_NAME", "C_ADDRESS", "C_NATIONKEY", "C_PHONE", "C_ACCTBAL", "C_MKTSEGMENT", "C_COMMENT"});
    // 导入数据
    CustomerTable.importData("customer.tbl");
    // 获取数据
    const auto& data = CustomerTable.getData();
    const auto& columnNames = CustomerTable.getColumnNames();
    // 输出列名
    for (const auto& columnName : columnNames) {
        std::cout << columnName << "\t";
    }
    std::cout << std::endl;
    // 输出数据
    for (const auto& row : data) {
        std::cout << row.C_CUSTKEY << "\t" << row.C_NAME << "\t" << row.C_ADDRESS << "\t" << row.C_NATIONKEY << "\t" << row.C_PHONE << "\t" << row.C_ACCTBAL << "\t" << row.C_MKTSEGMENT << "\t" << row.C_COMMENT << std::endl;
    }
}
// }

int main() {
    // myTest1();
    // std::cout << "----------------" << std::endl;
    // myTest2();
    // std::cout << "----------------" << std::endl;
    // myTest3();
    // std::cout << "----------------" << std::endl;
    // myTest4();
    // std::cout << "----------------" << std::endl;
    // myTest5();

    // q1();

    // q3();

    // q5();//待测试 bug

    // q7(); //待测试 答案

    // q9(); //待测试 答案

    // q11(); //待测试 答案 无内容，无满足条件

    // q13(); //待测试 答案

    // q15(); //待测试 bug  缺表revenus0.tbl

    // q17(); //待测试 答案

    // q19(); //待测试 答案

    // q21(); //待测试 答案

    return 0;
}
