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

#define BIT(x) (1<<x)