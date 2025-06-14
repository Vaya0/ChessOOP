#pragma once
#pragma once
#include <stdexcept>
#include <algorithm>

template<typename T>
class Vector {
private:
    T* data;
    size_t capacity_;
    size_t size_;

    void reallocate(size_t newCapacity) {
        if (newCapacity <= capacity_) {
            throw std::logic_error("New capacity must be greater than current capacity.");
        }
        T* newData = new T[newCapacity];

        for (size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data[i]);
        }

        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }

    void ensureCapacity(size_t minCapacity) {
        if (minCapacity > capacity_) {
            size_t newCapacity = capacity_ == 0 ? 1 : capacity_;
            while (newCapacity < minCapacity) {
                newCapacity *= 2;
            }
            reallocate(newCapacity);
        }
    }

public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector() : data(nullptr), capacity_(0), size_(0) {}

    explicit Vector(size_t count) : data(nullptr), capacity_(0), size_(0) {
        resize(count);
    }

    Vector(size_t count, const T& value) : data(nullptr), capacity_(0), size_(0) {
        resize(count, value);
    }

    Vector(std::initializer_list<T> init) : data(nullptr), capacity_(0), size_(0) {
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
    }

    Vector(const Vector& other) : data(nullptr), capacity_(0), size_(0) {
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; ++i) {
            push_back(other.data[i]);
        }
    }

    Vector(Vector&& other) noexcept
        : data(other.data), capacity_(other.capacity_), size_(other.size_) {
        other.data = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    ~Vector() {
        clear();
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            clear();
            reserve(other.size_);
            for (size_t i = 0; i < other.size_; ++i) {
                push_back(other.data[i]);
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            delete[] data;

            data = other.data;
            capacity_ = other.capacity_;
            size_ = other.size_;

            other.data = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    Vector& operator=(std::initializer_list<T> init) {
        clear();
        reserve(init.size());
        for (const auto& item : init) {
            push_back(item);
        }
        return *this;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }
        return data[index];
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("Vector is empty");
        }
        return data[0];
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Vector is empty");
        }
        return data[0];
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("Vector is empty");
        }
        return data[size_ - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Vector is empty");
        }
        return data[size_ - 1];
    }

    T* getData() { return data; }
    const T* getData() const { return data; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    const_iterator cbegin() const { return data; }

    iterator end() { return data + size_; }
    const_iterator end() const { return data + size_; }
    const_iterator cend() const { return data + size_; }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    void reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            reallocate(newCapacity);
        }
    }

    void shrink_to_fit() {
        if (size_ < capacity_) {
            reallocate(size_);
        }
    }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
        size_ = 0;
    }

    void push_back(const T& value) {
        ensureCapacity(size_ + 1);
        new(data + size_) T(value);
        ++size_;
    }

    void push_back(T&& value) {
        ensureCapacity(size_ + 1);
        new(data + size_) T(std::move(value));
        ++size_;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        ensureCapacity(size_ + 1);
        new(data + size_) T(std::forward<Args>(args)...);
        ++size_;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("Vector is empty");
        }
        --size_;
        data[size_].~T();
    }

    void resize(size_t newSize) {
        if (newSize > size_) {
            ensureCapacity(newSize);
            for (size_t i = size_; i < newSize; ++i) {
                new(data + i) T();
            }
        }
        else if (newSize < size_) {
            for (size_t i = newSize; i < size_; ++i) {
                data[i].~T();
            }
        }
        size_ = newSize;
    }

    void resize(size_t newSize, const T& value) {
        if (newSize > size_) {
            ensureCapacity(newSize);
            for (size_t i = size_; i < newSize; ++i) {
                new(data + i) T(value);
            }
        }
        else if (newSize < size_) {
            for (size_t i = newSize; i < size_; ++i) {
                data[i].~T();
            }
        }
        size_ = newSize;
    }

    iterator insert(const_iterator pos, const T& value) {
        size_t index = pos - data;
        ensureCapacity(size_ + 1);

        for (size_t i = size_; i > index; --i) {
            new(data + i) T(std::move(data[i - 1]));
            data[i - 1].~T();
        }

        new(data + index) T(value);
        ++size_;
        return data + index;
    }

    iterator insert(const_iterator pos, T&& value) {
        size_t index = pos - data;
        ensureCapacity(size_ + 1);

        for (size_t i = size_; i > index; --i) {
            new(data + i) T(std::move(data[i - 1]));
            data[i - 1].~T();
        }

        new(data + index) T(std::move(value));
        ++size_;
        return data + index;
    }

    iterator erase(const_iterator pos) {
        size_t index = pos - data;
        if (index >= size_) {
            throw std::out_of_range("Iterator out of range");
        }

        data[index].~T();

        for (size_t i = index; i < size_ - 1; ++i) {
            new(data + i) T(std::move(data[i + 1]));
            data[i + 1].~T();
        }

        --size_;
        return data + index;
    }

    iterator erase(const_iterator first, const_iterator last) {
        size_t firstIndex = first - data;
        size_t lastIndex = last - data;
        size_t count = lastIndex - firstIndex;

        if (firstIndex > size_ || lastIndex > size_ || firstIndex > lastIndex) {
            throw std::out_of_range("Iterator range invalid");
        }

        for (size_t i = firstIndex; i < lastIndex; ++i) {
            data[i].~T();
        }

        for (size_t i = firstIndex; i < size_ - count; ++i) {
            new(data + i) T(std::move(data[i + count]));
            data[i + count].~T();
        }

        size_ -= count;
        return data + firstIndex;
    }

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const {
        return std::lexicographical_compare(begin(), end(), other.begin(), other.end());
    }

    bool operator<=(const Vector& other) const {
        return !(other < *this);
    }

    bool operator>(const Vector& other) const {
        return other < *this;
    }

    bool operator>=(const Vector& other) const {
        return !(*this < other);
    }
};

