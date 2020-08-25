#include "lfpch.h"
#include "Leaf/Core/Platform.h"

#include <GLFW/glfw3.h>

namespace Leaf {
	float Platform::GetTime() {
		return (float)glfwGetTime();
	}
}