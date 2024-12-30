cmake_minimum_required(VERSION 3.22.1)

project(LightYears
        VERSION 1.0.0 #({new_iteration_of_code}.{new_feature_addition}.{bug_fixes})
        LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

add_subdirectory(LightYears)