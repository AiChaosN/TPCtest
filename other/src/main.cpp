#include "Table.h"
#include "Structs.h"

#include "q.h"

//计时器
#include <iostream>
#include <chrono>


// 分隔符
void delimiter()
{
    std::cout << "\n----------------\n----------------\n" << std::endl;
}

int main() {
    auto time_function = [](auto&& func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();  // 调用函数
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;
    };

    time_function(q1);
    delimiter();

    time_function(q3);
    delimiter();

    time_function(q5);
    delimiter();

    time_function(q7);
    delimiter();

    time_function(q9);
    delimiter();

    time_function(q11);
    delimiter();

    time_function(q13);
    delimiter();

    // time_function(q15); // Uncomment when bug fixed and revenus0.tbl is available
    // delimiter();

    time_function(q17);
    delimiter();

    time_function(q19);
    delimiter();

    time_function(q21);

    return 0;
}