cmake_minimum_required(VERSION 3.5)
project(parts_localization)

find_package( OpenCV REQUIRED )
find_library( Matio_LIBS matio )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories("./include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -D WITH_OPENMP=ON ")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lz")

set(SOURCE_FILES main.cpp edgesDetect.cpp edgesDetectMex.cpp parts_localization.cpp parts_localization_main.cpp edgesChns.cpp   edgesNmsMex.cpp gadgets.cpp tools/ConvTri.cpp tools/convConst.cpp  tools/gradient.cpp tools/gradientMex.cpp  tools/rgbConvertMex.cpp  tools/imPadMex.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(parts_localization ${SOURCE_FILES})
target_link_libraries(parts_localization ${OpenCV_LIBS} ${Matio_LIBS})
