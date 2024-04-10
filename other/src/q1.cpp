#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include "func/Structs.h"
#include <iomanip>  // 需要包含这个头文件来使用 std::setprecision 和 std::fixed

#include <fstream>
#include <sstream>
#include <string>

std::vector<LineItem> loadData() {
    std::vector<LineItem> data;
    std::ifstream file("../data/lineitem.tbl"); 
    std::string line;

    while (std::getline(file, line)) { 
        std::stringstream linestream(line); 
        LineItem item;
        std::string value;


        std::getline(linestream, value, '|'); 
        std::getline(linestream, value, '|'); 
        std::getline(linestream, value, '|');
        std::getline(linestream, value, '|');
        std::getline(linestream, value, '|');
        item.l_quantity = std::stod(value);
        std::getline(linestream, value, '|');
        item.l_extendedprice = std::stod(value);
        std::getline(linestream, value, '|');
        item.l_discount = std::stod(value);
        std::getline(linestream, value, '|');
        item.l_tax = std::stod(value);
        std::getline(linestream, item.l_returnflag, '|');
        std::getline(linestream, item.l_linestatus, '|');
        std::getline(linestream, item.l_shipdate, '|');

        data.push_back(item);
    }

    return data;
}

int main() {
    std::vector<LineItem> lineitems = loadData();

    // 使用map来聚合数据，键是(l_returnflag, l_linestatus)的组合
    std::map<std::tuple<std::string, std::string>, std::tuple<double, double, double, double, double, int>> aggregates;

    for (const auto& item : lineitems) {
        // 应用过滤条件
        if (item.l_shipdate <= "1998-09-02") { // 示例日期过滤逻辑
            auto& agg = aggregates[std::make_tuple(item.l_returnflag, item.l_linestatus)];
            std::get<0>(agg) += item.l_quantity;
            std::get<1>(agg) += item.l_extendedprice;
            std::get<2>(agg) += item.l_extendedprice * (1 - item.l_discount);
            std::get<3>(agg) += item.l_extendedprice * (1 - item.l_discount) * (1 + item.l_tax);
            std::get<4>(agg) += item.l_discount;
            std::get<5>(agg) += 1;
        }
    }

    // 输出结果
    for (const auto& [key, agg] : aggregates) {
        auto [l_returnflag, l_linestatus] = key;
        auto [sum_qty, sum_base_price, sum_disc_price, sum_charge, total_discount, count_order] = agg;
        double avg_qty = sum_qty / count_order;
        double avg_price = sum_base_price / count_order;
        double avg_disc = total_discount / count_order;

        // std::cout << "Return Flag: " << l_returnflag << ", Line Status: " << l_linestatus
        //           << ", Sum Qty: " << sum_qty << ", Sum Base Price: " << sum_base_price
        //           << ", Sum Disc Price: " << sum_disc_price << ", Sum Charge: " << sum_charge
        //           << ", Avg Qty: " << avg_qty << ", Avg Price: " << avg_price
        //           << ", Avg Disc: " << avg_disc << ", Count Order: " << count_order << std::endl;
        std::cout << std::fixed << std::setprecision(2);  // 设置浮点数显示为固定小数点格式，保留两位小数
        std::cout << l_returnflag << '|'
          << l_linestatus << '|'
          << std::setprecision(0) << sum_qty << '|'
          << std::setprecision(2) << sum_base_price << '|'
          << sum_disc_price << '|'
          << sum_charge << '|'
          << avg_qty << '|'
          << avg_price << '|'
          << avg_disc << '|'
          << count_order << std::endl;
    }

    return 0;
}