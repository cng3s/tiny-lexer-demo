#ifndef HZCC_TEST_PARSER_CPP
#define HZCC_TEST_PARSER_CPP

#include "../../scanner.hpp"
#include "../dsa/test_array.hpp"

namespace hzcc {

    namespace testcc {
        void test_scanner_case1()
        {
            std::string filename = "../test/scanner/samples/program4.c";
            auto *lexer = new scanner(filename);
            delete lexer;
        }

        void test_scanner()
        {
            test_scanner_case1();
        }
    }
}

#endif