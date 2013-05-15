#include <string>
#include <cstdint>
#include <vector>
#include <mutex>
#include <array>

#include "opencv2\opencv.hpp"

#include "IPSystem.hpp"
#include "MouseSystem.hpp"

namespace ipgm {

	struct WindowManager {

		WindowManager(const std::string PROCESS_NAME,
			const uint16_t POS_X, const uint16_t POS_Y);
		virtual ~WindowManager();

		void update(std::array<bool,11>& sensors_info, std::array<bool,8>& actuators_info);
		void activeActuator(const uint8_t ID);
		void copyLastFrame(cv::Mat& dst);

	private:
		IPSystem ipsystem_;
		MouseSystem mousesystem_;
		const std::string PROCESS_NAME_;
		const uint16_t POS_X_;
		const uint16_t POS_Y_;
		cv::Mat lastFrame_;
		mutable std::mutex frameCopyMutex_;
	};
};