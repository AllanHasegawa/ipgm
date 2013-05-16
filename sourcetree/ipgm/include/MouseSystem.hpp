#include <utility>
#include <cstdint>
#include <array>

#include "windows.h"

namespace ipgm {

	struct MouseSystem {

		MouseSystem();
		virtual ~MouseSystem();

		void click();
		void moveTo(const std::pair<long, long> POS);
		std::pair<long, long> getPosition();
		void clickAndBack(const std::pair<long, long> POS);

	private:
		std::array<INPUT,20> input_list_;
		POINT point_;
	};

}