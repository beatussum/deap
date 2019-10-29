message(STATUS "Building ${CMAKE_PROJECT_NAME}…")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(DEAP_CPP
    main.cpp)
set(DEAP_HPP)

find_package(SQLite3 REQUIRED)

configure_file(config-deap.hpp.in
               "${CMAKE_CURRENT_BINARY_DIR}/config-deap.hpp")

add_executable(deap ${DEAP_CPP} ${DEAP_HPP})
target_link_libraries(deap SQLite::SQLite3)
