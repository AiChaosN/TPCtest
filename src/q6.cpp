#include <iostream>
#include <vector>
#include <string>
#include <numeric>

// 表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"

// 扩展的工具函数
#include "Tool.h"
#include <ctime>

void q6() {
    // begin
    Table<LineItem> lineItemTable;

    lineItemTable.importData("../data/lineitem.tbl");
    
    // time
    clock_t start = clock();

    // from
    auto& lineitems = lineItemTable.getData();

    float totalRevenue = 0.0;

    // Process each line item
    for (auto& l : lineitems) {
        if (l.L_SHIPDATE >= "1995-01-01" && l.L_SHIPDATE < "1996-01-01" &&
            l.L_DISCOUNT >= 0.01 && l.L_DISCOUNT <= 0.03 &&
            l.L_QUANTITY < 24) {
            totalRevenue += l.L_EXTENDEDPRICE * l.L_DISCOUNT;
        }
    }

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    // Output the results
    std::cout << "q6 results:" << std::endl;
    std::cout << "Total Revenue: " << totalRevenue << std::endl;
}

int main() {
    q6();
    return 0;
}

