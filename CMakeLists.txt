cmake_minimum_required (VERSION 2.8)
project (stereoMatching)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
# export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/local/include/opencv4
aux_source_directory(. DIR_SRCS)
include_directories(${HDF5_INCLUDE_DIRS})
find_package( OpenCV REQUIRED )
find_package(HDF5)

add_executable(main main.cpp
                ./methods/bp.cpp
                ./methods/ioh.cpp
                ./methods/mbp.cpp
                ./methods/ncc.cpp 
                ./methods/sad.cpp

)
target_link_libraries( main ${OpenCV_LIBS} )
target_link_libraries( main ${HDF5_LIBRARIES} )