#pragma once

#ifdef VECTOR_PLATFORM_WINDOWS
	#ifdef VECTOR_BUILD_DLL
		#define VECTOR_API __declspec(dllexport)
	#else
		#define VECTOR_API __declspec(dllimport)
	#endif
#else
	#error Vector only supports Windows!
#endif

#ifdef VECTOR_DEBUG

#endif
