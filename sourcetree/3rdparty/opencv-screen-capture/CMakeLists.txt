project(opencv-screen-capture)

set(SRCS
	screenCapture.cpp
)

add_library(opencv-screen-capture ${SRCS})
#target_link_libraries(open ${OpenCV_LIBS})