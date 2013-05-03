cmake_minimum_required (VERSION 2.8)
project (IPGM)

set(OpenCV_DIR $ENV{OpenCV_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${OpenCV_DIR}/lib ${CMAKE_SOURCE_DIR}/../cmake)

find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include}

set(SRCS 3rdparty/opencv-screen-capture/screenCapture.cpp
	main.cpp
)

add_executable(ipmg WIN32 ${SRCS})
target_link_libraries(ipmg ${OpenCV_LIBS})

