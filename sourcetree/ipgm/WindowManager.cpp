#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include <windows.h>

#include "WindowManager.hpp"
#include "Log.hpp"

#include "opencv2\opencv.hpp"

#include "opencv-screen-capture\screenCapture.h"

namespace ipgm {

	WindowManager::WindowManager(const std::string PROCESS_NAME,
		const uint16_t POS_X, const uint16_t POS_Y)
		: PROCESS_NAME_(PROCESS_NAME), POS_X_(POS_X), POS_Y_(POS_Y) {

			cv::namedWindow( "D01", CV_WINDOW_AUTOSIZE );
			/*WindowCapture cap(hwnd_list.at(0));
			cv::Mat dst;
			cap.captureFrame(dst);

			//cv::namedWindow( "Display Image Copied", CV_WINDOW_AUTOSIZE );
			//cv::imshow( "Display Image Copied", dst );
			if (GetCursorPos(&p))
			{
			if (ScreenToClient(hwnd_list.at(0), &p))
			{
			std::cout << p.x << " / " << p.y << std::endl;
			}
			}
			}*/
	}

	WindowManager::~WindowManager() {
	}

	void WindowManager::update() {
		std::vector<HWND> hwnd_list;

		// TODO: REMOVE HARD_CODE
		// Process name is hard-coded ;)
		getHwndsByProcessName(L"ITS.PLC.PE.exe", hwnd_list, false);

		Log::instance()->printf("HWNDs found: %d\n", hwnd_list.size());

		if (hwnd_list.size() > 0) {
			HWND hwnd = hwnd_list.at(0);
			// TODO: REMOVE HARD_CODE
			// Window MUST be 800x600
			MoveWindow(hwnd, POS_X_, POS_Y_, 800, 600, true);

			WindowCapture cap(hwnd);
			cv::Mat dst;
			cap.captureFrame(dst);
			cv::imshow( "D01", dst );
		}
	}

	std::vector<bool> WindowManager::getSensorsInfo() {
		// Copy.
		return sensorsInfo_;
	}

	std::vector<bool> WindowManager::getActuatorsInfo() {
		return actuatorsInfo_;
	}

	void WindowManager::activeActuator(const uint8_t ID) {
	}
};