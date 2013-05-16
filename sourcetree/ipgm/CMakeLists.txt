project(IPGM)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ipgm/include)
include_directories(${INCLUDE_DIR})

set(SRCS
	Log.cpp
	main.cpp
	IPGM.cpp
	IPSystem.cpp
	MouseSystem.cpp
	WindowManager.cpp
	KeyboardSystem.cpp
)

set(HEADERS
	Log.hpp
	IPGM.hpp
	IPGMCallbacks.hpp
	IPSystem.hpp
	MouseSystem.hpp
	WindowManager.hpp
	KeyboardSystem.hpp
)

foreach(V ${HEADERS})
	set(_HEADERS ${_HEADERS} ${INCLUDE_DIR}/${V})
endforeach()

add_executable(ipmg WIN32 ${SRCS} ${_HEADERS})
target_link_libraries(ipmg ${OpenCV_LIBS} opencv-screen-capture)
