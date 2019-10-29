cmake_minimum_required(VERSION 3.14)

project(DEAP
        VERSION 0.9
        DESCRIPTION "An N.S.I. (Numérique et Sciences Informatiques) homework to help students elect their delegates"
        HOMEPAGE_URL "https://gitlab.com/beatussum/deap"
        LANGUAGES CXX)

# Use ccache if it is installed
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

set_property(GLOBAL PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED TRUE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_DEBUG TRUE)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/src")
