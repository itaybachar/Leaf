#pragma once
#include <memory>
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

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
#define BIT(x) (1<<x)