#pragma once
#include "lfpch.h"

#include "Leaf/Core/Application.h"
#include "Leaf/Core/Inputs.h"

#include <GLFW/glfw3.h>

namespace Leaf {

	bool Inputs::IsKeyPressed(int keycode) {
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window,keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Inputs::IsMouseButtonPressed(int button) {
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Inputs::GetMousePos() {
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}

	float Inputs::GetMouseX() {
		auto [x, y] = Inputs::GetMousePos();
		return x;
	}

	float Inputs::GetMouseY() {
		auto [x, y] = Inputs::GetMousePos();
		return y;
	}
}