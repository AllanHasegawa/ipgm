#include <stdarg.h>
#include <cstdio>
#include <memory>

#include "windows.h"

namespace ipgm {

	class Log {
	private:
		struct _LCK {};

	public:
		Log(const _LCK L) {
			AllocConsole();
			freopen( "CONOUT$", "wb", stdout);
		}

		virtual ~Log() {
			fclose( stdout );
			FreeConsole();
		}

		void printf(const char *str,...) {
			va_list al;
			va_start(al,str);
			vprintf(str, al);
			va_end(al);
		}

		static std::shared_ptr<ipgm::Log> instance() {
			static std::shared_ptr<Log> log_ = std::make_shared<Log>(_LCK());
			return log_;
		}
	};

}