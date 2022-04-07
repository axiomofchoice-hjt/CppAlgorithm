#ifndef AXIOMOFCHOICE_BASEINTERFACE_H
#define AXIOMOFCHOICE_BASEINTERFACE_H

template <class Type, class Derive>
class Clone {
   public:
    Derive clone() const { return Derive((static_cast<const Derive &>(*this))); }
};

template <class Type, class Derive>
class Display {
   public:
    friend std::ostream &operator<<(std::ostream &cout, const Derive &v) {
        std::cout << v.value();
        return cout;
    }
};

template <class Type, class Derive>
class Ord {
   public:
    friend bool operator<(const Derive &a, const Derive &b) {
        return a.value() < b.value();
    }
    friend bool operator>(const Derive &a, const Derive &b) {
        return a.value() > b.value();
    }
    friend bool operator<=(const Derive &a, const Derive &b) {
        return a.value() <= b.value();
    }
    friend bool operator>=(const Derive &a, const Derive &b) {
        return a.value() >= b.value();
    }
    friend bool operator==(const Derive &a, const Derive &b) {
        return a.value() == b.value();
    }
    friend bool operator!=(const Derive &a, const Derive &b) {
        return a.value() != b.value();
    }
};
#define UnaryOpt(Name, Opt)                                                   \
    template <class Type, class Derive>                                       \
    class Name {                                                              \
       public:                                                                \
        friend Derive operator Opt(const Derive &a) { return Opt a.value(); } \
    };
#define BinaryOpt(Name, Opt)                                           \
    template <class Type, class Derive>                                \
    class Name {                                                       \
       public:                                                         \
        friend Derive operator Opt(const Derive &a, const Derive &b) { \
            return a.value() Opt b.value();                            \
        }                                                              \
    };
#define BinaryOptAssign(Name, Opt)                                \
    template <class Type, class Derive>                           \
    class Name {                                                  \
       public:                                                    \
        friend Derive &operator Opt(Derive &a, const Derive &b) { \
            a.value() Opt b.value();                              \
            return a;                                             \
        }                                                         \
    };

UnaryOpt(Pos, +);
UnaryOpt(Neg, -);

BinaryOpt(Add, +);
BinaryOpt(Sub, -);
BinaryOpt(Mul, *);
BinaryOpt(Div, /);
BinaryOpt(Mod, %);
BinaryOptAssign(AddAssign, +=);
BinaryOptAssign(SubAssign, -=);
BinaryOptAssign(MulAssign, *=);
BinaryOptAssign(DivAssign, /=);
BinaryOptAssign(ModAssign, %=);

UnaryOpt(BitRev, ~);
BinaryOpt(BitAnd, &);
BinaryOpt(BitOr, |);
BinaryOpt(BitXor, ^);
BinaryOptAssign(BitAndAssign, &=);
BinaryOptAssign(BitOrAssign, |=);
BinaryOptAssign(BitXorAssign, ^=);

#endif
