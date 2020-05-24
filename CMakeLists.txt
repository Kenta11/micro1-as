cmake_minimum_required (VERSION 3.10)
enable_language(CXX)
project ("micro1-as")
set(CMAKE_CXX_STANDARD 17)

# files
include_directories(include/)
file(GLOB source_code src/*)

add_executable(micro1-as ${source_code})