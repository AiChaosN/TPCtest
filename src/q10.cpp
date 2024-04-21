#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

// 表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"
#include "q.h"
// 扩展的工具函数
#include "Tool.h"

void q10() {
    // begin
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;
    Table<Nation> nationTable;

    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    nationTable.importData("../data/nation.tbl");

    // from
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& nations = nationTable.getData();

    // Join logic using maps for efficient lookups
    std::map<int, Orders> ordersMap;
    for (auto& o : orders) {
        if (o.O_ORDERDATE >= "1994-05-01" && o.O_ORDERDATE < "1994-08-01") {
            ordersMap[o.O_ORDERKEY] = o;
        }
    }

    std::map<int, Nation> nationsMap;
    for (auto& n : nations) {
        nationsMap[n.N_NATIONKEY] = n;
    }

    // Aggregate data
    struct CustomerInfo {
        double revenue = 0;
        std::string name;
        double acctbal;
        std::string phone;
        std::string nationName;
        std::string address;
        std::string comment;
    };

    std::map<int, CustomerInfo> customerRevenue;

    for (auto& l : lineitems) {
        if (ordersMap.count(l.L_ORDERKEY) && l.L_RETURNFLAG == 'R') {
            Orders& o = ordersMap[l.L_ORDERKEY];
            Customer& c = customers[o.O_CUSTKEY];
            Nation& n = nationsMap[c.C_NATIONKEY];
            customerRevenue[c.C_CUSTKEY].revenue += l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
            customerRevenue[c.C_CUSTKEY].name = c.C_NAME;
            customerRevenue[c.C_CUSTKEY].acctbal = c.C_ACCTBAL;
            customerRevenue[c.C_CUSTKEY].phone = c.C_PHONE;
            customerRevenue[c.C_CUSTKEY].nationName = n.N_NAME;
            customerRevenue[c.C_CUSTKEY].address = c.C_ADDRESS;
            customerRevenue[c.C_CUSTKEY].comment = c.C_COMMENT;
        }
    }

    // Sorting results by revenue
    std::vector<std::pair<int, CustomerInfo>> sortedResults(customerRevenue.begin(), customerRevenue.end());
    std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
        return a.second.revenue > b.second.revenue; // Descending order
    });

    // Select top 20 results
    int count = 0;
    for (const auto& [custKey, info] : sortedResults) {
        if (++count > 20) break;
        std::cout << custKey << ", " << info.name << ", " << info.revenue << ", " << info.acctbal << ", "
                  << info.nationName << ", " << info.address << ", " << info.phone << ", " << info.comment << std::endl;
    }
}

