#pragma once
#include "Array.hpp"

template<typename T>
class UnorderedArray : public Array<T> {
    using Base = Array<T>;
public:
    using Base::Array;
    bool Push(const T& v) override {
        Base::EnsureGrow(); new (Base::m_data + Base::m_size) T(v); ++Base::m_size; return true;
    }
    bool Push(T&& v) override {
        Base::EnsureGrow(); new (Base::m_data + Base::m_size) T(std::move(v)); ++Base::m_size; return true;
    }
};
