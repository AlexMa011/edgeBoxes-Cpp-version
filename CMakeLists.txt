cmake_minimum_required(VERSION 2.5)
project(edgebox)



find_package(OpenCV REQUIRED)
find_library(Matio_LIBS matio)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("./include")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

file(GLOB tool_files tools/*.cpp)
file(GLOB main_files ./*.cpp)
set(SOURCE_FILES ${main_files} ${tool_files})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(edgebox ${SOURCE_FILES})
target_link_libraries(edgebox ${OpenCV_LIBS} ${Matio_LIBS})
