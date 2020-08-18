#pragma once

#ifdef LF_PLATFORM_WINDOWS
	#ifdef LF_BUILD_DLL
		#define LEAF_API __declspec(dllexport)
	#else
		#define LEAF_API __declspec(dllimport)
	#endif
#else
	#error Leaf only supports Windows!
#endif

#ifdef LF_ASSERTS
	#define LF_CORE_ASSERT(x, ...) if(!(x)) { LF_CORE_CRITICAL(__VA_ARGS__); __debugbreak(); }
	#define LF_ASSERT(x, ...) if(!(x)) { LF_CRITICAL(__VA_ARGS__); __debugbreak(); }
#else
	#define LF_CORE_ASSERT(x, ...)
	#define LF_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)