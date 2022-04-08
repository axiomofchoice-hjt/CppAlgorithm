#ifndef ITER_H
#define ITER_H

#include <functional>
#include <optional>
#include <utility>

#include "BaseType.h"

template <class Iter>
class Iterable {
   private:
    Iter iter;

   public:
    class RangeForIter {
       private:
        Iter iter;

       public:
        using result_type = typename Iter::result_type;

        RangeForIter(Iter iter) : iter(iter) {}

        void operator++() { iter.next(); }

        template <class T>
        bool operator!=(const T &other) {
            Iter temp = iter;
            return temp.next().has_value();
        }

        result_type operator*() {
            Iter temp = iter;
            return temp.next().value();
        }
    };

    Iterable(Iter iter) : iter(iter) {}

    RangeForIter begin() const { return RangeForIter(iter); }

    void *end() const { return nullptr; }
};

template <class IterA, class IterB>
class ConcatIter {
   private:
    IterA iterA;
    IterB iterB;

   public:
    using result_type = typename IterA::result_type;

    ConcatIter(IterA iterA, IterB iterB) : iterA(iterA), iterB(iterB) {}

    std::optional<result_type> next() {
        std::optional<result_type> result = iterA.next();
        if (!result.has_value()) {
            result = iterB.next();
        }
        return result;
    }
};

template <class IterA, class IterB>
class ZipIter {
   private:
    IterA iterA;
    IterB iterB;

   public:
    using first_type = typename IterA::result_type;
    using second_type = typename IterB::result_type;
    using result_type = std::pair<first_type, second_type>;

    ZipIter(IterA iterA, IterB iterB) : iterA(iterA), iterB(iterB) {}

    std::optional<result_type> next() {
        std::optional<first_type> resultA = iterA.next();
        if (!resultA.has_value()) {
            return std::nullopt;
        }
        std::optional<second_type> resultB = iterB.next();
        if (!resultB.has_value()) {
            return std::nullopt;
        }
        return std::make_optional<result_type>(resultA.value(),
                                               resultB.value());
    }
};

template <class Iter, class Fn>
class MapIter {
   public:
    using argument_type = typename Iter::result_type;
    using result_type = typename Fn::result_type;

   private:
    Iter iter;
    Fn func;

   public:
    MapIter(Iter iter, const Fn &func) : iter(iter), func(func) {}

    std::optional<result_type> next() {
        std::optional<argument_type> argument = iter.next();
        if (!argument.has_value()) {
            return std::nullopt;
        }
        return func(argument.value());
    }
};

template <class Iter, class Fn>
class FilterIter {
   public:
    using result_type = typename Iter::result_type;

   private:
    Iter iter;
    Fn func;

   public:
    FilterIter(Iter iter, const Fn &func) : iter(iter), func(func) {}

    std::optional<result_type> next() {
        while (1) {
            std::optional<result_type> result = iter.next();
            if (!result.has_value()) {
                return std::nullopt;
            } else if (func(result.value())) {
                return result;
            }
        }
    }
};

template <class Iter>
class EnumerateIter {
   public:
    using first_type = usize;
    using second_type = typename Iter::result_type;
    using result_type = std::pair<first_type, second_type>;

   private:
    Iter iter;
    usize counter;

   public:
    EnumerateIter(Iter iter) : iter(iter), counter(0) {}

    std::optional<result_type> next() {
        std::optional<second_type> second = iter.next();
        if (!second.has_value()) {
            return std::nullopt;
        }
        usize first = counter;
        counter++;
        return std::make_pair(first, second.value());
    }
};

template <class Iter>
class StepByIter {
   public:
    using result_type = typename Iter::result_type;

   private:
    Iter iter;
    usize step;

   public:
    StepByIter(Iter iter, usize step) : iter(iter), step(step - 1) {}

    std::optional<result_type> next() {
        std::optional<result_type> result = iter.next();
        if (!result.has_value()) {
            return std::nullopt;
        }
        for (usize i = 0; i < step; i++) {
            if (!iter.next().has_value()) {
                break;
            }
        }
        return result;
    }
};

template <class Iter>
class TakeIter {
   public:
    using result_type = typename Iter::result_type;

   private:
    Iter iter;
    usize counter;

   public:
    TakeIter(Iter iter, usize counter) : iter(iter), counter(counter) {}

    std::optional<result_type> next() {
        std::optional<result_type> result;
        if (counter != 0) {
            result = iter.next();
            counter--;
        }
        return result;
    }
};

template <class Iter>
class RangeIter {
   private:
    Iter _pointer;
    Iter _end;

   public:
    using result_type = Iter;

    RangeIter(Iter _pointer, Iter _end) : _pointer(_pointer), _end(_end) {}

    std::optional<result_type> next() {
        if (_pointer == _end) {
            return std::nullopt;
        } else {
            result_type result = _pointer;
            ++_pointer;
            return std::make_optional<result_type>(result);
        }
    }
};

template <class Iter>
class IterFromSTLIterator {
   private:
    Iter _pointer;
    Iter _end;

   public:
    using result_type = typename Iter::pointer;

    IterFromSTLIterator(Iter _pointer, Iter _end)
        : _pointer(_pointer), _end(_end) {}

    std::optional<result_type> next() {
        if (_pointer == _end) {
            return std::nullopt;
        } else {
            result_type result = &*_pointer;
            ++_pointer;
            return std::make_optional<result_type>(result);
        }
    }
};

#endif
