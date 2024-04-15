#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

// Include the necessary header files
#include "Table.h"
#include "Structs.h"

void q13() {
    // Import the tables
    Table<Customer> customerTable;
    Table<Orders> ordersTable;

    // Load data from files
    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");

    // Alias for easier access
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();

    // Map to store customer key to count of orders
    std::unordered_map<int, int> customerOrderCount;

    // First, count the orders for each customer excluding specific comments
    for (const auto& order : orders) {
        if (order.O_COMMENT.find("special accounts") == std::string::npos) {  // Assuming the comment needs to not include this phrase
            customerOrderCount[order.O_CUSTKEY]++;
        }
    }

    // Map to store the number of customers with a specific number of orders
    std::map<int, int> orderCountDistribution;

    // Count how many customers have the same number of orders
    for (const auto& customer : customers) {
        int count = customerOrderCount[customer.C_CUSTKEY];
        orderCountDistribution[count]++;
    }

    // Convert map to a vector for sorting
    std::vector<std::pair<int, int>> sortedResults(orderCountDistribution.begin(), orderCountDistribution.end());

    // Sort the results
    std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first > b.first;  // descending order of count
        }
        return a.second > b.second;  // descending order of distribution
    });

    // Output the results
    std::cout << "Count of Orders\tNumber of Customers\n";
    for (const auto& result : sortedResults) {
        std::cout << result.first << "\t" << result.second << std::endl;
    }
}

