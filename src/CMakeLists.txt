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


include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
                    "${CMAKE_CURRENT_BINARY_DIR}")

set(DEAP_UI
    gui/LoginWidget.ui
    gui/MainWindow.ui)
set(DEAP_HPP
    core/FilePath.hpp
    database/Database.hpp
    database/entities/Admin.hpp
    database/entities/Delegate.hpp
    database/entities/Student.hpp
    gui/LoginWidget.hpp
    gui/MainWindow.hpp)
set(DEAP_CPP
    main.cpp
    core/FilePath.cpp
    database/Database.cpp
    gui/LoginWidget.cpp
    gui/MainWindow.cpp)

find_package(Qt5 REQUIRED
             COMPONENTS Gui Sql Widgets)

configure_file(config-deap.hpp.in
               "${CMAKE_CURRENT_BINARY_DIR}/config-deap.hpp")
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC TRUE)

add_executable(deap ${DEAP_UI} ${DEAP_HPP} ${DEAP_CPP})
target_link_libraries(deap Qt5::Gui Qt5::Sql Qt5::Widgets)
