project(ITSPIC)

cmake_minimum_required(VERSION 2.8)

set(OpenCV_DIR $ENV{OpenCV_DIR})

find_package(OpenCV REQUIRED)
# TODO:
# automatic detection for IPGM lib
# automatic safe checking of variables
set(IPGM_INCLUDE_DIR CACHE FILEPATH "IPGM Include Dir")
set(IPGM_LIB_DIR CACHE FILEPATH "IPGM LIB DIR")
set(OPENCV_SCREEN_CAPTURE_LIB_DIR CACHE FILEPATH "opencv-screen-capture LIB dir")

include_directories(${IPGM_INCLUDE_DIR})
link_directories(${IPGM_LIB_DIR})
link_directories(${OPENCV_SCREEN_CAPTURE_LIB_DIR})

set(SRCS
	main.cpp
)


add_executable(itspic ${SRCS})
target_link_libraries(itspic ${OpenCV_LIBS} ipgm opencv-screen-capture)
