#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <string>
#include <ctime>
#include <map>

#include "Table.h"
#include "Structs.h"
#include "Tool.h"

void q3() {
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;

    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    clock_t start = clock();

    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineItems = lineItemTable.getData();

    std::string orderDateCutoff = "1995-03-14";
    std::string shipDateCutoff = "1995-03-14";

    // Build customer to order map
    std::unordered_map<int, std::vector<Orders>> customerOrderMap;
    for (auto& order : orders) {
        if (order.O_ORDERDATE < orderDateCutoff) {
            customerOrderMap[order.O_CUSTKEY].push_back(order);
        }
    }

    // Filter customers in the 'AUTOMOBILE' market segment and build final order map
    std::unordered_map<int, std::vector<std::pair<Orders, Customer>>> orderCustomerMap;
    for (auto& customer : customers) {
        if (customer.C_MKTSEGMENT == "AUTOMOBILE") {
            auto it = customerOrderMap.find(customer.C_CUSTKEY);
            if (it != customerOrderMap.end()) {
                for (auto& order : it->second) {
                    orderCustomerMap[order.O_ORDERKEY].emplace_back(order, customer);
                }
            }
        }
    }


    // Calculate aggregates
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

    // Collect and sort results
    std::vector<std::tuple<int, double, std::string, int>> results;
    for (auto& [key, revenue] : aggregates) {
        results.emplace_back(std::get<0>(key), revenue, std::get<1>(key), std::get<2>(key));
    }

    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        if (std::get<1>(a) != std::get<1>(b)) return std::get<1>(a) > std::get<1>(b);
        return std::get<2>(a) < std::get<2>(b);
    });

    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    // for (auto& [orderKey, revenue, orderDate, shipPriority] : results) {
    //     std::cout << orderKey << "\t" << revenue << "\t" << orderDate << "\t" << shipPriority << std::endl;
    // }
}

int main() {
    q3();
    return 0;
}
