cmake_minimum_required(VERSION 2.8)
project( RealSenseWheelCalib LANGUAGES CXX CUDA )
find_package( OpenCV REQUIRED )
find_package( realsense2 REQUIRED )
find_package( PCL REQUIRED )
find_package( Threads REQUIRED )
# set our includes directory
set ( target_includes
    include
)
include_directories( ${target_includes} ${OpenCV_INCLUDE_DIRS} ${realsense2_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} )
# set out source list
set ( target_sources
    src/Error.cpp
    src/Source.cpp
    src/RealSense.cpp
    src/main.cpp
    src/rgbd_deprojection.cu
)
add_executable( RealSenseWheelCalib ${target_sources} )
target_link_libraries( RealSenseWheelCalib ${OpenCV_LIBS} ${realsense2_LIBRARY} ${PCL_LIBRARIES} )
