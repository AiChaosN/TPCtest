#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Assume these are defined in included headers
#include "Table.h"
#include "Structs.h"

void q15() {
    // Load data for suppliers
    Table<Supplier> supplierTable;
    Table<Revenue> revenueTable;  // Assuming Revenue struct is defined to represent revenue0

    // Import data from files
    supplierTable.importData("../data/supplier.tbl");
    revenueTable.importData("../data/revenue0.tbl");  // Assuming this data source mimics the revenue0 view

    // Alias for easier access
    auto& suppliers = supplierTable.getData();
    auto& revenues = revenueTable.getData();

    // Find the maximum total revenue
    double maxRevenue = 0;
    for (const auto& revenue : revenues) {
        if (revenue.total_revenue > maxRevenue) {
            maxRevenue = revenue.total_revenue;
        }
    }

    // Find all suppliers whose total revenue matches the max revenue
    std::vector<Supplier> maxRevenueSuppliers;
    for (const auto& supplier : suppliers) {
        for (const auto& revenue : revenues) {
            if (supplier.S_SUPPKEY == revenue.supplier_no && revenue.total_revenue == maxRevenue) {
                maxRevenueSuppliers.push_back(supplier);
                break;  // Break as we need only one entry per supplier that matches
            }
        }
    }

    // Sort suppliers by supplier key
    std::sort(maxRevenueSuppliers.begin(), maxRevenueSuppliers.end(), [](const Supplier& a, the Supplier& b) {
        return a.S_SUPPKEY < b.S_SUPPKEY;
    });

    // Output results
    std::cout << "SuppKey\tName\tAddress\tPhone\tTotal Revenue\n";
    for (const auto& supplier : maxRevenueSuppliers) {
        std::cout << supplier.S_SUPPKEY << "\t"
                  << supplier.S_NAME << "\t"
                  << supplier.S_ADDRESS << "\t"
                  << supplier.S_PHONE << "\t"
                  << maxRevenue << std::endl;
    }
}

int main() {
    q15();
    return 0;
}

