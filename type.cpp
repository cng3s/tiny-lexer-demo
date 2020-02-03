#include "type.hpp"

namespace hzcc {

#define T(categ) (Types + categ)

#define IsIntegType(ty)    (ty->categ <= ENUM)
#define IsUnsigned(ty)	   (ty->categ & 0x1)
// Here, real-type means floating number.
#define IsRealType(ty)	   (ty->categ >= FLOAT && ty->categ <= LONGDOUBLE)
#define IsArithType(ty)    (ty->categ <= LONGDOUBLE)
// Scalar type is different from 'vector type' such as  struct
#define IsScalarType(ty)   (ty->categ <= POINTER)
#define IsPtrType(ty)      (ty->categ == POINTER)
#define IsRecordType(ty)   (ty->categ == STRUCT || ty->categ == UNION)
#define IsFunctionType(ty) (ty->categ == FUNCTION)

// allow pointers to object of zero size
#define IsObjectPtr(ty)     (ty->categ == POINTER &&  ty->bty->categ != FUNCTION)

#define IsIncompletePtr(ty) (ty->categ == POINTER && ty->bty->size == 0)
#define IsVoidPtr(ty)       (ty->categ == POINTER && ty->bty->categ == VOID)
#define NotFunctionPtr(ty)  (ty->categ == POINTER && ty->bty->categ != FUNCTION)

#define BothIntegType(ty1, ty2)   (IsIntegType(ty1) && IsIntegType(ty2))
#define BothArithType(ty1, ty2)   (IsArithType(ty1) && IsArithType(ty2))
#define BothScalarType(ty1, ty2)  (IsScalarType(ty1) && IsScalarType(ty2))
#define IsCompatiblePtr(ty1, ty2) (IsPtrType(ty1) && IsPtrType(ty2) &&  \
                                   IsCompatibleType(Unqual(ty1->bty), Unqual(ty2->bty)))

}