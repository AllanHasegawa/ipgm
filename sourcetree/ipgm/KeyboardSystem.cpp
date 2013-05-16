#include <chrono>
#include <thread>

#include "KeyboardSystem.hpp"

namespace ipgm {

	KeyboardSystem::KeyboardSystem() : sleep_time_(30) {
	}

	KeyboardSystem::~KeyboardSystem() {
	}

	void KeyboardSystem::pressNumber(const uint8_t N) {
		memset(&input_, 0, sizeof(INPUT));
		input_.type = INPUT_KEYBOARD;
		input_.ki.dwFlags = 0;
		input_.ki.wVk = 0x30 + N;
		SendInput(1, &input_, sizeof(INPUT));

		std::this_thread::sleep_for(this->sleep_time_);
		memset(&input_, 0, sizeof(INPUT));
		input_.type = INPUT_KEYBOARD;
		input_.ki.dwFlags = KEYEVENTF_KEYUP;
		input_.ki.wVk = 0x30 + N;
		SendInput(1, &input_, sizeof(INPUT));
		std::this_thread::sleep_for(this->sleep_time_);
	}

	void KeyboardSystem::setSleepTime(const uint32_t N) {
		this->sleep_time_ = std::chrono::milliseconds(N);
	}
}