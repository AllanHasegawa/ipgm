#include <string>
#include <cstdint>
#include <vector>
#include <mutex>

#include "opencv2\opencv.hpp"

namespace ipgm {

	class WindowManager {

	public:
		WindowManager(const std::string PROCESS_NAME,
			const uint16_t POS_X, const uint16_t POS_Y);
		virtual ~WindowManager();

		void update();
		std::vector<bool> getSensorsInfo();
		std::vector<bool> getActuatorsInfo();
		void activeActuator(const uint8_t ID);
		void copyLastFrame(cv::Mat& dst);

	private:
		const std::string PROCESS_NAME_;
		const uint16_t POS_X_;
		const uint16_t POS_Y_;
		std::vector<bool> sensorsInfo_;
		std::vector<bool> actuatorsInfo_;
		cv::Mat lastFrame_;
		mutable std::mutex frameCopyMutex_;
	};
};