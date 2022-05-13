cmake_minimum_required(VERSION 3.8)
project(HashMap VERSION 1.0 LANGUAGES CXX)

<<<<<<< HEAD
set(SRC_PATH {CMAKE_SOURCE_DIR}/src/hashmap)

enable_testing()

add_library(hashmap ${CMAKE_CURRENT_LIST_DIR}/src/hashmap/hashmap.hpp)
=======
set(SRC_PATH ${CMAKE_SOURCE_DIR}/src/hashmap)

enable_testing()

add_library(hashmap INTERFACE)
target_sources(hashmap INTERFACE ${SRC_PATH}/hashmap.hpp)


>>>>>>> dev
add_executable(HMtest tests/hashmap/hashmap.cpp)

target_include_directories(
  HMtest
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/hashmap
)

target_link_libraries(
  HMtest
    hashmap
    gtest_main
)

add_subdirectory(external)

find_program(
  CLANG_TIDY_EXE
  NAMES clang-tidy-11 clang-tidy
)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(CompileOptions)
<<<<<<< HEAD
set_compile_options(hashmap)
=======
set_compile_options(HMtest)

>>>>>>> dev
set_target_properties(
    HMtest
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      CXX_EXTENSIONS OFF
      LINKER_LANGUAGE CXX
  )

include(GoogleTest)
gtest_discover_tests(HMtest)

