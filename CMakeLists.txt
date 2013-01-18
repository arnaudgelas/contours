project( FindContours )

cmake_minimum_required( VERSION 2.8 )

set( CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} )

find_package( OpenCV REQUIRED )
include_directories( BEFORE ${OPENCV_INCLUDE_DIRS} )

add_executable( findcontours findcontours.cxx )
target_link_libraries( findcontours ${OPENCV_LIBRARIES} )
