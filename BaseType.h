#include <stdint.h>

#include <iostream>

template <class Type>
class BaseType {
   private:
    Type _value;

   public:
    using value_type = Type;
    BaseType() : _value() {}
    BaseType(Type _value) : _value(_value) {}

    BaseType<Type> clone() { return _value; }

    explicit operator Type() { return _value; }
};

template <class Type>
class OrdType : public BaseType<Type> {
   public:
    bool operator<(const OrdType<Type> &other) const {
        return BaseType<Type>::_value < other._value;
    }
    bool operator>(const OrdType<Type> &other) const {
        return BaseType<Type>::_value > other._value;
    }
    bool operator<=(const OrdType<Type> &other) const {
        return BaseType<Type>::_value <= other._value;
    }
    bool operator>=(const OrdType<Type> &other) const {
        return BaseType<Type>::_value >= other._value;
    }
    bool operator==(const OrdType<Type> &other) const {
        return BaseType<Type>::_value == other._value;
    }
    bool operator!=(const OrdType<Type> &other) const {
        return BaseType<Type>::_value != other._value;
    }
};

template <class Type>
class Integer : public BaseType<Type>, public OrdType<Type> {
   public:
    using value_type = Type;
    Integer() : BaseType<Type>() {}
    Integer(Type _value) : BaseType<Type>(_value) {}

    Integer<Type> operator+(const Integer<Type> &other) const {
        return BaseType<Type>::_value + other._value;
    }
    Integer<Type> operator-(const Integer<Type> &other) const {
        return BaseType<Type>::_value - other._value;
    }
    Integer<Type> operator*(const Integer<Type> &other) const {
        return BaseType<Type>::_value * other._value;
    }

    friend std::ostream &operator<<(std::ostream &cout,
                                    const Integer<Type> &v) {
        // cout << (void *)v._pointer << "/" << v._size << "/" << v._capacity;
        std::cout << v._value;
        return cout;
    }
};
using i8 = Integer<int8_t>;
using i16 = Integer<int16_t>;
using i32 = Integer<int32_t>;
using i64 = Integer<int64_t>;
using u8 = Integer<uint8_t>;
using u16 = Integer<uint16_t>;
using u32 = Integer<uint32_t>;
using u64 = Integer<uint64_t>;
