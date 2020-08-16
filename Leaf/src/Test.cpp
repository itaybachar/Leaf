#include "Test.h"

namespace Leaf {
	__declspec(dllexport) void print()
	{
		printf("Hello Leaf");
	}
}