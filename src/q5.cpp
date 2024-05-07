#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <ctime>
#include "Table.h"
#include "Structs.h"
#include "Tool.h"

void q5() {
    // 初始化表和导入数据
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;
    Table<Supplier> supplierTable;
    Table<Nation> nationTable;
    Table<Region> regionTable;

    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    supplierTable.importData("../data/supplier.tbl");
    nationTable.importData("../data/nation.tbl");
    regionTable.importData("../data/region.tbl");

    clock_t start = clock(); 

    // 获取数据引用
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& nations = nationTable.getData();
    auto& regions = regionTable.getData();

    // 构建映射
    std::unordered_map<int, Customer> customerMap;
    for (auto& c : customers) {
        customerMap[c.C_CUSTKEY] = c;
    }

    std::unordered_map<int, std::vector<Orders>> ordersMap;
    for (auto& o : orders) {
        if (o.O_ORDERDATE >= "1995-01-01" && o.O_ORDERDATE < "1996-01-01") {
            ordersMap[o.O_ORDERKEY].push_back(o);
        }
    }

    std::unordered_map<int, std::vector<LineItem>> lineitemMap;
    for (auto& l : lineitems) {
        lineitemMap[l.L_ORDERKEY].push_back(l);
    }

    std::unordered_map<int, Nation> nationMap;
    for (auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n;
    }

    std::unordered_map<int, Region> regionMap;
    for (auto& r : regions) {
        if (r.R_NAME == "EUROPE") {
            regionMap[r.R_REGIONKEY] = r;
        }
    }

    // 结果聚合
    std::map<std::string, double> aggregates;

    for (auto& s : suppliers) {
        auto s_nation = nationMap.find(s.S_NATIONKEY);
        if (s_nation != nationMap.end() && regionMap.count(s_nation->second.N_REGIONKEY)) {
            for (auto& l : lineitemMap[s.S_SUPPKEY]) {
                auto o_iter = ordersMap.find(l.L_ORDERKEY);
                if (o_iter != ordersMap.end()) {
                    for (auto& o : o_iter->second) {
                        aggregates[s_nation->second.N_NAME] += l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
                    }
                }
            }
        }
    }

    // 结果排序
    std::vector<std::pair<std::string, double>> results(aggregates.begin(), aggregates.end());
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    clock_t stop = clock(); // 记录结束时间
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    // 打印结果
    for (auto& [name, revenue] : results) {
        std::cout << name << "\t" << revenue << std::endl;
    }
}

int main() {
    q5();
    return 0;
}
