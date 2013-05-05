#include <iostream>
#include <vector>

#include <windows.h>

#include "opencv2/opencv.hpp"

#include "opencv-screen-capture/screenCapture.h"
#include "Log.hpp"


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	using namespace ipgm;
	
	Log::instance();

	std::vector<HWND> hwnd_list;

	getHwndsByProcessName(L"ITS.PLC.PE.exe", hwnd_list, false);

	//std::cout << "HWND: " <<  hwnd_list.size() << std::endl;
	Log::instance()->printf("HWND: %d\n", hwnd_list.size());

	cv::Mat image;
	image = cv::imread("lena.jpg", 1);

	cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Display Image", image );

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
	if (hwnd_list.size() > 0) {
		WindowCapture cap(hwnd_list.at(0));
		cv::Mat dst;
		cap.captureFrame(dst);

		cv::namedWindow( "Display Image Copied", CV_WINDOW_AUTOSIZE );
		cv::imshow( "Display Image Copied", dst );
		if (GetCursorPos(&p))
		{
			if (ScreenToClient(hwnd_list.at(0), &p))
			{
				std::cout << p.x << " / " << p.y << std::endl;
			}
		}
	}

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
	cv::waitKey(0);


	

	return 0;
}
