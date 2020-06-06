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
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
enable_testing()

include_directories(include)
file(GLOB source_code src/*.cc)

add_executable(micro1-as ${source_code})

include_directories(third_party/googletest/googletest/include)
add_subdirectory(third_party/googletest/googletest)

add_executable(test_instruction test/src/test_instruction.cc src/instruction.cc)
target_link_libraries(test_instruction gtest gtest_main)
add_test(NAME test_instruction COMMAND ./bin/test_instruction)

add_executable(test_lexer test/src/test_lexer.cc src/lexer.cc)
target_link_libraries(test_lexer gtest gtest_main)
file(GLOB input_files_for_test test/input/*.txt)
file(COPY ${input_files_for_test} DESTINATION ${CMAKE_BINARY_DIR}/test/input)
add_test(NAME test_lexer COMMAND ./bin/test_lexer)

# add_executable(test_parser test/src/test_parser.cc src/parser.cc)
# target_link_libraries(test_parser gtest gtest_main)
