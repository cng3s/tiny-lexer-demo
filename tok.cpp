#include "tok.hpp"


namespace hzcc {

void print_tok(tok *t)
{
        std::cout << "tok <";
        TAG tag = t->tag();
        switch(tag) {
        case TAG_NUM: {
                std::cout << "TAG_NUM," << ((t_num*)t)->val();
                break;
        }
        case TAG_STRING: {
                std::cout << "TAG_STRING," << ((t_string*)t)->val();
                break;
        }
        case TAG_ID: {
                std::cout << "TAG_ID" << ((t_id*)t)->id();
                break;
        }
        case TAG_EOF:                   std::cout << "TAG_EOF";                 break;
        case T_INT:                     std::cout << "T_INT";                   break;
        case T_CHAR:                    std::cout << "T_CHAR";                  break;
        case T_ENUM:                    std::cout << "T_ENUM";                  break;
        case T_DOUBLE:                  std::cout << "T_DOUBLE";                break;
        case T_FLOAT:                   std::cout << "T_FLOAT";                 break;
        case T_UNION:                   std::cout << "T_UNION";                 break;
        case T_VOID:                    std::cout << "T_VOID";                  break;
        case T_SPECIFIER_VOLATILE:      std::cout << "T_SEPCIFIER_VOLATILE";    break;
        case T_SPECIFIER_STATIC:        std::cout << "T_SPECIFIER_STATIC";      break;
        case T_SPECIFIER_CONST:         std::cout << "T_SPECIFIER_CONST";       break;
        case T_SPECIFIER_REGISTER:      std::cout << "T_SPECIFIER_REGISTER";    break;
        case T_SPECIFIER_AUTO:          std::cout << "T_SPECIFIER_AUTO";        break;
        case SEP_DOT:                   std::cout << "SEP_DOT";                 break;
        case SEP_COLON:                 std::cout << "SEP_COLON";               break;
        case SEP_COMMA:                 std::cout << "SEP_COMMA";               break;
        case SEP_LBRACK:                std::cout << "SEP_LBRACK";              break;
        case SEP_LCURLY:                std::cout << "SEP_LCURLY";              break;
        case SEP_LPAREN:                std::cout << "SEP_LPAREN";              break;
        case SEP_RBRACK:                std::cout << "SEP_RBRACK";              break;
        case SEP_RCURLY:                std::cout << "SEP_RCURLY";              break;
        case SEP_RPAREN:                std::cout << "SEP_RPAREN";              break;
        case SEP_SEMI:                  std::cout << "SEP_SEMI";                break;
        case OP_ADD:                    std::cout << "OP_ADD";                  break;
        case OP_ADD_ASSIGN:             std::cout << "OP_ADD_ASSIGN";           break;
        case OP_AND:                    std::cout << "OP_AND";                  break;
        case OP_ASSIGN:                 std::cout << "OP_ASSIGN";               break;
        case OP_BIT_AND:                std::cout << "OP_BIT_AND";              break;
        case OP_BIT_AND_ASSIGN:         std::cout << "OP_BIT_AND_ASSIGN";       break;
        case OP_BIT_OR:                 std::cout << "OP_BIT_OR";               break;
        case OP_BIT_OR_ASSIGN:          std::cout << "OP_BIT_OR_ASSIGN";        break;
        case OP_BIT_SHL:                std::cout << "OP_BIT_SHL";              break;
        case OP_BIT_SHL_ASSIGN:         std::cout << "OP_BIT_SHL_ASSIGN";       break;
        case OP_BIT_NOT:                std::cout << "OP_BIT_NOT";              break;
        case OP_BIT_SHR:                std::cout << "OP_BIT_SHR";              break;
        case OP_BIT_SHR_ASSIGN:         std::cout << "OP_BIT_SHR_ASSIGN";       break;
        case OP_SUB:                    std::cout << "OP_SUB";                  break;
        case OP_SUB_ASSIGN:             std::cout << "OP_SUB_ASSIGN";           break;
        case OP_BIT_XOR:                std::cout << "OP_BIT_XOR";              break;
        case OP_BIT_XOR_ASSIGN:         std::cout << "OP_BIT_XOR_ASSIGN";       break;
        case OP_STAR:                   std::cout << "OP_STAR";                 break;
        case OP_MUL_ASSIGN:             std::cout << "OP_MUL_ASSIGN";           break;
        case OP_DIV:                    std::cout << "OP_DIV";                  break;
        case OP_DIV_ASSIGN:             std::cout << "OP_DIV_ASSIGN";           break;
        case OP_EQ:                     std::cout << "OP_EQ";                   break;
        case OP_GE:                     std::cout << "OP_GE";                   break;
        case OP_GT:                     std::cout << "OP_GT";                   break;
        case OP_LE:                     std::cout << "OP_LE";                   break;
        case OP_LT:                     std::cout << "OP_LT";                   break;
        case OP_MOD:                    std::cout << "OP_MOD";                  break;
        case OP_MOD_ASSIGN:             std::cout << "OP_MOD_ASSIGN";           break;
        case KW_BREAK:                  std::cout << "KW_BREAK";                break;
        case KW_CASE:                   std::cout << "KW_CASE";                 break;
        case KW_CONTINUE:               std::cout << "KW_CONTINUE";             break;
        case KW_DEFAULT:                std::cout << "KW_DEFAULT";              break;
        case KW_ELIF:                   std::cout << "KW_ELIF";                 break;
        case KW_IF:                     std::cout << "KW_IF";                   break;
        case KW_ELSE:                   std::cout << "KW_ELSE";                 break;
        case KW_SWITCH:                 std::cout << "KW_SWITCH";               break;
        case KW_FOR:                    std::cout << "KW_FOR";                  break;
        case KW_WHILE:                  std::cout << "KW_WHILE";                break;
        case KW_DO:                     std::cout << "KW_DO";                   break;
        case KW_INLINE:                 std::cout << "KW_INLINE";               break;
        case KW_TYPEDEF:                std::cout << "KW_TYPEDEF";              break;
        case KW_GOTO:                   std::cout << "KW_GOTO";                 break;
        case KW_RETURN:                 std::cout << "KW_RETURN";               break;
        case PP_DEFINE:                 std::cout << "PP_DEFINE";               break;
        case PP_ELIF:                   std::cout << "PP_ELIF";                 break;
        case PP_ELSE:                   std::cout << "PP_ELSE";                 break;
        case PP_IFDEF:                  std::cout << "PP_IFDEF";                break;
        case PP_IFNDEF:                 std::cout << "PP_IFNDEF";               break;
        case PP_INCLUDE:                std::cout << "PP_INCLUDE";              break;
        default:                        std::cout << "undefined";               break;
        }
        std::cout << "," << t->line() << "," << t->column() << ">" << std::endl;
}


}