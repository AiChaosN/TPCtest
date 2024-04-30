#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

// 表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"

// 扩展的工具函数
#include "Tool.h"
#include <ctime>

void q4() {
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

    // Preprocess to filter lineitems
    std::unordered_map<int, bool> validLineItems;
    for (auto& l : lineitems) {
        if (l.L_COMMITDATE < l.L_RECEIPTDATE) {
            validLineItems[l.L_ORDERKEY] = true;
        }
    }

    // Initialize map for counting orders by priority
    std::map<std::string, int> orderCounts;

    // Filter orders and count
    for (auto& o : orders) {
        if (o.O_ORDERDATE >= "1995-01-01" && o.O_ORDERDATE < "1995-04-01" && validLineItems.count(o.O_ORDERKEY)) {
            orderCounts[o.O_ORDERPRIORITY]++;
        }
    }

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;


    // Sort by priority (already sorted due to using std::map)
    // Output results
    std::cout << "Order Priority\tCount\n";
    for (const auto& [priority, count] : orderCounts) {
        std::cout << priority << "\t" << count << "\n";
    }
}

int main() {
    q4();
    return 0;
}

