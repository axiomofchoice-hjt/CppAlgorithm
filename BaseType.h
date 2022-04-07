#ifndef AXIOMOFCHOICE_BASETYPE_H
#define AXIOMOFCHOICE_BASETYPE_H

#include <stdint.h>

#include <iostream>

#include "BaseInterface.h"

template <class Type>
class Integer : public Clone<Type, Integer<Type>>,
                public Display<Type, Integer<Type>>,
                public Ord<Type, Integer<Type>>,
                public Pos<Type, Integer<Type>>,
                public Neg<Type, Integer<Type>>,
                public Add<Type, Integer<Type>>,
                public Sub<Type, Integer<Type>>,
                public Mul<Type, Integer<Type>>,
                public Div<Type, Integer<Type>>,
                public Mod<Type, Integer<Type>>,
                public AddAssign<Type, Integer<Type>>,
                public SubAssign<Type, Integer<Type>>,
                public MulAssign<Type, Integer<Type>>,
                public DivAssign<Type, Integer<Type>>,
                public ModAssign<Type, Integer<Type>>,
                public BitRev<Type, Integer<Type>>,
                public BitAnd<Type, Integer<Type>>,
                public BitOr<Type, Integer<Type>>,
                public BitXor<Type, Integer<Type>>,
                public BitAndAssign<Type, Integer<Type>>,
                public BitOrAssign<Type, Integer<Type>>,
                public BitXorAssign<Type, Integer<Type>> {
   private:
    Type _value;

   public:
    Type value() const { return _value; }
    Type &value() { return _value; }
    using value_type = Type;
    Integer() : _value() {}
    Integer(Type _value) : _value(_value) {}
    Integer(const Integer<Type> &other) : _value(other.value()) {}
};

template <class Type>
class Float : public Clone<Type, Float<Type>>,
              public Display<Type, Float<Type>>,
              public Ord<Type, Float<Type>>,
              public Pos<Type, Float<Type>>,
              public Neg<Type, Float<Type>>,
              public Add<Type, Float<Type>>,
              public Sub<Type, Float<Type>>,
              public Mul<Type, Float<Type>>,
              public Div<Type, Float<Type>>,
              public AddAssign<Type, Float<Type>>,
              public SubAssign<Type, Float<Type>>,
              public MulAssign<Type, Float<Type>>,
              public DivAssign<Type, Float<Type>> {
   private:
    Type _value;

   public:
    Type value() const { return _value; }
    Type &value() { return _value; }
    using value_type = Type;
    Float() : _value() {}
    Float(Type _value) : _value(_value) {}
    Float(const Float<Type> &other) : _value(other.value()) {}
};

using i8 = Integer<int8_t>;
using i16 = Integer<int16_t>;
using i32 = Integer<int32_t>;
using i64 = Integer<int64_t>;
using u8 = Integer<uint8_t>;
using u16 = Integer<uint16_t>;
using u32 = Integer<uint32_t>;
using u64 = Integer<uint64_t>;

using f32 = Float<float>;
using f64 = Float<double>;

#endif
