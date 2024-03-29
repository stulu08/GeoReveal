#pragma once
#define USING_GLFW 1
#define OPENGL 1

#if OPENGL == 0
	#define VULKAN
	#undef OPENGL
#else
	#define IMGUI_OPENGL_4 1
#endif

#ifdef GV_DEBUG
	#define GV_ENABLE_ASSERTS 1
	#define GV_ENABLE_ASSERTS_ONLY_LOGGING 1
	#define	GV_ENABLE_TRACE_LOGGING 1

	#define GV_GRAPHICS_API_DEBUG_LOGGING 1
	#define GV_GRAPHICS_API_INFO_LOGGING 0 // GL_DEBUG_SEVERITY_LOW | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
	#define GV_GRAPHICS_API_VERBOSE_LOGGING 0 // GL_DEBUG_SEVERITY_NOTIFICATION | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
#elif GV_RELEASE
	#define GV_GRAPHICS_API_DEBUG_LOGGING 1
	#define GV_ENABLE_ASSERTS 1

#elif GV_DIST
	#define GV_ENABLE_ASSERTS_ONLY_LOGGING 1
#endif