#include <cstdint>
#include <chrono>

#include "windows.h"

namespace ipgm {

	struct KeyboardSystem {
		KeyboardSystem();
		virtual ~KeyboardSystem();

		void pressNumber(const uint8_t N);
		void setSleepTime(const uint32_t N);

	private:
		std::chrono::milliseconds sleep_time_;
		INPUT input_;
	};
}