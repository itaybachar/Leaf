#pragma once

namespace Leaf {
	class Timestep {
	public:
		Timestep(float time) 
			: m_Time(time) {}

		operator float() const { return m_Time; }

		float GetTime() const { return m_Time; }
		float GetTimeMili() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}