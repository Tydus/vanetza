cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)
project(Vanetza)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/static)
set(CMAKE_CXX_STANDARD 11)
include(VanetzaModule)

option(ENABLE_CONAN "Build with conan package manager" OFF)
if(ENABLE_CONAN)
    include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

option(ENABLE_TESTS "Build unit tests" OFF)
if(ENABLE_TESTS)
    enable_testing()
    include(gtest/GTestFramework.cmake)
endif()

# Add subdirectory only when tests are enabled
## DIR subdirectory name
macro(add_test_subdirectory DIR)
  if(ENABLE_TESTS)
    add_subdirectory(${DIR})
  endif(ENABLE_TESTS)
endmacro(add_test_subdirectory)

add_subdirectory(vanetza)
add_subdirectory(tools/cohda_proxy)
add_subdirectory(tools/proxy_fake_feed)

option(ENABLE_SOCKTAP "Build socktap application" OFF)
if(ENABLE_SOCKTAP)
  add_subdirectory(tools/socktap)
endif()
vanetza_export_modules()

