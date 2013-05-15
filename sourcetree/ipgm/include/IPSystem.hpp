
#include <cstdint>
#include <array>
#include "opencv2\opencv.hpp"

namespace ipgm {

	class IPSystem {
	public:
		IPSystem();
		virtual ~IPSystem();

		void setSensorsSimilarityThreshould(const uint32_t T);
		void setActuatorsSimilarityThreshould(const uint32_t T);
		void processImage(const cv::Mat F, std::array<bool,11>& sensors, std::array<bool,8>& actuators);

	private:
		uint32_t sensor_similarity_;
		uint32_t actuator_similarity_;
		std::array<cv::Mat,11> sensors_mat_;
		std::array<cv::Mat,8> actuators_mat_;
		std::array<cv::Mat,4> f_rgb_;

		void segmentSingleSensorLED(const cv::Mat F, const uint8_t ID);
		void segmentSingleActuatorLED(const cv::Mat F, const uint8_t ID);
		bool detectSensorLED(const uint8_t ID);
		bool detectActuatorLED(const uint8_t ID);
	};

}