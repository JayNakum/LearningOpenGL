#pragma once

// Here dll import and export are handled by the macro
// the engine defines YARN_BUILD_DLL
// 
// Any class starting with YARN_API will be exported into the dll

#ifdef YARN_PLATFORM_WINDOWS
	#ifdef YARN_BUILD_DLL
		#define YARN_API __declspec(dllexport)
	#else
		#define YARN_API __declspec(dllimport)
	#endif
#else
	#error Yarn only supports Windows!
#endif

#ifdef YARN_DEBUG
#define YARN_ENABLE_ASSERTS
#endif

#ifdef YARN_ENABLE_ASSERTS
	#define YARN_ASSERT(x, ...) { if(!(x)) { YARN_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define YARN_CORE_ASSERT(x, ...) { if(!(x)) { YARN_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define YARN_ASSERT(x, ...)
	#define YARN_CORE_ASSERT(x, ...)
#endif // YARN_ENABLE_ASSERTS


// BIT() is used for Event Flags
// it basically generates a binary number for which every bit acts as a flag
#define BIT(x) (1 << x)

#define YARN_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)