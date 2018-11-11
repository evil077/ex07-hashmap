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
#include <memory>

namespace edu { namespace vcccd { namespace vc { namespace csv15 {

template <class KeyType, class ValueType>
class HashMap {
public:
    typedef std::pair<KeyType, ValueType> pair_type;

    class Iterator {
    public:
        Iterator(pair_type **first, pair_type **last) {
            _current = first;
            _last = last;
            _incrementToNextNonEmpty();
        }

        Iterator(const Iterator &other) {
            _current = other._current;
            _last = other._last;
        }

    public:
        pair_type &operator*() {
            return **_current;
        }

        pair_type *operator->() {
            return *_current;
        }

        const Iterator operator++(int) {
            _current++;
            _incrementToNextNonEmpty();
            return *this;
        }

        Iterator &operator=(pair_type *p) {
            *_current = p;
            return *this;
        }

        bool operator==(const Iterator &that) const {
            return this->_current == that._current;
        }

        bool operator!=(const Iterator &that) const {
            return !(*this == that);
        }

    private:
        void _incrementToNextNonEmpty() {
            for (; *_current == nullptr && _current != _last; _current++);
        }

    private:
        pair_type **_current;
        pair_type **_last;
    };

public:
    static constexpr size_t DEFAULT_BUCKET_SIZE = 7;
    static constexpr size_t C1 = 11;
    static constexpr size_t C2 = 14;
    static constexpr float DEFAULT_LOAD = 0.75;

public:
    HashMap(): _capacity(DEFAULT_BUCKET_SIZE), _size(0) {
        _buckets = new pair_type*[DEFAULT_BUCKET_SIZE];
        std::fill(_buckets, _buckets + _capacity, nullptr);
    }

    HashMap(const HashMap &other) {
        _buckets = new pair_type*[other._capacity];
        _capacity = other._capacity;
        _size = other._size;
        std::transform(other._buckets, other._buckets + _capacity, _buckets, [] (pair_type* bucket){
            return bucket == nullptr ? bucket : new pair_type(*bucket);
        });
    }

    HashMap(HashMap &&other) noexcept {
        _buckets = other._buckets;
        _capacity = other._capacity;
        _size = other._size;
    }

    virtual ~HashMap() {
        std::for_each(_buckets, _buckets+_capacity, [] (pair_type* bucket) {
            delete bucket;
        });
        delete [] _buckets;
    }

    pair_type *&_find(const KeyType &key) {
        size_t hashValue = _hash(key);
        size_t index = hashValue % _capacity;
        for(size_t i = 1; (_buckets[index] != nullptr && _buckets[index]->first != key) && i < _capacity; i++) {
            index = (hashValue + C1 * i + C2 * i * i) % _capacity;
        }
        return _buckets[index];
    }

public:
    Iterator find(const KeyType &key) {
        pair_type *&item = _find(key);
        if (item == nullptr) {
            return end();
        }
        return Iterator(&item, _buckets + _capacity);
    }

    void insert(const KeyType &key, ValueType value) {
        operator[](key) = value;
    }

    ValueType &operator[](const KeyType &key) {
        pair_type *&item = _find(key);
        // We need to check if this is an insert
        if (item == nullptr){
            _size++;
            item = new std::pair<KeyType, ValueType>;
            item->first = key;

            if (1.0 * _size / _capacity > DEFAULT_LOAD) {
                _rehash();
                item = _find(key);
            }
        }
        return item->second;
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

    size_t bucket_count() const {
        // Put your code here
    }

    bool empty() const {
        // Put your code here
    }

    Iterator erase(Iterator where) {
        // Put your code here
        return where;
    }

    Iterator erase(Iterator first, Iterator end) {
        // Put your code here
    }

    size_t erase(const KeyType &key) {
        // Put your code here
        return 0;
    }

    void swap(HashMap<KeyType, ValueType> &other) {
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
  size_t _hashSizeIndex = 0;
  std::hash<KeyType> _hash;
};

}}}}
#endif //HASH_MAP_HASH_MAP_H
