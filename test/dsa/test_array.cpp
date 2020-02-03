#include "test_array.hpp"
#include <array>

namespace hzcc {

    namespace testcc {

        void test_array()
        {
                test_array_case1();
        }

        void test_array_case1()
        {
                // TestCase1: 测试int型数组自动扩容缩容及其他基本功能
                auto *arr = new hzcc::dsa_array<int>(100);
                arr->print_info();
                for (int i = 0; i < 100; i++) {
                        arr->add_last(i);
                }
                arr->print_info(); // 此时数组满
                arr->add(80, 150); // 添加一个数字，数组自动扩容
                arr->print_info();
                arr->rm_elem(4);
                arr->rm(0);
                arr->print_info();
                for (int i = 0; i < 49; i++) {
                        arr->rm(i);
                }
                arr->print_info(); // 此时应自动缩容,输出2,5,7,9,11,13,....
                std::cout << arr->get(10) << std::endl;
                arr->set(10, 10000214);
                std::cout << arr->get(10) << std::endl;
                delete arr;
        }

    } // namespace testcc end
} // namespace hzcc end