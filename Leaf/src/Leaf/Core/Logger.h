#pragma once
#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Leaf {
	class LEAF_API Logger
	{
	public:
		static void InitLogger();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return  s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return  s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Defines for logger macros
#define LF_CORE_TRACE(...) Leaf::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LF_CORE_INFO(...) Leaf::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LF_CORE_WARN(...) Leaf::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LF_CORE_ERROR(...) Leaf::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LF_CORE_CRITICAL(...) Leaf::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define LF_TRACE(...) Leaf::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define LF_INFO(...) Leaf::Logger::GetClientLogger()->info(__VA_ARGS__)
#define LF_WARN(...) Leaf::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define LF_ERROR(...) Leaf::Logger::GetClientLogger()->error(__VA_ARGS__)
#define LF_CRITICAL(...) Leaf::Logger::GetClientLogger()->critical(__VA_ARGS__)
