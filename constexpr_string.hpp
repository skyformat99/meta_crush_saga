//
// Created by jguegant on 2017-06-08.
//

#ifndef META_CRUSH_SAGA_CONSTEXPR_STRING_HPP
#define META_CRUSH_SAGA_CONSTEXPR_STRING_HPP

#include <array>

#include "utils.hpp"

template <std::size_t N>
class constexpr_string
{
public:
    using iterator = char*;

    constexpr constexpr_string(const char(&a)[N]): data_{}, size_(N - 1)
    {
        for (std::size_t i = 0; i < N; ++i) {
            data_[i] = a[i];
        }
    }

    constexpr constexpr_string(const char* a, int size): data_{}, size_(size)
    {
        for (std::size_t i = 0; i < N && i < size; ++i) {
            data_[i] = a[i];
        }
    }

    constexpr char operator[](std::size_t n) const
    {
        return n < size_? data_[n] : throw std::out_of_range("");
    }

    constexpr std::size_t size() const
    {
        return size_;
    }

    template <std::size_t M>
    constexpr bool startswith(const constexpr_string<M>& other)
    {
        int i = 0;

        for (; i < other.size() && i < size(); ++i) {
            if (data_[i] != other[i]) {
                return false;
            }
        }

        return i == other.size();
    }

    template <std::size_t M>
    constexpr bool startswith(const char(&a)[M])
    {
        return startswith(constexpr_string<M>(a, M - 1));
    }


    constexpr constexpr_string<N> substr(std::size_t pos, std::size_t len = -1) const
    {
        if (pos > size_) {
            throw std::runtime_error("out of range");
        }

        const std::size_t new_size = (len == -1)?  (size_ - pos): std::min(len, (size_ - pos));
        return constexpr_string<N>(data_.data() + pos, new_size);
    }

    constexpr const char* data() const 
    {
        return data_.data();
    }

    constexpr iterator begin()
    {
        return data_.data();
    }

    constexpr iterator end()
    {
        return data_.data() + size_ + 1;
    }

    constexpr void erase(iterator pos)
    {   
        for (; pos < end() - 1; ++pos) {
            swap(*pos, *(pos + 1));
        }

        --size_;
    }

    constexpr void erase(iterator begin, iterator end)
    {
        auto it = begin;

        for (; it < end; ++it) {
            erase(begin);
        }
    }

private:
    std::array<char, N> data_;
    std::size_t size_;
};

#endif //TEMPLATE_CRUSH_SAGA_CONSTEXPR_STRING_HPP
