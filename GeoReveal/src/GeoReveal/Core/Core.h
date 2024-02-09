#pragma once

#include "CoreConfig.h"
#include "PlatformConfig.h"

#define GV_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define GV_BIT(x) (1 << x)
#define GV_CONCAT_INNER(a, b) a ## b
#define GV_CONCAT(a, b) GV_CONCAT_INNER(a, b)
#define GV_ENUM_TYPE uint16_t
#define GV_ENUM(name) enum class name : GV_ENUM_TYPE
#define GV_STRINGIFY(x) GV_MAKESTRING(x)
#define GV_MAKESTRING(x) #x

#ifdef GV_PLATFORM_WINDOWS
#define GV_DEBUGBREAK() __debugbreak()
#elif GV_PLATFORM_LINUX
#include <signal.h>
#define GV_DEBUGBREAK() raise(SIGTRAP)
#endif


#if GV_ENABLE_ASSERTS
	#define GV_ASSERT(x) {if(!(x)){GV_ERROR("Assertion {0} failed in {1} at line {2}", #x, __FILE__, __LINE__); GV_DEBUGBREAK(); } }
	#define GV_ASSERT_MSG(x, msg, ...) {if(!(x)){GV_ERROR(msg, __VA_ARGS__); GV_DEBUGBREAK(); } }
#elif GV_ENABLE_ASSERTS_ONLY_LOGGING
	#define GV_ASSERT(x) {if(!(x)){GV_ERROR("Assertion {0} failed in {1} at line {2}", #x, __FILE__, __LINE__); abort();  } }
	#define GV_ASSERT_MSG(x, msg, ...) {if(!(x)){GV_ERROR(msg, __VA_ARGS__); abort(); } }
#else
#define GV_ASSERT(x, ...)	
#endif // GV_ENABLE_ASSERT

#include <memory>

namespace GV {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> createScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "Logger.h"
#include "Utils.h"