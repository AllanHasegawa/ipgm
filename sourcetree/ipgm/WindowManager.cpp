#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <array>
#include <windows.h>

#include "WindowManager.hpp"
#include "Log.hpp"

#include "opencv2\opencv.hpp"

#include "opencv-screen-capture\screenCapture.h"

namespace ipgm {

	WindowManager::WindowManager(const std::string PROCESS_NAME,
		const uint16_t POS_X, const uint16_t POS_Y)
		: ipsystem_(), PROCESS_NAME_(PROCESS_NAME), POS_X_(POS_X), POS_Y_(POS_Y), lastFrame_(10, 10, CV_8U) {

			//cv::namedWindow( "D01", CV_WINDOW_AUTOSIZE );
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

	void WindowManager::update(std::array<bool,11>& sensors_info, std::array<bool,8>& actuators_info) {
		std::vector<HWND> hwnd_list;

		// TODO: REMOVE HARD_CODE
		// Process name is hard-coded ;)
		getHwndsByProcessName(L"ITS.PLC.PE.exe", hwnd_list, false);

		Log::instance()->dprintf("HWNDs found: %d\n", hwnd_list.size());

		if (hwnd_list.size() > 0) {
			HWND hwnd = hwnd_list.at(0);
			// TODO: REMOVE HARD_CODE
			// Window MUST be 800x600
			//MoveWindow(hwnd, POS_X_, POS_Y_, 800, 600, true);
			
			WindowCapture cap(hwnd);
			{
				std::lock_guard<std::mutex> lock(frameCopyMutex_);
				try {
					// TODO: Capture frame is capturing the ENTIRE window. ROI is a lot smaller
					cap.captureFrame(lastFrame_);
					this->ipsystem_.processImage(lastFrame_, sensors_info, actuators_info);
				} catch (std::exception& e) {
				}
			}
		}
	}

	void WindowManager::activeActuator(const uint8_t ID) {
	}

	void WindowManager::copyLastFrame(cv::Mat& dst) {
		std::lock_guard<std::mutex> lock(frameCopyMutex_);
		lastFrame_.copyTo(dst);
	}
};