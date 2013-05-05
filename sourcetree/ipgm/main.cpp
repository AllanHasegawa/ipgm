#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"

#include "IPGM.hpp";
#include "IPGMCallbacks.hpp"
#include "Log.hpp"

class TI : public ipgm::IPGMCallbacks {
public:
	TI() {
	}
	virtual ~TI() {
	}

	void sensorON(const uint8_t ID) {
		ipgm::Log::instance()->printf("SENSOR ON %uc\n", ID);
	}
	void sensorOFF(const uint8_t ID) {
		ipgm::Log::instance()->printf("SENSOR OFF %uc\n", ID);
	}
	void actuatorON(const uint8_t ID) {
		ipgm::Log::instance()->printf("ACT ON %uc\n", ID);
	}
	void actuatorOFF(const uint8_t ID) {
		ipgm::Log::instance()->printf("ACT OFF %uc\n", ID);
	}
};

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	using namespace ipgm;

	TI ti;
	IPGM ipgm("", 0, 0, ti);
	
	ipgm.start();
	/*
	cv::waitKey(0);
	INPUT input[4];
	memset(input, 0, sizeof(input));
	input[0].type = INPUT_KEYBOARD;

	input[0].ki.wVk = 65; // ASCI value of A
	input[0].ki.dwFlags = 0;
	input[0].ki.time = 0;
	input[0].ki.dwExtraInfo = 0;

	input[1].ki.wVk = 65; // ASCI value of A
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;
	input[1].ki.time = 0;
	input[1].ki.dwExtraInfo = 0;

	//SendInput(2,input,sizeof(INPUT));
	POINT p;	

	if (GetCursorPos(&p))
	{
	}
	memset(input, 4, sizeof(input));
	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	input[0].mi.dx = 512*(65536.0f/GetSystemMetrics(SM_CXSCREEN));
	input[0].mi.dy = 512*(65536.0f/GetSystemMetrics(SM_CYSCREEN));
	input[0].mi.mouseData = 0;
	input[0].mi.time = 0;

	input[1].type = INPUT_MOUSE;
	input[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	input[1].mi.dx = 0;
	input[1].mi.dy = 0;
	input[1].mi.mouseData = 0;
	input[1].mi.time = 0;

	input[2].type = INPUT_MOUSE;
	input[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;
	input[2].mi.dx = 0;
	input[2].mi.dy = 0;
	input[2].mi.mouseData = 0;
	input[2].mi.time = 0;

	input[3].type = INPUT_MOUSE;
	input[3].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	input[3].mi.dx = p.x*(65536.0f/GetSystemMetrics(SM_CXSCREEN));
	input[3].mi.dy = p.y*(65536.0f/GetSystemMetrics(SM_CYSCREEN));
	input[3].mi.mouseData = 0;
	input[3].mi.time = 0;

	SendInput(4,input,sizeof(INPUT));
	cv::waitKey(0);*/




	return 0;
}
