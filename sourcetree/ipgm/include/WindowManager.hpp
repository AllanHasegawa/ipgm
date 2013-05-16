#include <string>
#include <cstdint>
#include <vector>
#include <mutex>
#include <array>

#include "opencv2\opencv.hpp"

#include "IPSystem.hpp"
#include "KeyboardSystem.hpp"

namespace ipgm {

	struct WindowManager {

		WindowManager(const std::wstring PROCESS_NAME);
		virtual ~WindowManager();

		void update(std::array<bool,11>& sensors_info, std::array<bool,8>& actuators_info);
		void activeActuator(const uint8_t ID);
		void copyLastFrame(cv::Mat& dst);

	private:
		IPSystem ipsystem_;
		KeyboardSystem keyboardsystem_;
		const std::wstring PROCESS_NAME_;
		cv::Mat lastFrame_;
		mutable std::mutex frameCopyMutex_;
	};
};