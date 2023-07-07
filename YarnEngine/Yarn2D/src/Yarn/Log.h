#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Yarn {

	// Logging system in Yarn has 2 loggers.
	// CoreLogger is used to log all the Engine related Logs.
	// ClientLogger is for the Yarn Applications

	class YARN_API Log
	{
	public:
		static void init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;

	};

}

// 4 different type of log messages supported in Yarn are
// TRACE, INFO, WARN, ERROR

// Core log macros
#define YARN_CORE_TRACE(...)    ::Yarn::Log::getCoreLogger()->trace(__VA_ARGS__)
#define YARN_CORE_INFO(...)     ::Yarn::Log::getCoreLogger()->info(__VA_ARGS__)
#define YARN_CORE_WARN(...)     ::Yarn::Log::getCoreLogger()->warn(__VA_ARGS__)
#define YARN_CORE_ERROR(...)    ::Yarn::Log::getCoreLogger()->error(__VA_ARGS__)
#define YARN_CORE_CRITICAL(...) ::Yarn::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define YARN_TRACE(...)    ::Yarn::Log::getClientLogger()->trace(__VA_ARGS__)
#define YARN_INFO(...)     ::Yarn::Log::getClientLogger()->info(__VA_ARGS__)
#define YARN_WARN(...)     ::Yarn::Log::getClientLogger()->warn(__VA_ARGS__)
#define YARN_ERROR(...)    ::Yarn::Log::getClientLogger()->error(__VA_ARGS__)
#define YARN_CRITICAL(...) ::Yarn::Log::getClientLogger()->critical(__VA_ARGS__)

//	RESET_COLOR,
//	BLACK_TXT = 30,
//	RED_TXT,
//	GREEN_TXT,
//	YELLOW_TXT,
//	BLUE_TXT,
//	MAGENTA_TXT,
//	CYAN_TXT,
//	WHITE_TXT,
//
//	BLACK_BKG = 40,
//	RED_BKG,
//	GREEN_BKG,
//	YELLOW_BKG,
//	BLUE_BKG,
//	MAGENTA_BKG,
//	CYAN_BKG,
//	WHITE_BKG
// 
//#define TRACE(msg) printf("\x1b[37m%s\n\x1b[0m", msg);
//#define INFO(msg)  printf("\x1b[32m%s\n\x1b[0m", msg);
//#define WARN(msg)  printf("\x1b[33m%s\n\x1b[0m", msg);
//#define ERROR(msg) printf("\x1b[31m%s\n\x1b[0m", msg);
//#define FATAL(msg) printf("\x1b[41m%s\n\x1b[0m", msg);
