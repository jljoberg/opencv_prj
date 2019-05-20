cmake_minimum_required(VERSION 2.8)
project( SequenceDetect )
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(  SequenceDetect   sequenceDetect.cpp methods/processing.cpp)
target_link_libraries(  SequenceDetect  ${OpenCV_LIBS} )

set(CMAKE_CXX_COMPILER /usr/bin/g++)
message("Compiler is " ${CMAKE_CXX_COMPILER} )
