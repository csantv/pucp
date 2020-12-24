# Code I've written whilst in college
# Copyright (C) 2020   Carlos Toro

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.17)
project(INF281 CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(INF281
        2020-2/lab9/Paciente.cpp
        2020-2/lab9/Paciente.h
        2020-2/lab9/Ambulatorio.cpp
        2020-2/lab9/Ambulatorio.h
        2020-2/lab9/Urgencia.cpp
        2020-2/lab9/Urgencia.h
        2020-2/lab9/Emergencia.cpp
        2020-2/lab9/Emergencia.h
        2020-2/lab9/p2.cpp
        2020-2/lab9/ListaDePacientes.cpp
        2020-2/lab9/ListaDePacientes.h
        2020-2/lab9/NodoPaciente.cpp
        2020-2/lab9/NodoPaciente.h)
