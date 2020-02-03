#include "scanner.hpp"


namespace hzcc {

scanner::scanner(std::string &filename)
        : _line(1), _column(1), _file(filename)
{
        fileReader(_file);
        run();
}

scanner::~scanner() = default;

void scanner::run()
{
        while (true) {
                tok *tok = next_token();
                print_tok(tok);
                if (tok->tag() == TAG_EOF)
                        break;
        }
}


void scanner::fileReader(std::string &filename)
{
        assert(is_file_correct());
        std::ifstream in(filename, std::ios::in);
        assert(in.is_open());
        std::ostringstream ss;
        ss << in.rdbuf();
        _data = ss.str();
        in.close();
        _size = _data.length();
}

inline unsigned int scanner::line() const
{
        return _line;
}

inline unsigned int scanner::column() const
{
        return _column;
}

bool scanner::is_file_correct() const
{
        size_t i;
        for (i = _file.length(); i >= 0; i--) {
                if (_file[i] == '.')
                        break;
        }
        i++;
        if (_file[i] == 'c' || _file[i] == 'h') {
                i++;
                return _file[i] == '\0';
        }
        return false;
}

void scanner::skip_ignore_block()
{
        size_t len = _data.length();
        for (size_t i = _pos; i < len; i++) {
                if (is_white_space(_data[_pos])) {
                        eat(1);
                } else if (is_new_line_char(_data[_pos])) {
                        change_line();
                }
                else if (match("//")) {
                        eat(2);
                        skip_short_comment();
                }
                else if (match("/*")) {
                        eat(2);
                        skip_long_comment();
                }
                else if (match("\r\n") || match("\n\r")) {
                        eat(2);
                        change_line();
                }
                else {
                        break;
                }
        }
}

bool scanner::is_white_space(char c)
{
        return c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ';
}

bool scanner::is_new_line_char(char c) const
{
        return c == '\r' || c == '\n';
}

bool scanner::match(std::string str) const
{
        if (str.length() + _pos >= _size)
                return false;
        return str == _data.substr(_pos, str.length());
}

void scanner::eat(unsigned long skipNum)
{
        _pos += skipNum;
        _column += skipNum;
}

void scanner::skip_short_comment()
{
        for (; ; ++_pos) {
                if (is_end()) {
                        return;
                } else if (is_new_line_char(_data[_pos])) {
                        change_line();
                        return;
                } else {
                        eat(1);
                }
        }
}

void scanner::skip_long_comment()
{
        for (;; _pos++) {
                if (is_end()) {
                        panic("find /* but can't match */");
                        return;
                } else if (_data[_pos] == '*' && match("*/")) {
                        eat(2);
                        return;
                } else if (is_new_line_char(_data[_pos])) {
                        change_line();
                } else {
                        eat(1);
                }
        }
}

bool scanner::is_end()
{
        return 0 == _size || _data[_pos] == '\0';
}


double scanner::scan_num()
{
        double val = _data[_pos] - '0';
        eat(1);
        while (isdigit(_data[_pos])) {
                val = 10 * val + (_data[_pos] - '0');
                eat(1);
        }
        if (_data[_pos] == '.') {
                double exp = 0.1;
                eat(1);
                while (isdigit(_data[_pos])) {
                        val = val + exp * (_data[_pos] - '0');
                        exp *= 0.1;
                        eat(1);
                }
        }
        return val;
}

bool scanner::is_arith_op(char c) const
{
        return c=='+' || c=='-' || c=='*' || c=='/' || c=='%' || c=='&' || c=='|' || c=='^';
}

std::string scanner::scan_id()
{
        std::string ret;
        if (!isalpha(_data[_pos]) && _data[_pos] != '_')
                panic("scan_id() error, first character must be alpha or _");
        for (ret += _data[_pos++], _column++; isalnum(_data[_pos]) || _data[_pos] == '_'; _pos++, _column++)
                ret += _data[_pos];
        return ret;
}

std::string scanner::scan_string()
{
        std::string ret;
        for (; _data[_pos] != '"'; _pos++, _column++) {
                if (_data[_pos] == '\\')
                        escape(ret);
                else if (_data[_pos] == EOF)
                        break;
                else
                        ret += _data[_pos];
        }
        eat(1); // eat '"'
        return ret;
}

void scanner::escape(std::string &str)
{
        eat(1); // eat '\'
        switch (_data[_pos]) {
        case 'a':
        case 'b':
        case 'f':
        case 'v':
        case 'r':
        case 'n':
        case 't':
        case '0': str = str + "\\" + _data[_pos]; eat(1); break;
        case '"':
        case '\\':
        case '\'':
        case '?': str += _data[_pos]; eat(1); break;
        default: break;
        }
}

void scanner::panic(const std::string &err) const
{
        throw std::invalid_argument(err);
}



void scanner::change_line()
{
        _line += 1;
        _column = 1;
        _pos++;
}

tok* scanner::next_token()
{
        skip_ignore_block();
        if (is_end())
                return new tok(TAG_EOF, _line, _column);
        auto retCol = _column;
        switch (_data[_pos]) {
        case ';':
                eat(1);
                return new tok(SEP_SEMI, _line, retCol);
        case ',':
                eat(1);
                return new tok(SEP_COMMA, _line, retCol);
        case '(':
                eat(1);
                return new tok(SEP_LPAREN, _line, retCol);
        case ')':
                eat(1);
                return new tok(SEP_RPAREN, _line, retCol);
        case '[':
                eat(1);
                return new tok(SEP_LBRACK, _line, retCol);
        case ']':
                eat(1);
                return new tok(SEP_RBRACK, _line, retCol);
        case '{':
                eat(1);
                return new tok(SEP_LCURLY, _line, retCol);
        case '}':
                eat(1);
                return new tok(SEP_RCURLY, _line, retCol);
        case ':':
                eat(1);
                return new tok(SEP_COLON, _line, retCol);
        case '.':
                eat(1);
                return new tok(SEP_DOT, _line, retCol);
        case '+':
                eat(1);
                if (match("=")) {
                        eat(1);
                        return new tok(OP_ADD_ASSIGN, _line, retCol);
                } else if (match("+")) {
                        eat(1);
                        return new tok(OP_UNP, _line, retCol);
                } else {
                        return new tok(OP_ADD, _line, retCol);
                }
        case '-':
                eat(1);
                if (match("=")) {
                        eat(1);
                        return new tok(OP_SUB_ASSIGN, _line, retCol);
                } else if (match("-")) {
                        return new tok(OP_UNM, _line, retCol);
                } else if (match(">")) {
                        return new tok(OP_PTR_2_MEMBER, _line, retCol);
                } else {
                        return new tok(OP_SUB, _line, retCol);
                }
        case '*':
                eat(1);
                if (match("=")) {
                        eat(1);
                        return new tok(OP_MUL_ASSIGN, _line, retCol);
                } else {
                        return new tok(OP_STAR, _line, retCol);
                }
        case '/':
                eat(1);
                if (match("=")) {
                        return new tok(OP_DIV_ASSIGN, _line, retCol);
                } else {
                        return new tok(OP_DIV, _line, retCol);
                }
        case '%':
                eat(1);
                if (match("=")) {
                        return new tok(OP_MOD_ASSIGN, _line, retCol);
                } else {
                        return new tok(OP_MOD, _line, retCol);
                }
        case '=':
                eat(1);
                if (match("=")) {
                        eat(1);
                        return new tok(OP_EQ, _line, retCol);
                } else {
                        return new tok(OP_ASSIGN, _line, retCol);
                }
        case '&':
                eat(1);
                if (match("&")) {
                        eat(1);
                        return new tok(OP_AND, _line, retCol);
                } else if (match("=")) {
                        eat(1);
                        return new tok(OP_BIT_AND_ASSIGN, _line, retCol);
                } else {
                        return new tok(OP_BIT_AND, _line, retCol);
                }
        case '|':
                eat(1);
                if (match("|")) {
                        eat(1);
                        return new tok(OP_OR, _line, retCol);
                } else if (match("=")) {
                        eat(1);
                        return new tok(OP_BIT_OR_ASSIGN, _line, retCol);
                } else {
                        return new tok(OP_BIT_OR, _line, retCol);
                }
        case '!':
                eat(1);
                if (match("=")) {
                        eat(1);
                        return new tok(OP_NE, _line, retCol);
                } else {
                        return new tok(OP_NOT, _line, retCol);
                }
        case '<':
                eat(1);
                if (match("<=")) {
                        eat(2);
                        return new tok(OP_BIT_SHL_ASSIGN, _line, retCol);
                } else if (match("=")) {
                        eat(1);
                        return new tok(OP_LE, _line, retCol);
                } else if (match("<")) {
                        eat(1);
                        return new tok(OP_BIT_SHL, _line, retCol);
                } else {
                        return new tok(OP_LT, _line, retCol);
                }
        case '>':
                eat(1);
                if (match(">=")) {
                        eat(2);
                        return new tok(OP_BIT_SHR_ASSIGN, _line, retCol);
                } else if (match("=")) {
                        eat(1);
                        return new tok(OP_GE, _line, retCol);
                } else if (match(">")) {
                        eat(1);
                        return new tok(OP_BIT_SHR, _line, retCol);
                } else {
                        return new tok(OP_GT, _line, retCol);
                }
        case '^':
                eat(1);
                if (match("=")) {
                        eat(1);
                        return new tok(OP_BIT_XOR_ASSIGN, _line, retCol);
                } else {
                        return new tok(OP_BIT_XOR, _line, retCol);
                }
        case '~':
                eat(1);
                return new tok(OP_BIT_NOT, _line, retCol);
        case '\'':
                // type char maybe wrong..
                eat(3);
                return new t_num(_data[_pos - 2], _line, retCol);
        case '"':
                eat(1);
                return new t_string(scan_string(), _line, retCol);
        case 'i':
                if (match("int")) {
                        eat(3);
                        return new tok(T_INT, _line, retCol);
                }
        case 'f':
                if (match("float")) {
                        eat(5);
                        return new tok(T_FLOAT, _line, retCol);
                }
        case 'd':
                if (match("double")) {
                        eat(6);
                        return new tok(T_DOUBLE, _line, retCol);
                }
        case 'c':
                if (match("char")) {
                        eat(4);
                        return new tok(T_CHAR, _line, retCol);
                } else if (match("const")) {
                        eat(5);
                        return new tok(T_SPECIFIER_CONST, _line, retCol);
                }
        case 'e':
                if (match("enum")) {
                        eat(4);
                        return new tok(T_ENUM, _line, retCol);
                }
        case 'v':
                if (match("void")) {
                        eat(4);
                        return new tok(T_VOID, _line, retCol);
                } else if (match("volatile")) {
                        eat(8);
                        return new tok(T_SPECIFIER_VOLATILE, _line, retCol);
                }
        case 'u':
                if (match("union")) {
                        eat(5);
                        return new tok(T_UNION, _line, retCol);
                }
        case 's':
                if (match("static")) {
                        eat(6);
                        return new tok(T_SPECIFIER_STATIC, _line, retCol);
                }
        default: break;
        }
        if (isdigit(_data[_pos])) {
                double val = (_data[_pos] - '0');
                eat(1);
                while (isdigit(_data[_pos])) {
                        val = val * 10 + (_data[_pos] - '0');
                        eat(1);
                }
                if (_data[_pos] == '.') {
                        eat(1);
                        double exp = 0.1;
                        while (isdigit(_data[_pos])) {
                                val = val + (_data[_pos] - '0') * exp;
                                exp *= 0.1;
                                eat(1);
                        }
                }
                return new t_num(val, _line, retCol);
        }
        std::string id = scan_id();
        return new t_id(id, _line, retCol);
}

}
