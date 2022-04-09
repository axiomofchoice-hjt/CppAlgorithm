#ifndef YETANOTHERBIGINTEGER_H
#define YETANOTHERBIGINTEGER_H

#include <stdint.h>

#include <functional>
#include <iostream>
#include <utility>

using std::cout;
using std::endl;

template <class Type>
class YABigInt {
   private:
    Type high, low;

   public:
    YABigInt() : high(), low() {}

    YABigInt(Type low) : high(), low(low) {}

    YABigInt(Type high, Type low) : high(high), low(low) {}

    std::pair<YABigInt<Type>, YABigInt<Type>> operator+(
        const YABigInt<Type> &other) const {
        auto [h0, l] = low + other.low;
        auto [x1, h1] = h0 + high;
        auto [x2, h] = h1 + other.high;
        auto [_, x] = x1 + x2;
        return std::make_pair(YABigInt(x), YABigInt(h, l));
    }

    std::pair<YABigInt<Type>, YABigInt<Type>> operator*(
        const YABigInt<Type> &other) const {
        auto [h0, l] = low * other.low;
        auto [xl1, h1] = low * other.high;
        auto [xl2, h2] = high * other.low;
        auto [xh3, xl3] = high * other.high;

        auto [xl4, h4] = h0 + h1;
        auto [xl5, h] = h4 + h2;

        auto [xh6, xl6] = xl1 + xl2;
        auto [xh7, xl7] = xl6 + xl3;
        auto [xh8, xl8] = xl7 + xl4;
        auto [xh9, xl] = xl8 + xl5;

        auto [_10, xh10] = xh3 + xh6;
        auto [_11, xh11] = xh10 + xh7;
        auto [_12, xh12] = xh11 + xh8;
        auto [_13, xh] = xh12 + xh9;

        return std::make_pair(YABigInt(xh, xl), YABigInt(h, l));
    }

    bool operator==(const YABigInt<Type> &other) const {
        return high == other.high && low == other.low;
    }

    void printHex() const {
        high.printHex();
        low.printHex();
    }

    friend std::ostream &operator<<(std::ostream &cout,
                                    const YABigInt<Type> &self) {
        self.printHex();
        return cout;
    }
};

void putHexChar(uint32_t num) {
    if (num < 10) {
        cout << char(num + '0');
    } else {
        cout << char(num - 10 + 'a');
    }
}

class YAInt32 {
   private:
    uint32_t value;

   public:
    YAInt32() : value() {}

    YAInt32(uint32_t value) : value(value) {}

    std::pair<YAInt32, YAInt32> operator+(const YAInt32 &other) const {
        uint64_t result = static_cast<uint64_t>(value) + other.value;
        return std::make_pair(YAInt32(result >> 32), YAInt32(result));
    }
    
    std::pair<YAInt32, YAInt32> operator*(const YAInt32 &other) const {
        uint64_t result = static_cast<uint64_t>(value) * other.value;
        return std::make_pair(YAInt32(result >> 32), YAInt32(result));
    }

    bool operator==(const YAInt32 &other) const { return value == other.value; }

    void printHex() const {
        putHexChar(value >> 28 & 0xf);
        putHexChar(value >> 24 & 0xf);
        putHexChar(value >> 20 & 0xf);
        putHexChar(value >> 16 & 0xf);
        putHexChar(value >> 12 & 0xf);
        putHexChar(value >> 8 & 0xf);
        putHexChar(value >> 4 & 0xf);
        putHexChar(value & 0xf);
    }

    friend std::ostream &operator<<(std::ostream &cout, const YAInt32 &self) {
        self.printHex();
        return cout;
    }
};

#endif
