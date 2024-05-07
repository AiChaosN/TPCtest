#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

// 表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"

// 扩展的工具函数
#include "Tool.h"
#include <ctime>

void q12() {
    // begin
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;

    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // time
    clock_t start = clock();

    // from
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();

    // Build a map to relate orders with lineitems
    std::map<int, Orders> ordersMap;
    for (auto& o : orders) {
        ordersMap[o.O_ORDERKEY] = o;
    }

    struct CountInfo {
        int highLineCount = 0;
        int lowLineCount = 0;
    };

    std::map<std::string, CountInfo> shipModeCounts;

    for (auto& l : lineitems) {
        if ((l.L_SHIPMODE == "SHIP" || l.L_SHIPMODE == "REG AIR") &&
            l.L_COMMITDATE < l.L_RECEIPTDATE &&
            l.L_SHIPDATE < l.L_COMMITDATE &&
            l.L_RECEIPTDATE >= "1995-01-01" && l.L_RECEIPTDATE < "1996-01-01" &&
            ordersMap.count(l.L_ORDERKEY)) {
            Orders& o = ordersMap[l.L_ORDERKEY];
            bool isHighPriority = (o.O_ORDERPRIORITY == "1-URGENT" || o.O_ORDERPRIORITY == "2-HIGH");
            bool isLowPriority = (o.O_ORDERPRIORITY != "1-URGENT" && o.O_ORDERPRIORITY != "2-HIGH");

            if (isHighPriority) {
                shipModeCounts[l.L_SHIPMODE].highLineCount++;
            }
            if (isLowPriority) {
                shipModeCounts[l.L_SHIPMODE].lowLineCount++;
            }
        }
    }

    // Output results ordered by shipmode
    std::vector<std::pair<std::string, CountInfo>> sortedResults(shipModeCounts.begin(), shipModeCounts.end());
    std::sort(sortedResults.begin(), sortedResults.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    std::cout << "Ship Mode\tHigh Line Count\tLow Line Count\n";
    for (const auto& [shipMode, counts] : sortedResults) {
        std::cout << shipMode << "\t" << counts.highLineCount << "\t" << counts.lowLineCount << "\n";
    }
}

int main() {
    q12();
    return 0;
}

