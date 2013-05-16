#include <utility>
#include <cstdint>
#include <exception>
#include <thread>
#include <chrono>

#include "MouseSystem.hpp"

namespace ipgm {

	MouseSystem::MouseSystem() {
	}

	MouseSystem::~MouseSystem() {
	}

	void MouseSystem::click() {
		
		memset(input_list_.data(), 0, sizeof(INPUT));
		input_list_[0].type = INPUT_MOUSE;
		input_list_[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		input_list_[0].mi.dx = 0;
		input_list_[0].mi.dy = 0;
		input_list_[0].mi.mouseData = 0;
		input_list_[0].mi.time = 0;

		// TODO: WAY TOO INEFICIENT. Maybe inject input msgs direct into the process?
		SendInput(1, input_list_.data(), sizeof(INPUT));
		std::chrono::milliseconds dura( 20 );
		std::this_thread::sleep_for( dura );

		memset(input_list_.data(), 0, sizeof(INPUT));
		input_list_[0].type = INPUT_MOUSE;
		input_list_[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		input_list_[0].mi.dx = 0;
		input_list_[0].mi.dy = 0;
		input_list_[0].mi.mouseData = 0;
		input_list_[0].mi.time = 0;
		
		SendInput(1, input_list_.data(), sizeof(INPUT));
		std::this_thread::sleep_for( dura );
	}

	void MouseSystem::moveTo(const std::pair<long, long> POS) {
		memset(input_list_.data(), 0, sizeof(INPUT)*4);

		input_list_[0].type = INPUT_MOUSE;
		input_list_[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		input_list_[0].mi.dx = POS.first*(65536.0f/GetSystemMetrics(SM_CXSCREEN));
		input_list_[0].mi.dy = POS.second*(65536.0f/GetSystemMetrics(SM_CYSCREEN));
		input_list_[0].mi.mouseData = 0;
		input_list_[0].mi.time = 0;

		SendInput(1, input_list_.data(), sizeof(INPUT));
	}

	std::pair<long, long> MouseSystem::getPosition() {

		if (GetCursorPos(&point_)) {
			return std::pair<long,long>(point_.x,point_.y);
		} else {
			throw new std::exception("Error with GetCursorPos");
		}
	}

	
	void MouseSystem::clickAndBack(const std::pair<long, long> POS) {
		auto oldPos = getPosition();
		moveTo(POS);
		click();
		moveTo(oldPos);
	}
}