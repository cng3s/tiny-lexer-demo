#ifndef MYCC_TEST_PLATFORM_HPP
#define MYCC_TEST_PLATFORM_HPP

#include "dsa/test_array.hpp"
#include "dsa/test_linked_list.hpp"
#include "scanner/test_parser.hpp"
#include "dsa/test_avl_map.hpp"

namespace hzcc {

    namespace testcc {

        void run_tester() {
                test_scanner();
        }

    }

}
#endif