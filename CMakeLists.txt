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
