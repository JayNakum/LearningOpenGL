#include "YarnPCH.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Yarn {
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	// [init()] initializes CoreLogger and ClientLogger
	// And sets spdlog with a specific pattern 
	// Here the pattern is [TimeStamp] CORE/CLIENT : Log Message
	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("YARN");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("APP");
		s_clientLogger->set_level(spdlog::level::trace);
	}
}