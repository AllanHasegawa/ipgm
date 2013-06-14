#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>
#include <memory>
#include <queue>
#include <mutex>
#include <array>

#include "AsyncSerial.h"
#include "BufferedAsyncSerial.h"

#include "IPGM.hpp"
#include "IPGMCallbacks.hpp"
#include "Log.hpp"

struct TI : public ipgm::IPGMCallbacks {
	TI(BufferedAsyncSerial* serial) : serial_(serial),
		buffer_sensors_count_(0) {
	}
	virtual ~TI() {
	}

	void sensorON(const uint8_t ID) {
		std::lock_guard<std::mutex> _lock(mutex_serial_);
		ipgm::Log::instance()->rprintf("SENSOR ON %u\n", ID);
		buffer_sensors_[buffer_sensors_count_++] = (char)(ID + 110);
	}
	void sensorOFF(const uint8_t ID) {
		std::lock_guard<std::mutex> _lock(mutex_serial_);
		ipgm::Log::instance()->rprintf("SENSOR OFF %u\n", ID);
		buffer_sensors_[buffer_sensors_count_++] = (char)(ID + 10);
	}
	void actuatorON(const uint8_t ID) {
		ipgm::Log::instance()->rprintf("ACT ON %u\n", ID);
	}
	void actuatorOFF(const uint8_t ID) {
		ipgm::Log::instance()->rprintf("ACT OFF %u\n", ID);
	}

	void update() {
		if (buffer_sensors_count_ > 0) {
			std::lock_guard<std::mutex> _lock(mutex_serial_);
			serial_->write(&buffer_sensors_[0], buffer_sensors_count_);
			buffer_sensors_count_ = 0;
		}
	}

private:
	BufferedAsyncSerial* serial_;
	std::array<char,1000> buffer_sensors_;
	int buffer_sensors_count_;
	std::mutex mutex_serial_;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	using namespace ipgm;
	using namespace std;

	Log::instance()->log_level_ = LOG_LEVEL::DEBUG;

	// initialize serial comm
	BufferedAsyncSerial* serial;

	try {
		serial = new BufferedAsyncSerial("COM2", 9600);
	} catch (boost::system::system_error& e) {
		Log::instance()->rprintf("Error opening serial COMM\n");
	}

	TI ti(serial);
	IPGM ipgm(L"ITS.PLC.PE.exe", ti);

	ipgm.start();

	std::chrono::milliseconds dura( 1 );
	std::array<char,1000> buffer_actuators;
	
	int ready_chars_received = 0;
	while (ready_chars_received < 4) {
		char buffer;
		if (serial->read(&buffer,1) == 1) {
			if ((unsigned char)buffer == 255) {
				ready_chars_received++;
			}
		}
	}


	while (true) {
		std::this_thread::sleep_for( dura );

		ti.update();

		int n_read = serial->read(&buffer_actuators[0],1000);

		if (n_read > 0) {
			Log::instance()->dprintf("N: %d\n", n_read);
			for (int i = 0; i < n_read; i++) {
				unsigned char c = (unsigned char)buffer_actuators[i];
				if (c < 30 || c > 137 || (c > 37 && c < 130)) {
					continue;
				}
				Log::instance()->dprintf("C: %d\n", c);
				bool turn_on = c > 100;
				if (turn_on) {
					c -= 130;
					bool state = ipgm.getActuatorsInfo()[c];
					if (!state) {
						try {
							Log::instance()->dprintf("Activating %d\n", c);
							ipgm.activeActuator(c);
						} catch (std::exception& e) {
							Log::instance()->rprintf("ERROR: %s\n", e.what());
						}
					}
				} else {
					c -= 30;
					bool state = ipgm.getActuatorsInfo()[c];
					if (state) {
						try {
							Log::instance()->dprintf("DE-Activating %d\n", c);
							ipgm.activeActuator(c);
						} catch (std::exception& e) {
							Log::instance()->rprintf("ERROR: %s\n", e.what());
						}
					}
				}
			}
		}
	}

	// cleaning up ;)
	serial->close();
	delete serial;
	ipgm.stop();
	return 0;
}
