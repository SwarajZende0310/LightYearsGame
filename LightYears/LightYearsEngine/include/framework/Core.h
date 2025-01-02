#pragma once

#include<stdio.h>

namespace ly
{
    // Macro definition
    #define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}