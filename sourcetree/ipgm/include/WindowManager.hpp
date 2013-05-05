#include <string>
#include <cstdint>
#include <vector>

namespace ipgm {

	class WindowManager {

	public:
		WindowManager(const std::string PROCESS_NAME,
			const uint16_t POS_X, const uint16_t POS_Y);
		virtual ~WindowManager();

		void update();
		std::vector<bool> getSensorsInfo();
		std::vector<bool> getActuatorsInfo();
		void activeActuator(const uint8_t ID);

	private:
		const std::string PROCESS_NAME_;
		const uint16_t POS_X_;
		const uint16_t POS_Y_;
		std::vector<bool> sensorsInfo_;
		std::vector<bool> actuatorsInfo_;
	};
};