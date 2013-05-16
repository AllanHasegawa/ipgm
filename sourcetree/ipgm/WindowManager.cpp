#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <array>
#include <thread>

#include <windows.h>

#include "WindowManager.hpp"
#include "Log.hpp"

#include "opencv2\opencv.hpp"

#include "opencv-screen-capture\screenCapture.h"

namespace ipgm {

	WindowManager::WindowManager(const std::wstring PROCESS_NAME)
		: ipsystem_(), keyboardsystem_(),
		PROCESS_NAME_(PROCESS_NAME),
		lastFrame_(0, 0, CV_8U) {
	}

	WindowManager::~WindowManager() {
	}

	void WindowManager::update(std::array<bool,11>& sensors_info, std::array<bool,8>& actuators_info) {
		std::vector<HWND> hwnd_list;
		getHwndsByProcessName(this->PROCESS_NAME_.c_str(), hwnd_list, false);

		if (hwnd_list.size() > 0) {
			HWND hwnd = hwnd_list.at(0);
			{
				std::lock_guard<std::mutex> lock(frameCopyMutex_);
				try {
					// TODO: Capture frame is capturing the ENTIRE window. ROI will be problaby faster
					captureWindow(hwnd, lastFrame_, false);
					this->ipsystem_.processImage(lastFrame_, sensors_info, actuators_info);
				} catch (std::exception& e) {
				}
			}
		}
	}

	void WindowManager::activeActuator(const uint8_t ID) {
		std::vector<HWND> hwnd_list;
		getHwndsByProcessName(this->PROCESS_NAME_.c_str(), hwnd_list, false);
		if (hwnd_list.empty()) {
			throw std::exception("Window not found");
		}
		HWND window = hwnd_list[0];

		revealWindow(window);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		this->keyboardsystem_.pressNumber(ID);
	}

	void WindowManager::copyLastFrame(cv::Mat& dst) {
		std::lock_guard<std::mutex> lock(frameCopyMutex_);
		lastFrame_.copyTo(dst);
	}
};