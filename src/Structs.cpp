#include "Structs.h"
#include <sstream>

// 特化模板函数为 Nation 类型
template<>
Nation convertToT<Nation>(const std::string& value) {
    std::istringstream iss(value);
    Nation n;

    std::string part;
    std::getline(iss, part, '|');
    n.N_NATIONKEY = std::stoi(part);
    std::getline(iss, n.N_NAME, '|');
    std::getline(iss, part, '|');
    n.N_REGIONKEY = std::stoi(part);
    std::getline(iss, n.N_COMMENT, '|');

    return n;
}

// 特化模板函数为 Customer 类型
template<>
Customer convertToT<Customer>(const std::string& value) {
    std::istringstream iss(value);
    Customer c;
    std::string part;

    std::getline(iss, part, '|');
    c.C_CUSTKEY = std::stoi(part);
    std::getline(iss, c.C_NAME, '|');
    std::getline(iss, c.C_ADDRESS, '|');
    std::getline(iss, part, '|');
    c.C_NATIONKEY = std::stoi(part);
    std::getline(iss, c.C_PHONE, '|');
    std::getline(iss, part, '|');
    c.C_ACCTBAL = std::stof(part);
    std::getline(iss, c.C_MKTSEGMENT, '|');
    std::getline(iss, c.C_COMMENT, '|');

    return c;
}

// 特化模板函数为 LineItem 类型
template<>
LineItem convertToT<LineItem>(const std::string& value) {
    std::istringstream iss(value);
    LineItem l;
    std::string part;

    std::getline(iss, part, '|');
    l.L_ORDERKEY = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_PARTKEY = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_SUPPKEY = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_LINENUMBER = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_QUANTITY = std::stof(part);
    std::getline(iss, part, '|');
    l.L_EXTENDEDPRICE = std::stof(part);
    std::getline(iss, part, '|');
    l.L_DISCOUNT = std::stof(part);
    std::getline(iss, part, '|');
    l.L_TAX = std::stof(part);
    std::getline(iss, part, '|');
    l.L_RETURNFLAG = part[0];
    std::getline(iss, part, '|');
    l.L_LINESTATUS = part[0];
    std::getline(iss, l.L_SHIPDATE, '|');
    std::getline(iss, l.L_COMMITDATE, '|');
    std::getline(iss, l.L_RECEIPTDATE, '|');
    std::getline(iss, l.L_SHIPINSTRUCT, '|');
    std::getline(iss, l.L_SHIPMODE, '|');
    std::getline(iss, l.L_COMMENT, '|');

    return l;
}

// 特化模板函数为 Orders 类型
template<>
Orders convertToT<Orders>(const std::string& value) {
    std::istringstream iss(value);
    Orders o;
    std::string part;

    std::getline(iss, part, '|');
    o.O_ORDERKEY = std::stoi(part);
    std::getline(iss, part, '|');
    o.O_CUSTKEY = std::stoi(part);
    std::getline(iss, part, '|');
    o.O_ORDERSTATUS = part[0];
    std::getline(iss, part, '|');
    o.O_TOTALPRICE = std::stof(part);
    std::getline(iss, o.O_ORDERDATE, '|');
    std::getline(iss, o.O_ORDERPRIORITY, '|');
    std::getline(iss, o.O_CLERK, '|');
    std::getline(iss, part, '|');
    o.O_SHIPPRIORITY = std::stoi(part);
    std::getline(iss, o.O_COMMENT, '|');

    return o;
}

// 特化模板函数为 Part 类型
template<>
Part convertToT<Part>(const std::string& value) {
    std::istringstream iss(value);
    Part p;
    std::string part;

    std::getline(iss, part, '|');
    p.P_PARTKEY = std::stoi(part);
    std::getline(iss, p.P_NAME, '|');
    std::getline(iss, p.P_MFGR, '|');
    std::getline(iss, p.P_BRAND, '|');
    std::getline(iss, p.P_TYPE, '|');
    std::getline(iss, part, '|');
    p.P_SIZE = std::stoi(part);
    std::getline(iss, p.P_CONTAINER, '|');
    std::getline(iss, part, '|');
    p.P_RETAILPRICE = std::stof(part);
    std::getline(iss, p.P_COMMENT, '|');

    return p;
}

// 特化模板函数为 PartSupp 类型
template<>
PartSupp convertToT<PartSupp>(const std::string& value) {
    std::istringstream iss(value);
    PartSupp ps;
    std::string part;

    std::getline(iss, part, '|');
    ps.PS_PARTKEY = std::stoi(part);
    std::getline(iss, part, '|');
    ps.PS_SUPPKEY = std::stoi(part);
    std::getline(iss, part, '|');
    ps.PS_AVAILQTY = std::stoi(part);
    std::getline(iss, part, '|');
    ps.PS_SUPPLYCOST = std::stof(part);
    std::getline(iss, ps.PS_COMMENT, '|');

    return ps;
}

// 特化模板函数为 Region 类型
template<>
Region convertToT<Region>(const std::string& value) {
    std::istringstream iss(value);
    Region r;
    std::string part;

    std::getline(iss, part, '|');
    r.R_REGIONKEY = std::stoi(part);
    std::getline(iss, r.R_NAME, '|');
    std::getline(iss, r.R_COMMENT, '|');

    return r;
}

// 特化模板函数为 Supplier 类型
template<>
Supplier convertToT<Supplier>(const std::string& value) {
    std::istringstream iss(value);
    Supplier s;
    std::string part;

    std::getline(iss, part, '|');
    s.S_SUPPKEY = std::stoi(part);
    std::getline(iss, s.S_NAME, '|');
    std::getline(iss, s.S_ADDRESS, '|');
    std::getline(iss, part, '|');
    s.S_NATIONKEY = std::stoi(part);
    std::getline(iss, s.S_PHONE, '|');
    std::getline(iss, part, '|');
    s.S_ACCTBAL = std::stof(part);
    std::getline(iss, s.S_COMMENT, '|');

    return s;
}


// 特化模板函数为 Revenue0 类型
template<>
Revenue0 convertToT<Revenue0>(const std::string& value) {
    std::istringstream iss(value);
    Revenue0 r;
    std::string part;

    std::getline(iss, part, '|');
    r.supplier_no = std::stoi(part);
    std::getline(iss, part, '|');
    r.total_revenue = std::stod(part);

    return r;
}