cmake_minimum_required(VERSION 3.31.3)

project(LightYears
        VERSION 1.0.0 #({new_iteration_of_code}.{new_feature_addition}.{bug_fixes})
        LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS off)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
        ${SFML_LIB_NAME}
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(LIGHT_YEARS_GAME_TARGET_NAME LightYearsGame)

add_subdirectory(LightYears)