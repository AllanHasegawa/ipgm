#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>

#include "opencv2/opencv.hpp"

#include "IPGM.hpp";
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
				   int nCmdShow)
{
	using namespace ipgm;

	Log::instance()->log_level_ = LOG_LEVEL::RELEASE;

	TI ti;
	IPGM ipgm("", 0, 0, ti);
	
	ipgm.start();
	
	while (true) {
		std::chrono::milliseconds dura( 2000 );
		std::this_thread::sleep_for( dura );
	}

	ipgm.stop();
	return 0;
}
