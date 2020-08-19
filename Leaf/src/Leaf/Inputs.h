#pragma once
#include "Leaf/Core.h"

namespace Leaf {
	
	class LEAF_API Inputs {
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos();
		static float GetMouseX();
		static float GetMouseY();
	};
}