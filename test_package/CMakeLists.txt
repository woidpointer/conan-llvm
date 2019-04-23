cmake_minimum_required(VERSION 2.8.12)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Clang REQUIRED)


add_executable(example example.cpp)

target_compile_options(example 
  PRIVATE
  -fno-rtti
  -fno-exceptions
)

target_link_libraries(example 
  clangTooling 
  )





# CTest is a testing tool that can be used to test your project.
# enable_testing()
# add_test(NAME example
#          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#          COMMAND example)
