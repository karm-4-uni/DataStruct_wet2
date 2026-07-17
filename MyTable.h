#ifndef MYTABLE_H
#define MYTABLE_H

#include <memory>
#include <stdexcept>

template <typename T>
class My_Table {
private:
    std::shared_ptr<T> first;
    std::shared_ptr<T> second;

public:
    My_Table(
        std::shared_ptr<T> first = nullptr,
        std::shared_ptr<T> second = nullptr
    ) : first(first), second(second) {}

    // Allows modification: table[0] = ...
    std::shared_ptr<T>& operator[](int index) {
        if (index == 0) {
            return first;
        }

        if (index == 1) {
            return second;
        }

        throw std::out_of_range("no no table");
    }

    // Allows access to a const My_Table
    const std::shared_ptr<T>& operator[](int index) const {
        if (index == 0) {
            return first;
        }

        if (index == 1) {
            return second;
        }

        throw std::out_of_range("My_Table index must be 0 or 1");
    }

    // void setFirst(std::shared_ptr<T> value) {
    //     first = value;
    // }
    //
    // void setSecond(std::shared_ptr<T> value) {
    //     second = value;
    // }
// no need here because it keys
    std::shared_ptr<T> getFirst() const {
        return first;
    }

    std::shared_ptr<T> getSecond() const {
        return second;
    }
};

#endif // MYTABLE_H