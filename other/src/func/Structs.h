#include <string>

// 这个头文件定义了LineItem结构体和其他可能的结构体或类

struct LineItem {
    std::string l_returnflag;
    std::string l_linestatus;
    double l_quantity;
    double l_extendedprice;
    double l_discount;
    double l_tax;
    std::string l_shipdate;
};
// 可以在这里定义更多的结构体或类