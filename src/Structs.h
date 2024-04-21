// Structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

/*
    * Structs.h
    * 定义一些结构体，用于模仿数据库建表
    * 该文件还需要定义模板函数，用于将字符串转换为特定类型
*/


// 定义一个结构体模仿数据库建表
struct MyStruct {
    int id;
    std::string name;
};

struct Customer {
    int C_CUSTKEY;
    std::string C_NAME;
    std::string C_ADDRESS;
    int C_NATIONKEY;
    std::string C_PHONE;
    float C_ACCTBAL;
    std::string C_MKTSEGMENT;
    std::string C_COMMENT;
};

struct LineItem {
    int L_ORDERKEY;
    int L_PARTKEY;
    int L_SUPPKEY;
    int L_LINENUMBER;
    float L_QUANTITY;
    float L_EXTENDEDPRICE;
    float L_DISCOUNT;
    float L_TAX;
    char L_RETURNFLAG;
    char L_LINESTATUS;
    std::string L_SHIPDATE;  // DATE
    std::string L_COMMITDATE; // DATE
    std::string L_RECEIPTDATE; // DATE
    std::string L_SHIPINSTRUCT;
    std::string L_SHIPMODE;
    std::string L_COMMENT;
};

struct Nation {
    int N_NATIONKEY;
    std::string N_NAME;
    int N_REGIONKEY;
    std::string N_COMMENT;
};

struct Orders {
    int O_ORDERKEY;
    int O_CUSTKEY;
    char O_ORDERSTATUS;
    float O_TOTALPRICE;
    std::string O_ORDERDATE;  // DARE
    std::string O_ORDERPRIORITY;
    std::string O_CLERK;
    int O_SHIPPRIORITY;
    std::string O_COMMENT;
};

struct Part {
    int P_PARTKEY;
    std::string P_NAME;
    std::string P_MFGR;
    std::string P_BRAND;
    std::string P_TYPE;
    int P_SIZE;
    std::string P_CONTAINER;
    float P_RETAILPRICE;
    std::string P_COMMENT;
};

struct PartSupp {
    int PS_PARTKEY;
    int PS_SUPPKEY;
    int PS_AVAILQTY;
    float PS_SUPPLYCOST;
    std::string PS_COMMENT;
};

struct Region {
    int R_REGIONKEY;
    std::string R_NAME;
    std::string R_COMMENT;
};

struct Supplier {
    int S_SUPPKEY;
    std::string S_NAME;
    std::string S_ADDRESS;
    int S_NATIONKEY;
    std::string S_PHONE;
    float S_ACCTBAL;
    std::string S_COMMENT;
};

// 定义一个模板函数，用于将特定类型转换为字符串 -----------------------------------------------------------

// 定义一个模板函数，用于将字符串转换为特定类型
template<typename T>
T convertToT(const std::string& value);

// // 特化模板函数为 MyStruct 类型的实现
template<>
MyStruct convertToT<MyStruct>(const std::string& value);

// // 特化模板函数为 Nation 类型的实现
template<>
Nation convertToT<Nation>(const std::string& value);

// // 特化模板函数为 Customer 类型的实现
template<>
Customer convertToT<Customer>(const std::string& value);

// // 特化模板函数为 LineItem 类型的实现
template<>
LineItem convertToT<LineItem>(const std::string& value);

// // 特化模板函数为 Orders 类型的实现
template<>
Orders convertToT<Orders>(const std::string& value);

// // 特化模板函数为 Part 类型的实现
template<>
Part convertToT<Part>(const std::string& value);

// // 特化模板函数为 PartSupp 类型的实现
template<>
PartSupp convertToT<PartSupp>(const std::string& value);

// // 特化模板函数为 Region 类型的实现
template<>
Region convertToT<Region>(const std::string& value);

// // 特化模板函数为 Supplier 类型的实现
template<>
Supplier convertToT<Supplier>(const std::string& value);

// 定义一个模板函数，用于将特定类型转换为字符串 -----------------------------------------------------------
#endif // STRUCTS_H
