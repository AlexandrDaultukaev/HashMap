#pragma once
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <optional>
#include <utility>
#include <vector>

static const std::size_t SIZE = 5;

template <class K, class V> class Iterator {
    typename std::vector<std::list<std::pair<const K, V>>>::iterator ivect;
    typename std::vector<std::list<std::pair<const K, V>>>::iterator ivect_end;
    typename std::list<std::pair<const K, V>>::iterator ilist;

  public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::pair<const K, V>;
    using difference_type = std::ptrdiff_t;
    using pointer = std::pair<const K, V> *;
    using reference = std::pair<const K, V> &;

    Iterator<K, V>(
        typename std::vector<std::list<std::pair<const K, V>>>::iterator iv,
        typename std::vector<std::list<std::pair<const K, V>>>::iterator ivend)
        : ivect(iv), ivect_end(ivend) {
        if (ivect != ivect_end) {
            ilist = ivect->begin();
            if (ilist == ivect->end()) {
                while (ilist == ivect->end() && ivect != ivect_end) {
                    ivect++;
                    ilist = ivect->begin();
                }
                if (ivect == ivect_end) {
                    std::cerr << "Error: Unable to iterate on an empty HashMap";
                }
            }
        }
    }
    Iterator &operator++() {
        if (ivect == ivect_end) {
        } else {
            if (ilist != ivect->end()) {
                ilist++;
            }
            if (ilist == ivect->end()) {
                while (ilist == ivect->end() && ivect != ivect_end) {
                    ivect++;
                    if (ivect == ivect_end) {
                        break;
                    }
                    ilist = ivect->begin();
                }
            }
        }
        return *this;
    }

    Iterator operator++(int) {
        Iterator<K, V> tmp = *this;
        this->operator++();
        return tmp;
    }

    bool operator!=(Iterator p) const { return ivect != p.ivect; }
    bool operator==(Iterator p) const { return ivect == p.ivect; }

    std::pair<const K, V> operator*() const { return *ilist; }

    std::pair<const K, V> *operator->() const { return &*ilist; }
};

template <class K, class V> class HashMap {
    std::vector<std::list<std::pair<const K, V>>> elements;

  public:
    // auto begin() -> decltype(Iterator<K, V>(elements.begin(),
    // elements.end())) {
    //    return Iterator<K, V>(elements.begin(), elements.end());
    //}
    // auto end() -> decltype(Iterator<K, V>(elements.end(), elements.end())) {
    //    return Iterator<K, V>(elements.end(), elements.end());
    //}
    Iterator<K, V> begin() {
        return Iterator<K, V>(elements.begin(), elements.end());
    }

    Iterator<K, V> end() {
        return Iterator<K, V>(elements.end(), elements.end());
    }

    HashMap() { elements.resize(SIZE); }

    std::size_t get_hash(K key) {
        return std::floor(std::hash<K>{}(key) % SIZE);
    }

    void set_value(K key, V value) {
        std::size_t hash = get_hash(key);

        std::pair<K, V> p(key, value);

        elements[hash].push_back(p);
    }

    V get_value(K key) {
        std::size_t hash = get_hash(key);
        auto it = elements[hash].begin();
        for (; it != elements[hash].end(); it++) {
            if (it->first == key) {
                return it->second;
            }
        }
        return V();
    }

    V &operator[](K key) {
        std::size_t hash = get_hash(key);
        auto it = elements[hash].begin();
        for (; it != elements[hash].end(); it++) {
            if (it->first == key) {
                return it->second;
            }
        }
        set_value(key, V());
        return elements[hash].back().second;
    }

    std::vector<std::pair<K, V>> as_vector(int print_key = 0) const {
        std::vector<std::pair<K, V>> mp;
        for (auto &i : elements) {
            typename std::list<std::pair<const K, V>>::const_iterator it =
                i.begin();
            for (; it != i.end(); it++) {
                std::pair<K, V> p(it->first, it->second);
                mp.push_back(p);
                if (print_key)
                    std::cout << "  -" << it->first << "-" << it->second
                              << '\n';
            }
        }
        if (print_key)
            std::cout << "----------------------------------------------\n";
        return mp;
    }

    bool operator==(const HashMap &other) const {
        return as_vector() == other.as_vector();
    }

    HashMap &operator=(const HashMap &other) {
        int ind = 0;
        if (this == &other)
            return *this;
        for (auto &i : other.elements) {
            // elements[ind] = i;
            typename std::list<std::pair<const K, V>>::const_iterator it =
                i.begin();
            for (; it != i.end(); it++) {
                std::pair<const K, V> p(it->first, it->second);
                elements[ind].push_back(p);
            }
        }
        return *this;
    }

    std::optional<V> find_value(K key) {
        std::size_t hash = get_hash(key);
        auto it = elements[hash].begin();
        std::optional<V> opt;
        for (; it != elements[hash].end(); it++) {
            if (it->first == key) {
                opt = it->second;
                return opt;
            }
        }
        return opt;
    }
};