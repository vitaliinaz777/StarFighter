#pragma once
#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>


namespace st {
    template<typename T>
    using unique = std::unique_ptr<T>;

    template<typename T>
    using shared = std::shared_ptr<T>;

    template<typename T>
    using weak = std::weak_ptr<T>;

    template<typename T>
    using List = std::vector<T>;

    // Red-Black Tree complexity O(log n)
    template<typename keyType, typename valType, typename Pr = std::less<keyType>>
    using Map = std::map<keyType, valType, Pr>;

    // Hashmap average complexity O(1)
    template<typename keyType, typename valType, typename hasher = std::hash<keyType>>
    using Dictionary = std::unordered_map<keyType, valType, hasher>;


    // macro for logging
    // ... is a variadic argument
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}