project(IPGM)

set(SRCS
	main.cpp
)

add_executable(ipmg WIN32 ${SRCS})
target_link_libraries(ipmg ${OpenCV_LIBS} opencv-screen-capture)