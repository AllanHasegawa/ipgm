#include <string>
#include <cstdint>
#include <vector>
#include <memory>

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
		void activeActuator(const uint8_t ID);
		std::vector<bool>& getSensorsInfo();
		std::vector<bool>& getActuatorsInfo();
		
	private:
		std::shared_ptr<WindowManager> windowManager_;
		IPGMCallbacks& callbacks_;
	};
};