#include <stdarg.h>
#include <cstdio>
#include <memory>

#include "windows.h"

namespace ipgm {
	enum class LOG_LEVEL {
		RELEASE,
		INFO,
		DEBUG
	};

	class Log {
	private:
		struct _LCK {};

	public:
		static LOG_LEVEL log_level_;

		Log(const _LCK L) {
			AllocConsole();
			freopen( "CONOUT$", "wb", stdout);
		}

		virtual ~Log() {
			fclose( stdout );
			FreeConsole();
		}

		void dprintf(const char *str,...) {
			if (log_level_ == LOG_LEVEL::DEBUG) {
				va_list al;
				va_start(al,str);
				vprintf(str, al);
				va_end(al);
			}
		}

		void iprintf(const char *str,...) {
			if (log_level_ == LOG_LEVEL::INFO || log_level_ == LOG_LEVEL::DEBUG) {
				va_list al;
				va_start(al,str);
				vprintf(str, al);
				va_end(al);
			}
		}

		void rprintf(const char *str,...) {
			va_list al;
			va_start(al,str);
			vprintf(str, al);
			va_end(al);
		}

		void printf(const LOG_LEVEL ll, const char *str,...) {
			if (ll == LOG_LEVEL::DEBUG && log_level_ == LOG_LEVEL::RELEASE) {
				return;
			}
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