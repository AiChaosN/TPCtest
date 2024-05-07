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

int extractYear(const std::string& dateStr) {
    // Assuming dateStr is in the format "YYYY-MM-DD"
    return std::stoi(dateStr.substr(0, 4));
}

void q8() {
    // begin
    Table<Part> partTable;
    Table<Supplier> supplierTable;
    Table<LineItem> lineItemTable;
    Table<Orders> ordersTable;
    Table<Customer> customerTable;
    Table<Nation> nationTable;
    Table<Region> regionTable;

    partTable.importData("../data/part.tbl");
    supplierTable.importData("../data/supplier.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    ordersTable.importData("../data/orders.tbl");
    customerTable.importData("../data/customer.tbl");
    nationTable.importData("../data/nation.tbl");
    regionTable.importData("../data/region.tbl");

    // time
    clock_t start = clock();

    // from
    auto& parts = partTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& orders = ordersTable.getData();
    auto& customers = customerTable.getData();
    auto& nations = nationTable.getData();
    auto& regions = regionTable.getData();

    // Create maps for quick lookup
    std::map<int, Region> regionMap;
    for (auto& r : regions) {
        regionMap[r.R_REGIONKEY] = r;
    }

    std::map<int, Nation> nationMap;
    for (auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n;
    }

    // Prepare to aggregate data
    std::map<int, double> totalVolumeByYear;
    std::map<int, double> iraqVolumeByYear;

    for (auto& o : orders) {
        for (auto& l : lineitems) {
            if (l.L_ORDERKEY == o.O_ORDERKEY) {
                for (auto& c : customers) {
                    if (c.C_CUSTKEY == o.O_CUSTKEY && nationMap.count(c.C_NATIONKEY) &&
                        regionMap[nationMap[c.C_NATIONKEY].N_REGIONKEY].R_NAME == "MIDDLE EAST") {
                        int year = extractYear(o.O_ORDERDATE);
                        double volume = l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
                        totalVolumeByYear[year] += volume;

                        if (nationMap[c.C_NATIONKEY].N_NAME == "IRAQ") {
                            iraqVolumeByYear[year] += volume;
                        }
                    }
                }
            }
        }
    }

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;


    // Compute market share and output
    std::cout << "Year\tMarket Share\n";
    for (auto& [year, totalVolume] : totalVolumeByYear) {
        double iraqVolume = iraqVolumeByYear[year];
        double marketShare = (totalVolume == 0) ? 0 : (iraqVolume / totalVolume);
        std::cout << year << "\t" << marketShare << "\n";
    }
}

int main() {
    q8();
    return 0;
}

