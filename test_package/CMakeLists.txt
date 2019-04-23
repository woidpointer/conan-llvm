cmake_minimum_required(VERSION 2.8.12)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Clang REQUIRED)


add_executable(example example.cpp)


if(WIN32)
target_link_libraries(example 
  clangTooling 
  )
else(WIN32)

target_compile_options(example 
  PRIVATE
  -fno-rtti
  -fno-exceptions
)

target_link_libraries(example 
  clangTooling 
  )
endif(WIN32)

