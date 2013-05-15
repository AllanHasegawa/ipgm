#include <array>
#include <cstdio>
#include "opencv2\opencv.hpp"

#include "Log.hpp"
#include "IPSystem.hpp"

namespace ipgm {


	IPSystem::IPSystem() : sensor_similarity_(10), actuator_similarity_(10) {
	}

	IPSystem::~IPSystem() {
	}

	void IPSystem::setSensorsSimilarityThreshould(const uint32_t T) {
		this->sensor_similarity_ = T;
	}

	void IPSystem::setActuatorsSimilarityThreshould(const uint32_t T) {
		this->actuator_similarity_ = T;
	}

	void IPSystem::processImage(const cv::Mat F, std::array<bool,11>& sensors, std::array<bool,8>& actuators) {
		using namespace cv;
		for (int i = 0; i < 11; i++) {
			segmentSingleSensorLED(F, i);
			sensors[i] = detectSensorLED(i);
		}
		for (int i = 0; i < 8; i++) {
			segmentSingleActuatorLED(F, i);
			actuators[i] = detectActuatorLED(i);
		}
	}

	void IPSystem::segmentSingleSensorLED(const cv::Mat F, const uint8_t ID) {
		// TODO: HARD CODES
		using namespace cv;
		uint32_t hs = 5;
		uint32_t ws = 13;
		uint32_t xi = 525;
		uint32_t yi = 94;
		uint32_t wss = 9;
		uint32_t xii = xi;
		uint32_t yii = yi+(uint32_t)ID*(wss+ws);
		//g = F[:,xii:xii+hs,yii:yii+ws];
		F(Rect(yii,xii,ws,hs)).copyTo(sensors_mat_[ID]);
	}

	void IPSystem::segmentSingleActuatorLED(const cv::Mat F, const uint8_t ID) {
		// TODO: HARD CODES
		using namespace cv;
		uint32_t hs = 7;
		uint32_t ws = 21;
		uint32_t xi = 560;
		uint32_t yi = 90;
		uint32_t wss = 1;
		uint32_t xii = xi;
		uint32_t yii = yi+(uint32_t)ID*(wss+ws);
		//g = F[:,xii:xii+hs,yii:yii+ws];
		F(Rect(yii,xii,ws,hs)).copyTo(actuators_mat_[ID]);
	}

	bool IPSystem::detectSensorLED(const uint8_t ID) {
		// TODO: It is detecting the mouse pointer
		using namespace cv;
		using namespace std;
		split(sensors_mat_[ID], f_rgb_.data());
		//led_l = mmsubm(led[0],led[2]) > 10\n",
		Mat g = (f_rgb_[2] - f_rgb_[0]) > 10;
		//"    return sum(led_l) > t\n",
		return sum(g)[0]/255. > sensor_similarity_;
	}

	bool IPSystem::detectActuatorLED(const uint8_t ID) {
		// TODO: It is detecting the mouse pointer
		using namespace cv;
		using namespace std;
		split(actuators_mat_[ID], f_rgb_.data());
		//led_l = mmsubm(led[0],led[2]) > 10\n",
		Mat g = (f_rgb_[2] - f_rgb_[0]) > 10;
		//"    return sum(led_l) > t\n",
		return sum(g)[0]/255. > actuator_similarity_;
	}
}