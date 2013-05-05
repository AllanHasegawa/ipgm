#include <string>
#include <cstdint>
#include <vector>

#include "IPGM.hpp"
#include "IPGMCallbacks.hpp"
#include "WindowManager.hpp"

ipgm::IPGM::IPGM(const std::string PROCESS_NAME,
				 const uint16_t POS_X, const uint16_t POS_Y,
				 ipgm::IPGMCallbacks& callbacks)
				 : callbacks_(callbacks)
{
	windowManager_ = std::make_shared<WindowManager>(PROCESS_NAME, POS_X, POS_Y);
}

ipgm::IPGM::~IPGM() {
}

void ipgm::IPGM::start() {
	while (true) {
		windowManager_->update();
	}
}

void ipgm::IPGM::activeActuator(const uint8_t ID) {
}

std::vector<bool>& ipgm::IPGM::getSensorsInfo() {
	std::vector<bool> v;
	return v;
}

std::vector<bool>& ipgm::IPGM::getActuatorsInfo() {
	std::vector<bool> v;
	return v;
}