#include <string>
#include <cstdint>
#include <vector>
#include <future>

#include "IPGM.hpp"
#include "IPGMCallbacks.hpp"
#include "WindowManager.hpp"

ipgm::IPGM::IPGM(const std::wstring PROCESS_NAME,
				 const uint16_t POS_X, const uint16_t POS_Y,
				 ipgm::IPGMCallbacks& callbacks)
				 : callbacks_(callbacks), running_(true)
{
	sensors_info_.fill(false);
	actuators_info_.fill(false);
	windowManager_ = std::make_shared<WindowManager>(PROCESS_NAME, POS_X, POS_Y);
}

ipgm::IPGM::~IPGM() {
}

void ipgm::IPGM::start() {
	ret_ = std::async(std::launch::async, [this]{
		std::array<bool,11> t_sensors;
		t_sensors.fill(false);
		std::array<bool,8> t_actuators;
		t_actuators.fill(false);
		while (this->running_) {
			windowManager_->update(t_sensors, t_actuators);
			for (int i = 0; i < 11; i++) {
				if (t_sensors[i] != this->sensors_info_[i]) {
					if (t_sensors[i]) {
						this->callbacks_.sensorON(i);
					} else {
						this->callbacks_.sensorOFF(i);
					}
					this->sensors_info_[i] = t_sensors[i];
				}
			}
			for (int i = 0; i < 8; i++) {
				if (t_actuators[i] != this->actuators_info_[i]) {
					if (t_actuators[i]) {
						this->callbacks_.actuatorON(i);
					} else {
						this->callbacks_.actuatorOFF(i);
					}
					this->actuators_info_[i] = t_actuators[i];
				}
			}
		}
	});
}

void ipgm::IPGM::stop() {
	this->running_ = false;
	ret_.wait();
}

void ipgm::IPGM::activeActuator(const uint8_t ID) {
	this->windowManager_->activeActuator(ID);
}

std::array<bool,11>& ipgm::IPGM::getSensorsInfo() {
	return sensors_info_;
}

std::array<bool,8>& ipgm::IPGM::getActuatorsInfo() {
	return actuators_info_;
}

std::shared_ptr<ipgm::WindowManager> ipgm::IPGM::getWindowManager() {
	return windowManager_;
}