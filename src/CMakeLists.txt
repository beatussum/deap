# Copyright (C) 2019 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.


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
