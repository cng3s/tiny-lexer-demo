#ifndef HZCC_TEST_STACK_HPP
#define HZCC_TEST_STACK_HPP

#include "../../dsa/dsa_ll_stack.hpp"

namespace hzcc {
    namespace testcc {

        void test_stack_case1()
        {
                auto stack = dsa_ll_stack<int>();
                for (int i = 0; i < 100; i++) {
                        stack.push(i);
                }
        }

        void test_stack()
        {
                test_stack_case1();
        }
    }
}

#endif //MYCC_STACKTEST_HPP
