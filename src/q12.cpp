#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include <algorithm>

#include "Table.h"
#include "Structs.h"

// 扩展的工具函数
#include "Tool.h"
#include <ctime>

void q12() {
    // Import the tables
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;

    // Load data
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // time
    clock_t start = clock();

    // from
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();

    // Prepare results container
    std::map<std::string, std::tuple<int, int>> results;  // Key: shipmode, Value: tuple of high_line_count, low_line_count

    // Processing the join and conditions
    for (const auto& l : lineitems) {
        if (l.L_SHIPMODE == "SHIP" || l.L_SHIPMODE == "REG AIR") {
            if (l.L_COMMITDATE < l.L_RECEIPTDATE && l.L_SHIPDATE < l.L_COMMITDATE &&
                l.L_RECEIPTDATE >= "1995-01-01" && l.L_RECEIPTDATE < "1996-01-01") {
                for (const auto& o : orders) {
                    if (o.O_ORDERKEY == l.L_ORDERKEY) {
                        int high_count = 0;
                        int low_count = 0;

                        if (o.O_ORDERPRIORITY == "1-URGENT" || o.O_ORDERPRIORITY == "2-HIGH") {
                            high_count = 2;
                        } else {
                            low_count = 2;
                        }

                        if (results.find(l.L_SHIPMODE) != results.end()) {
                            std::get<0>(results[l.L_SHIPMODE]) += high_count;
                            std::get<1>(results[l.L_SHIPMODE]) += low_count;
                        } else {
                            results[l.L_SHIPMODE] = std::make_tuple(high_count, low_count);
                        }
                    }
                }
            }
        }
    }

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    // Sorting the results (C++ maps are sorted by key by default)
    // Output the results
    std::cout << "results for Q12:\n";
    std::cout << "Ship_Mode\tHigh_Line_Count\tLow_Line_Count\n";
    for (const auto& res : results) {
        std::cout << res.first << "\t"
                  << std::get<0>(res.second) << "\t"
                  << std::get<1>(res.second) << std::endl;
    }
}

int main() {
    q12();
    return 0;
}

