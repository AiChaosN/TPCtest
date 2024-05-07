#include <iostream>
#include <algorithm>
#include <map>

//表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"

//扩展的工具函数
#include "Tool.h"
#include <ctime>

void q3() {
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;

    // Import data
    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // Prepare data
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineItems = lineItemTable.getData();

    // String literals for date comparison
    std::string orderDateCutoff = "1995-03-14";
    std::string shipDateCutoff = "1995-03-14";

    // Hash maps for efficient joins
    std::unordered_map<int, std::vector<std::pair<Orders, Customer>>> orderCustomerMap;
    for (auto& customer : customers) {
        if (customer.C_MKTSEGMENT == "AUTOMOBILE") {
            for (auto& order : orders) {
                if (order.O_ORDERDATE < orderDateCutoff && customer.C_CUSTKEY == order.O_CUSTKEY) {
                    orderCustomerMap[order.O_ORDERKEY].emplace_back(order, customer);
                }
            }
        }
    }

    std::map<std::tuple<int, std::string, int>, double> aggregates;
    for (auto& lineItem : lineItems) {
        if (lineItem.L_SHIPDATE > shipDateCutoff) {
            auto it = orderCustomerMap.find(lineItem.L_ORDERKEY);
            if (it != orderCustomerMap.end()) {
                for (auto& [order, customer] : it->second) {
                    auto key = std::make_tuple(lineItem.L_ORDERKEY, order.O_ORDERDATE, order.O_SHIPPRIORITY);
                    aggregates[key] += lineItem.L_EXTENDEDPRICE * (1 - lineItem.L_DISCOUNT);
                }
            }
        }
    }

    // Collect results
    std::vector<std::tuple<int, double, std::string, int>> results;
    for (auto& [key, revenue] : aggregates) {
        results.emplace_back(std::get<0>(key), revenue, std::get<1>(key), std::get<2>(key));
    }

    // Sort results
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        if (std::get<1>(a) != std::get<1>(b)) return std::get<1>(a) > std::get<1>(b);
        return std::get<2>(a) < std::get<2>(b);
    });

    // Print results
    std::cout << "---------print results-------\n" << std::endl;
    for (auto& [orderKey, revenue, orderDate, shipPriority] : results) {
        std::cout << orderKey << "\t" << revenue << "\t" << orderDate << "\t" << shipPriority << std::endl;
    }
}

int main() {
    q3();
    return 0;
}