// Structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

/*
    * Structs.h
    * define the struct of the tables
    * define the convertToT function
*/


// define the struct of the tables
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

// new Sreuct for q14
struct Revenue0 {
    int supplier_no;
    double total_revenue;
};

// define the convertToT function
template<typename T>
T convertToT(const std::string& value);


template<>
Nation convertToT<Nation>(const std::string& value);


template<>
Customer convertToT<Customer>(const std::string& value);


template<>
LineItem convertToT<LineItem>(const std::string& value);


template<>
Orders convertToT<Orders>(const std::string& value);


template<>
Part convertToT<Part>(const std::string& value);


template<>
PartSupp convertToT<PartSupp>(const std::string& value);


template<>
Region convertToT<Region>(const std::string& value);


template<>
Supplier convertToT<Supplier>(const std::string& value);

// new convertToT function for q14
template<>
Revenue0 convertToT<Revenue0>(const std::string& value);
#endif // STRUCTS_H
