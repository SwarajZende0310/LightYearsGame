#pragma once

#include<stdio.h>
#include<memory>
#include<vector>
#include<map>
#include<unordered_map>
#include<unordered_set>

namespace ly
{
    template<typename T>
    using unique = std::unique_ptr<T>;

    template<typename T>
    using shared = std::shared_ptr<T>;

    template<typename T>
    using weak = std::weak_ptr<T>;

    template<typename T>
    using List = std::vector<T>;

    template<typename keyType,typename valType,typename Pr=std::less<keyType>>
    using Map = std::map<keyType,valType,Pr>;

    template<typename keyType,typename valType,typename Hasher=std::hash<keyType>>
    using Dictionary = std::unordered_map<keyType,valType,Hasher>;

    template<typename T>
    using Set = std::unordered_set<T>;

    using uint6 = unsigned char;

    // Macro definition
    #define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}