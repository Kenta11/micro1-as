# Copyright (c) 2020 Kenta Arai
# 
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.10)
project(micro1-as CXX)
set(CMAKE_CXX_STANDARD 17)
if(UNIX)
    # warnings
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Wall")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    endif ()
    if(NOT CMAKE_CXX_FLAGS MATCHES "-Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    endif()
    # optimization
    if(CMAKE_CXX_FLAGS MATCHES "-O[0-3]")
        string(REGEX REPLACE "-O[0-3]" "-O2" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    endif()
elseif(MSVC)
    # warnings
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    # optimization
    if(CMAKE_CXX_FLAGS MATCHES "/O[12d]")
        string(REGEX REPLACE "/O[12d]" "/O2" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
    endif()
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

option(BUILD_UNIT_TESTS "Build unit tests" OFF)

include_directories(include)
file(GLOB source_code src/*.cc)

add_executable(micro1-as ${source_code})

if(BUILD_UNIT_TESTS)
    enable_testing()

    file(GLOB input_files_for_test test/unittest/input/*)
    file(COPY ${input_files_for_test} DESTINATION ${CMAKE_BINARY_DIR}/test/unittest/input)

    include_directories(third_party/googletest/googletest/include)
    add_subdirectory(third_party/googletest/googletest)

    add_executable(test_instruction test/unittest/src/test_instruction.cc src/instruction.cc)
    target_link_libraries(test_instruction gtest gtest_main)
    add_test(NAME test_instruction COMMAND ./bin/test_instruction)

    add_executable(test_lexer test/unittest/src/test_lexer.cc src/lexer.cc)
    target_link_libraries(test_lexer gtest gtest_main)
    add_test(NAME test_lexer COMMAND ./bin/test_lexer)

    add_executable(test_parser test/unittest/src/test_parser.cc src/parser.cc src/lexer.cc src/instruction.cc)
    target_link_libraries(test_parser gtest gtest_main)
    add_test(NAME test_parser COMMAND ./bin/test_parser)
endif()
