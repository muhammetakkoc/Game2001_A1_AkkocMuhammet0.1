#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
protected:
    T* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
    size_t m_nextGrow = 2;

    void Realloc(size_t newCap) {
        if (newCap < m_size) throw std::runtime_error("realloc");
        T* newData = newCap ? static_cast<T*>(operator new[](newCap * sizeof(T))) : nullptr;
        for (size_t i = 0; i < m_size; ++i) {
            new (newData + i) T(std::move(m_data[i]));
            m_data[i].~T();
        }
        operator delete[](m_data);
        m_data = newData;
        m_capacity = newCap;
    }
    void Expand() {                    
        size_t add = m_nextGrow ? m_nextGrow : 2;
        Realloc(m_capacity + add);
        m_nextGrow = add * 2;
    }
    void EnsureGrow() { if (m_size >= m_capacity) Expand(); }

public:
    Array() = default;
    explicit Array(size_t cap) {
        if (cap) { m_data = static_cast<T*>(operator new[](cap * sizeof(T))); m_capacity = cap; }
    }
    Array(const Array& o) {
        m_capacity = o.m_capacity; m_size = o.m_size; m_nextGrow = o.m_nextGrow;
        if (m_capacity) {
            m_data = static_cast<T*>(operator new[](m_capacity * sizeof(T)));
            for (size_t i = 0; i < m_size; ++i) new (m_data + i) T(o.m_data[i]);
        }
    }
    Array(Array&& o) noexcept {
        m_data = o.m_data; m_size = o.m_size; m_capacity = o.m_capacity; m_nextGrow = o.m_nextGrow;
        o.m_data = nullptr; o.m_size = 0; o.m_capacity = 0; o.m_nextGrow = 2;
    }
    virtual ~Array() { Clear(); operator delete[](m_data); }

    T& operator[](size_t i) { if (i >= m_size) throw std::out_of_range("[]"); return m_data[i]; }
    const T& operator[](size_t i) const { if (i >= m_size) throw std::out_of_range("[]"); return m_data[i]; }

    size_t Size() const { return m_size; }
    size_t Capacity() const { return m_capacity; }
    bool   Empty() const { return m_size == 0; }

    bool Contains(const T& v) const { for (size_t i = 0; i < m_size; ++i) if (m_data[i] == v) return true; return false; }

    virtual void RemoveAt(size_t idx) {
        if (idx >= m_size) throw std::out_of_range("remove");
        m_data[idx].~T();
        for (size_t i = idx; i + 1 < m_size; ++i) { new(m_data + i) T(std::move(m_data[i + 1])); m_data[i + 1].~T(); }
        --m_size;
    }
    void Clear() { for (size_t i = 0; i < m_size; ++i) m_data[i].~T(); m_size = 0; }

    virtual bool Push(const T& v) = 0;
    virtual bool Push(T&& v) = 0;
};
