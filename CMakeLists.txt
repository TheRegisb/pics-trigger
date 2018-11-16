# Copyright 2018 Régis Berthelot

# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at

#   http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

cmake_minimum_required(VERSION 3.1)

if (CMAKE_COMPILER_IS_GNUCC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
elseif (MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

project(pics-trigger)
set (pics-trigger_VERSION_MAJOR 1)
set (pics-trigger_VERSION_MINOR 0)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(SOURCES
  src/main.cpp
  src/TextureManager.cpp
  src/picstrigger.cpp
  src/SpriteSheet.cpp
  src/Parameters.cpp)

if (WIN32)
  include_directories(${CMAKE_SOURCE_DIR}/SFML_win32/include)
  link_directories(${CMAKE_SOURCE_DIR}/SFML_win32/lib)
  add_custom_target(deploy ALL)
  add_custom_command(TARGET deploy POST_BUILD
		     COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${CMAKE_SOURCE_DIR}/SFML_win32/bin"
			${CMAKE_BINARY_DIR}/Release)
else()
  find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
endif()

add_executable(pics-trigger ${SOURCES})
target_link_libraries(pics-trigger sfml-graphics sfml-window sfml-system)
