#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>

#include "boost\asio.hpp"

#include "IPGM.hpp"
#include "IPGMCallbacks.hpp"
#include "Log.hpp"


class TI : public ipgm::IPGMCallbacks {
public:
	TI() {
	}
	virtual ~TI() {
	}

	void sensorON(const uint8_t ID) {
		ipgm::Log::instance()->rprintf("SENSOR ON %u\n", ID);
	}
	void sensorOFF(const uint8_t ID) {
		ipgm::Log::instance()->rprintf("SENSOR OFF %u\n", ID);
	}
	void actuatorON(const uint8_t ID) {
		ipgm::Log::instance()->rprintf("ACT ON %u\n", ID);
	}
	void actuatorOFF(const uint8_t ID) {
		ipgm::Log::instance()->rprintf("ACT OFF %u\n", ID);
	}
};

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow) {
	using namespace ipgm;

	Log::instance()->log_level_ = LOG_LEVEL::DEBUG;

	TI ti;
	IPGM ipgm(L"ITS.PLC.PE.exe", ti);
	
	ipgm.start();
	
	int actuator = 0;
	while (true) {
		std::chrono::milliseconds dura( 1000 );
		std::this_thread::sleep_for( dura );

		try {
			ipgm.activeActuator(actuator++);
		} catch (std::exception& e) {
			Log::instance()->rprintf("ERROR: %s\n", e.what());
		}
		if (actuator > 6) {
			actuator = 0;
		}
	}

	ipgm.stop();
	return 0;
}
