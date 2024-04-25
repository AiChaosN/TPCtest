#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

// Include the necessary header files
#include "Table.h"
#include "Structs.h"
#include <ctime>

void q13() {
    // Import 
    Table<Customer> customerTable;
    Table<Orders> ordersTable;

    // Load data 
    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");

    // time
    clock_t start = clock();

    // from
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();

    // Map to store 
    std::unordered_map<int, int> customerOrderCount;

    // Count 
    for (const auto& order : orders) {
        if (order.O_COMMENT.find("special accounts") == std::string::npos) { 
            customerOrderCount[order.O_CUSTKEY]++;
        }
    }

    // Map to store 
    std::map<int, int> orderCountDistribution;

    // Count
    for (const auto& customer : customers) {
        int count = customerOrderCount[customer.C_CUSTKEY];
        orderCountDistribution[count]++;
    }

    // order by
    std::vector<std::pair<int, int>> sortedResults(orderCountDistribution.begin(), orderCountDistribution.end());

    // Sort
    std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first > b.first;  
        }
        return a.second > b.second;  
    });
    
    // time off
    clock_t stop = clock();
    std::cout << "执行时间13: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    // Output
    std::cout << "Count of Orders\tNumber of Customers\n";
    for (const auto& result : sortedResults) {
        std::cout << result.first << "\t" << result.second << std::endl;
    }
}

int main() {
    q13();
    return 0;
}

