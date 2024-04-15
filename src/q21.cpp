#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

// Include necessary headers
#include "Table.h"
#include "Structs.h"

void q21() {
    // Load data for suppliers, lineitems, orders, and nations
    Table<Supplier> supplierTable;
    Table<LineItem> lineItemTable;
    Table<Orders> ordersTable;
    Table<Nation> nationTable;

    // Import data from files
    supplierTable.importData("../data/supplier.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    ordersTable.importData("../data/orders.tbl");
    nationTable.importData("../data/nation.tbl");

    // Alias for easier access
    auto& suppliers = supplierTable.getData();
    auto& lineItems = lineItemTable.getData();
    auto& orders = ordersTable.getData();
    auto& nations = nationTable.getData();

    // Preparing a map for nation keys to filter by nation name 'INDIA'
    std::unordered_map<int, std::string> nationKeyMap;
    for (const auto& n : nations) {
        nationKeyMap[n.N_NATIONKEY] = n.N_NAME;
    }

    // Mapping orders to a specific status 'F' and mapping line items to orders
    std::unordered_map<int, const Orders*> ordersMap;
    for (const auto& o : orders) {
        if (o.O_ORDERSTATUS == 'F') {
            ordersMap[o.O_ORDERKEY] = &o;
        }
    }

    // Suppliers from India
    std::unordered_map<int, const Supplier*> indianSuppliers;
    for (const auto& s : suppliers) {
        if (nationKeyMap[s.S_NATIONKEY] == "INDIA") {
            indianSuppliers[s.S_SUPPKEY] = &s;
        }
    }

    // Count the number of waits per supplier name
    std::map<std::string, int> numWait;

    // Check each line item for the conditions specified
    for (const auto& l1 : lineItems) {
        if (ordersMap.find(l1.L_ORDERKEY) != ordersMap.end() && indianSuppliers.find(l1.L_SUPPKEY) != indianSuppliers.end()) {
            if (l1.L_RECEIPTDATE > l1.L_COMMITDATE) {
                bool otherSupplierExists = false;
                bool otherSupplierLateExists = false;

                // Check for existence of other suppliers' line items
                for (const auto& l2 : lineItems) {
                    if (l2.L_ORDERKEY == l1.L_ORDERKEY && l2.L_SUPPKEY != l1.L_SUPPKEY) {
                        otherSupplierExists = true;
                        if (l2.L_RECEIPTDATE > l2.L_COMMITDATE) {
                            otherSupplierLateExists = true;
                            break;
                        }
                    }
                }

                if (otherSupplierExists && !otherSupplierLateExists) {
                    numWait[indianSuppliers[l1.L_SUPPKEY]->S_NAME]++;
                }
            }
        }
    }

    // Prepare sorted results
    std::vector<std::pair<std::string, int>> sortedResults(numWait.begin(), numWait.end());
    std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
    });

    // Output the results, limited to the top 100 entries
    std::cout << "Supplier Name\tNumWait\n";
    int count = 0;
    for (const auto& result : sortedResults) {
        if (++count > 100) break;
        std::cout << result.first << "\t" << result.second << std::endl;
    }
}

