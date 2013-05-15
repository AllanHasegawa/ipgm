#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <future>
#include <array>

namespace ipgm {
	class IPGMCallbacks;
	class WindowManager;

	class IPGM {
	public:
		IPGM(const std::string PROCESS_NAME,
			const uint16_t POS_X, const uint16_t POS_Y,
			IPGMCallbacks& callbacks);
		virtual ~IPGM();

		void start();
		void stop();
		void activeActuator(const uint8_t ID);
		std::array<bool,11>& getSensorsInfo();
		std::array<bool,8>& getActuatorsInfo();
		std::shared_ptr<WindowManager> getWindowManager();
		
	private:
		std::shared_ptr<WindowManager> windowManager_;
		IPGMCallbacks& callbacks_;
		bool running_;
		std::future<void> ret_;
		std::array<bool,11> sensors_info_;
		std::array<bool,8> actuators_info_;
	};
};