#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include "Table.h"
#include "Structs.h"
#include <ctime>

void q13() {
    // Import data
    Table<Customer> customerTable;
    Table<Orders> ordersTable;

    // Load data from files
    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");

    // Get data references
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();

    // Start time measurement
    clock_t start = clock();

    // Create a map to count orders for each customer that do not include "special accounts" in the comment
    std::unordered_map<int, int> customerOrderCount;
    
    // Initialize all customers in the map with a count of zero
    for (const auto& customer : customers) {
        customerOrderCount[customer.C_CUSTKEY] = 0;
    }

    // Increment count for orders that do not contain "special accounts" in the comment
    for (const auto& order : orders) {
        if (order.O_COMMENT.find("special accounts") == std::string::npos) {
            customerOrderCount[order.O_CUSTKEY]++;
        }
    }

    // Map to store the distribution of order counts
    std::map<int, int> orderCountDistribution;

    // Populate the distribution map
    for (const auto& pair : customerOrderCount) {
        int count = pair.second;
        orderCountDistribution[count]++;
    }

    // Sort the results for output
    std::vector<std::pair<int, int>> sortedResults(orderCountDistribution.begin(), orderCountDistribution.end());

    // Custom sort to order by number of customers descending and then by count of orders descending
    std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first > b.first;  // Descending order of order count
        }
        return a.second > b.second;  // Descending order of customer count
    });

    // Stop time measurement
    clock_t stop = clock();
    std::cout << "Execution time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    // Print results
    std::cout << "Count of Orders\tNumber of Customers\n";
    for (const auto& result : sortedResults) {
        std::cout << result.first << "\t" << result.second << std::endl;
    }
}

int main() {
    q13();
    return 0;
}
