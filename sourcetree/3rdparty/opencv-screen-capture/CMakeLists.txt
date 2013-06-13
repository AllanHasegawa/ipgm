project(opencv-screen-capture)

set(SRCS
	screenCapture.cpp
)

add_library(opencv-screen-capture STATIC ${SRCS})
#target_link_libraries(open ${OpenCV_LIBS})