#pragma once
#include "Array.hpp"

template<typename T>
class OrderedArray : public Array<T> {
    using Base = Array<T>;
    bool m_allowDuplicates = false;

    size_t LowerBound(const T& v) const {
        size_t lo = 0, hi = Base::m_size;
        while (lo < hi) { size_t mid = lo + (hi - lo) / 2; if (Base::m_data[mid] < v) lo = mid + 1; else hi = mid; }
        return lo;
    }
public:
    explicit OrderedArray(bool allowDup = false) : m_allowDuplicates(allowDup) {}
    OrderedArray(size_t cap, bool allowDup) : Base(cap), m_allowDuplicates(allowDup) {}

    bool Push(const T& v) override {
        if (!m_allowDuplicates && Base::Contains(v)) return false;
        Base::EnsureGrow();
        size_t pos = LowerBound(v);
        for (size_t i = Base::m_size; i > pos; --i) { new(Base::m_data + i) T(std::move(Base::m_data[i - 1])); Base::m_data[i - 1].~T(); }
        new(Base::m_data + pos) T(v); ++Base::m_size; return true;
    }
    bool Push(T&& v) override {
        if (!m_allowDuplicates && Base::Contains(v)) return false;
        Base::EnsureGrow();
        size_t pos = LowerBound(v);
        for (size_t i = Base::m_size; i > pos; --i) { new(Base::m_data + i) T(std::move(Base::m_data[i - 1])); Base::m_data[i - 1].~T(); }
        new(Base::m_data + pos) T(std::move(v)); ++Base::m_size; return true;
    }
};
