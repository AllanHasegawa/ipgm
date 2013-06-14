project(ITSPIC)

cmake_minimum_required(VERSION 2.8)

set(OpenCV_DIR $ENV{OpenCV_DIR})

find_package(OpenCV REQUIRED)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE( Boost 1.53.0 COMPONENTS system REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
link_directories(${Boost_LIBRARY_DIRS})


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

message(STATUS "BOOOOOOST ${Boost_LIBRARIES}")

add_executable(itspic WIN32 ${SRCS})
target_link_libraries(itspic ${OpenCV_LIBS} ${Boost_LIBRARIES} ipgm opencv-screen-capture)
