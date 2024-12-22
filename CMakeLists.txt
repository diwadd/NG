cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_COMPILER "/usr/bin/clang-18")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -std=c++23)
add_link_options(-lstdc++)


project(NG)

add_subdirectory(Utilities)
add_subdirectory(UserEquipment)


find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )



add_executable(NG main.cpp)

target_link_libraries(NG PUBLIC Utilities)
target_link_libraries(NG PUBLIC ${ZeroMQ_LIBRARY})

target_include_directories(NG PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Utilities"
                          "${PROJECT_SOURCE_DIR}/UserEquipment"
                          )


