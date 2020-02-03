
#ifndef HZCC_SCANNER_HPP
#define HZCC_SCANNER_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include "dsa/dsa_stack.hpp"
#include "tok.hpp"

namespace hzcc {


class scanner {
protected:
        std::string             _file;
        std::string             _data;
        unsigned long           _size;
        unsigned int            _line, _column;
        unsigned long           _pos;


public:
        explicit scanner(std::string &filename);

        ~scanner();

        void fileReader(std::string &filename);

        unsigned int line() const;

        unsigned int column() const;

        void run();

protected:
        bool is_file_correct() const;

        void skip_ignore_block();

        void skip_short_comment();

        void skip_long_comment();

        bool match(std::string str) const;

        void eat(unsigned long skipNum);

        bool is_white_space(char c);

        bool is_new_line_char(char c) const;

        bool is_arith_op(char c) const;

        tok* next_token();

        std::string scan_string();

        std::string scan_id();

        void escape(std::string &str);

        void panic(const std::string &err) const;

        double eval();

        bool is_end();

        void change_line();

        double scan_num();

        char ops_order_between(char op1, char op2);
};


}

#endif //HZCC_SCANNER_HPP
