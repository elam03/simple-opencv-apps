cmake_minimum_required(VERSION 2.8)

project(opencv-cpp-test)

find_package(OpenCV REQUIRED)

add_executable(opencv-cpp-test main.cpp)

target_link_libraries(opencv-cpp-test ${OpenCV_LIBS})
