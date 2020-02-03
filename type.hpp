#ifndef HZCC_TYPE_HPP
#define HZCC_TYPE_HPP


#include "dsa/dsa_vec.hpp"

namespace hzcc {

enum {
	CHAR, UCHAR, SHORT, USHORT, INT, UINT, LONG, ULONG, LONGLONG, ULONGLONG, ENUM,
	FLOAT, DOUBLE, LONGDOUBLE, POINTER, VOID, UNION, STRUCT, ARRAY, FUNCTION
};

/* I1 : signed int8	1byte=8bit;  U1: unsigned int8
 * V: no type              B: memory block,
 * see TypeCode()
 * */
enum {
	I1, U1, I2, U2, I4, U4, F4, F8, V, B
};

enum {
	CONST = 0x1, VOLATILE = 0x2
};

/* class type == 24byte
 * so class type doesn't have padding
 * _kind, _qualifier, _align, _size == 4byte * 4
 * *_next == 8byte
 * */
class type {
public:
	int kind               : 8;
	int qualifier          : 8;
	int align              : 16;
	int size;
	class type *next;

public:
	type(int ki, int qual, int al, int sz, class type *n)
		: kind(ki), qualifier(qual), align(al), size(sz), next(n)
	{}


};

/* class t_array == 32byte, padding == 4byte
 * _len == 4byte, type + t_array == 4 + 24 == 28byte
 * */
class t_array : public type {
public:
	int len;

public:
	t_array(int le, int kind, int qualifier, int align
		, int size, class type *next)
		: type(kind, qualifier, align, size, next), len(le)
	{}
};


/* field == 36byte, padding == 4byte
 * *_next_field == *_next_type == *id = 8byte
 * _offset == _bits == _pos = 4byte
 * the field member of a struct or union
 * offset:	offset to the beginning of struct/union
 * id:	filed name
 * bits: bits of a bit filed; // int align:16;
 *       for non-bit files, bits is 0. //int size;
 * pos:  see EndRecord() funcion: fld->pos = LITTLE_ENDIAN ? bits : intBits - bits;
 * ty:	 field type
 * next: pointer to next field
 * */
class field {
public:
        class field	*next_field;
        class type	*next_type;
        char 		*id;
	int 		offset;
	int		bits;
	int		pos;

public:
        field(int off, int bi, int po
                , char *i, class field *nf, class type *nt)
                : offset(off), bits(bi), pos(po)
                , id(i), next_field(nf), next_type(nt)
        {}
};

/* t_record == 24byte(type) + 36byte(just t_record) == 60byte, padding == 4byte
 * *_id: struct/union name, for anonymous struct/union, id == nullptr
 * *_fields: all the fields of struct/union
 * **tail: used for construction of field list
 * _has_const_field: contains constant field or not
 * _has_flex_array: contains flexible array(array with size 0) or not.
 *                      the flexible array must be last field
 * */
class t_record : public type {
public:
        char            *id;
        class field     *fields;
        class field     **tail;
        int             has_const_field : 16;
        int             has_flex_array  : 16;
        int             complete;

public:
        t_record(char *i, class field *fi, class field **ta
                , int hcf, int hfa, int com
                , int ki, int qual, int al, int sz, class type *n)
                : id(i), fields(fi), tail(ta), has_const_field(hcf)
                , has_flex_array(hfa), complete(com)
                , type(ki, qual, al, sz, n)
        {}
};


class t_enum : public type {
public:
        char            *_id;
        int             complete;
};

/* class t_parameter == 36byte, padding == 4byte
 * describes the parameter information in
 * function declaration or definition.
 * id:	parameter name ,can be nullptr.
 * ty:	parameter type
 * reg:	qualified by register or not
 * */
class t_parameter : public type {
public:
        char            *id;
        int             reg;

public:
        t_parameter(char *i, int re
                , int ki, int qual, int al, int sz, class type *n)
                        : id(i), reg(re)
                        , type(ki, qual, al, sz, n)
        {}
};

/* The meaning of hasProto: 	see K&R	 A.10.1
 * (1)
 * new-style definition:
 *              int max(int a,int b,int c){}
 * old-style definiition:
 *              see K&R A.8.6.3
 *              In the old-style declarator, the identifier list must be absent unless
 *              the declarator is used in the head of a function defition.
 *              No information about the types of the parameters is supplied by the declaration
 *              T D1(id-list);
 *              int max(a,b,c)	// This is a special old-style function declaration, because it appears in definition.
 *              int a,b,c;
 *              {
 *              }
 * (2)
 * no proto:  we only know function returns int. It could be used as max(2,3), max(2,3,4)  in fact.
 * has proto:	max(2,3,4) is right, max(2,3) wrong.
 * (3)
 * hasProto: has function prototype or not.
 * hasEllipse: has variable argument or not
 * params:  parameter set
 * */
class signature {
        int has_proto           :  16;
        int has_ellipsis        :  16;
        dsa_vec<void*>          params;
};


class t_function : public type {
public:
        signature *sig;

public:
        t_function(signature *s
                , int ki, int qual, int al, int sz, class type *n)
                        : sig(s), type(ki, qual, al, sz, n)
        {}
};


}

#endif //HZCC_TYPE_HPP
