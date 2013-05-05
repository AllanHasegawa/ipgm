#include <cstdint>

namespace ipgm {
	
	class IPGMCallbacks {
	public:
		virtual ~IPGMCallbacks() {
		}

		virtual void sensorON(const uint8_t ID) = 0;
		virtual void sensorOFF(const uint8_t ID) = 0;
		virtual void actuatorON(const uint8_t ID) = 0;
		virtual void actuatorOFF(const uint8_t ID) = 0;
	};
};