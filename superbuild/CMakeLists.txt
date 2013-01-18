project( supa )

cmake_minimum_required( VERSION 2.8.6 )

include( ExternalProject )

find_package(Git)
if(NOT GIT_FOUND)
  message(ERROR "Cannot find git. git is required for Superbuild")
endif()

option( USE_GIT_PROTOCOL "If behind a firewall turn this off to use http instead." ON)

set(git_protocol "git")
if(NOT USE_GIT_PROTOCOL)
  set(git_protocol "http")
endif()

# Compute -G arg for configuring external projects with the same CMake
# generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}" )
endif()

if(${CMAKE_BUILD_TYPE})
  set(ep_common_args ${ep_common_args}
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  )
endif()

set( INSTALL_DIRECTORY ${CMAKE_BINARY_DIR}/INSTALL )

# ----------------------------------------------------------------
# ----------------------------------------------------------------
message( "External project - OpenCV" )

ExternalProject_Add(opencv
  GIT_REPOSITORY ${git_protocol}://code.opencv.org/opencv.git
  GIT_TAG 2.4.3.2
  SOURCE_DIR opencv
  BINARY_DIR opencv-build
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    -DBUILD_DOCS:BOOL=OFF
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_NEW_PYTHON_SUPPORT:BOOL=OFF
    -DBUILD_PACKAGE:BOOL=OFF
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -DBUILD_TESTS:BOOL=OFF
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DWITH_FFMPEG:BOOL=OFF
    -DWITH_CUDA:BOOL=OFF
    # -DWITH_EIGEN:BOOL=OFF
    -DBUILD_WITH_STATIC_CRT:BOOL=ON
    -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIRECTORY}
)

set( OPENCV_ROOT_DIR ${INSTALL_DIRECTORY} )
set( OPENCV_DIR ${INSTALL_DIRECTORY} )
# ----------------------------------------------------------------
# ----------------------------------------------------------------

ExternalProject_Add( Contours
  DEPENDS opencv
  DOWNLOAD_COMMAND ""
	UPDATE_COMMAND ""
	PATCH_COMMAND ""
	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
	BINARY_DIR Contours-build
	CMAKE_GENERATOR ${gen}
	CMAKE_ARGS
	${ep_common_args}
	-DOPENCV_DIR:PATH=${OPENCV_DIR}
	-DOPENCV_ROOT_DIR:PATH=${OPENCV_ROOT_DIR}
)
