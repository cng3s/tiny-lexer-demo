#ifndef HZCC_TOK_HPP
#define HZCC_TOK_HPP

#include <iostream>
#include "tok.hpp"

namespace hzcc {

class tok;
class t_id;
class t_string;
class t_num;
void print_tok(tok *t);

enum TAG {
        // TAG: id EOF num string
        TAG_ID, TAG_EOF, TAG_NUM, TAG_STRING,


        // TYPE
        T_INT, T_FLOAT, T_DOUBLE, T_CHAR, T_VOID, T_ENUM, T_UNION, T_STRUCT,

        // TYPE SPECIFIER: volatile const static register
        T_SPECIFIER_VOLATILE, T_SPECIFIER_CONST, T_SPECIFIER_STATIC, T_SPECIFIER_REGISTER, T_SPECIFIER_EXTERN,
        T_SPECIFIER_AUTO,


        // SEP == SEPLIT: ; , . () [] {} :
        SEP_SEMI, SEP_COMMA, SEP_DOT, SEP_LPAREN, SEP_RPAREN,
        SEP_LBRACK, SEP_RBRACK, SEP_LCURLY, SEP_RCURLY, SEP_COLON,


        // OP == OPERATOR
        OP_PLUS, OP_UNP  = OP_PLUS, OP_ADD = OP_PLUS, OP_PREFIX_UNP, OP_POSTFIX_UNP,
        OP_MINUS, OP_UNM = OP_MINUS,  OP_SUB = OP_MINUS, OP_PREFIX_UNM, OP_POSTFIX_UNM,
        OP_STAR, OP_PTR = OP_STAR,  OP_MUL = OP_STAR,
        OP_PTR_2_MEMBER,
        OP_DIV,OP_ADD_ASSIGN, OP_SUB_ASSIGN, OP_MUL_ASSIGN, OP_DIV_ASSIGN,OP_MOD, OP_MOD_ASSIGN,
        OP_AND, OP_OR,  OP_NOT, OP_LT,  OP_GT, OP_LE, OP_GE, OP_EQ, OP_NE, OP_ASSIGN,
        OP_BIT_AND, OP_BIT_AND_ASSIGN, OP_BIT_OR, OP_BIT_OR_ASSIGN, OP_BIT_XOR, OP_BIT_XOR_ASSIGN,
        OP_BIT_NOT, OP_BIT_SHR, OP_BIT_SHR_ASSIGN, OP_BIT_SHL, OP_BIT_SHL_ASSIGN,


        // KW == KEYWORD
        KW_RETURN,  KW_IF, KW_ELSE,  KW_WHILE, KW_DO, KW_SWITCH, KW_CASE, KW_DEFAULT,
        KW_ELIF, KW_FOR,  KW_BREAK, KW_GOTO,  KW_INLINE,  KW_TYPEDEF, KW_CONTINUE,


        // PP == Pre-Processor: #include #ifndef #define #ifdef #elif #else
        PP_INCLUDE, PP_IFNDEF, PP_DEFINE, PP_IFDEF, PP_ELIF, PP_ELSE,
};


class tok {
protected:
        enum TAG        _tag;
        unsigned int    _line, _column;

public:

        explicit tok(enum TAG tag, unsigned int line, unsigned int column)
                : _tag(tag), _line(line), _column(column)
        {}

        ~tok() = default;

protected:
        explicit tok() = default;

public:
        inline enum TAG tag() const
        {
                return _tag;
        }

        inline unsigned int line() const
        {
                return _line;
        }

        inline unsigned int column() const
        {
                return _column;
        }

};


class t_id : public tok {
private:
        std::string _id;

public:
        explicit t_id(std::string ID, unsigned int line, unsigned int column)
                : _id(std::move(ID)), tok(TAG_ID, line, column)
        {}

        ~t_id() = default;

public:
        std::string id() const
        {
                return _id;
        }
};

class t_num : public tok {
protected:
        double _val;               // value

public:
        t_num(double value, unsigned int line, unsigned int column)
                : _val(value), tok(TAG_NUM, line, column)
        {}

        ~t_num() = default;

public:

        double val() const
        {
                return _val;
        }
};


class t_string : public tok {
protected:
        std::string _val;

public:
        t_string(std::string value, unsigned int line, unsigned int column)
                : _val(std::move(value)), tok(TAG_STRING, line, column)
        {}

        ~t_string() = default;

public:
        std::string val() const
        {
                return _val;
        }
};

}


#endif //HZCC_TOK_HPP
