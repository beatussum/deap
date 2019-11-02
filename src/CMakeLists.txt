include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(DEAP_CPP
    main.cpp
    database/Database.cpp)
set(DEAP_HPP
	database/Database.hpp
	database/entities/Admin.hpp
	database/entities/Delegate.hpp
	database/entities/Student.hpp)

find_package(Qt5 REQUIRED
             COMPONENTS Gui Sql Widgets)

configure_file(config-deap.hpp.in
               "${CMAKE_CURRENT_BINARY_DIR}/config-deap.hpp")

add_executable(deap ${DEAP_HPP} ${DEAP_CPP})
target_link_libraries(deap Qt5::Gui Qt5::Sql Qt5::Widgets)
