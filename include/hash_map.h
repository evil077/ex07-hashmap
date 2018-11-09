//
// Created by aknight on 10/24/2018.
//

#ifndef HASH_MAP_HASH_MAP_H
#define HASH_MAP_HASH_MAP_H

#include <utility>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <algorithm>

namespace edu { namespace vcccd { namespace vc { namespace csv15 {

template <class KeyType, class ValueType>
class HashMap {
public:
    class Iterator {
    public:
        Iterator(std::pair<KeyType, ValueType> **first, std::pair<KeyType, ValueType> **last) {
            _current = first;
            _last = last;
            _incrementToNextNonEmpty();
        }

        Iterator(const Iterator &other) {
            _current = other._current;
            _last = other._last;
        }

    public:
        const std::pair<KeyType, ValueType> &operator*() {
            return **_current;
        }

        Iterator &operator++(int) {
            _current++;
            _incrementToNextNonEmpty();
            return *this;
        }

        bool operator!=(const Iterator &that) {
            return this->_current != that._current;
        }

    private:
        void _incrementToNextNonEmpty() {
            for (; *_current == nullptr && _current != _last; _current++);
        }
    private:
        std::pair<KeyType, ValueType> **_current;
        std::pair<KeyType, ValueType> **_last;
    };
public:
    static constexpr size_t DEFAULT_BUCKET_SIZE = 7;
    static constexpr size_t C1 = 11;
    static constexpr size_t C2 = 14;
    static constexpr float DEFAULT_LOAD = 0.75;

public:
    HashMap(): _capacity(DEFAULT_BUCKET_SIZE), _size(0) {
        _buckets = new std::pair<KeyType, ValueType>*[DEFAULT_BUCKET_SIZE];
        std::fill(_buckets, _buckets + _capacity, nullptr);
    }

    HashMap(const HashMap &other) {
        _buckets = new std::pair<KeyType, ValueType>*[other._capacity];
        _capacity = other._capacity;
        _size = other._size;
        std::copy(other._buckets, other._buckets + _capacity, _buckets);
    }

    HashMap(HashMap &&other) {
        _buckets = other._buckets;
        _capacity = other._capacity;
        _size = other._size;
    }

    ~HashMap() {
        std::for_each(_buckets, _buckets+_capacity, [] (std::pair<KeyType, ValueType>* bucket) {
            delete bucket;
        });
        delete [] _buckets;
    }

public:
    ValueType find(const KeyType &key) {
        return operator[](key);
    }

    void insert(const KeyType &key, ValueType value) {
        operator[](key) = value;
    }

    ValueType &operator[](const KeyType &key) {
        size_t hashValue = _hash(key);
        size_t index = hashValue % _capacity;
        for(size_t i = 1; (_buckets[index] != nullptr && _buckets[index]->first != key) && i < _capacity; i++) {
            index = (hashValue + C1 * i + C2 * i * i) % _capacity;
        }
        // We need to check if this is an insert
        if (_buckets[index] == nullptr){
            _size++;
            _buckets[index] = new std::pair<KeyType, ValueType>;
            _buckets[index]->first = key;

            if (1.0 * _size / _capacity > DEFAULT_LOAD) {
                _rehash();
            }
        }
        return _buckets[index]->second;
    }

    Iterator begin() {
        return Iterator(_buckets, _buckets + _capacity);
    }

    Iterator end() {
        return Iterator(_buckets + _capacity, _buckets + _capacity);
    }

    size_t size() const {
        // Put your code here
    }

    bool empty() const {
        // Put your code here
    }

    Iterator erase(Iterator where) {
        // Put your code here
    }

    Iterator erase(Iterator first, Iterator end) {
        // Put your code here
    }

    size_t erase(const KeyType &key) {
        // Put your code here
        return 0;
    }

    void swap(const HashMap<KeyType, ValueType> &other) {
        // Put your code here
    }

    void clear() {
        // Put your code here
    }

private:
    void _rehash() {
        // Put your code here
    }

private:
  std::pair<KeyType, ValueType> **_buckets;
  size_t _capacity;
  size_t _size;
  std::hash<KeyType> _hash;
};

}}}}
#endif //HASH_MAP_HASH_MAP_H
