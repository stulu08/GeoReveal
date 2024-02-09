#pragma once
#ifdef _WIN32
	#ifdef _WIN64
		#define GV_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define GV_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define GV_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define GV_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define GV_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif
#ifdef _WIN32
	#if GV_DYNAMIC_LINK
		#ifdef GV_DLL_BUILD
			#define GV_API __declspec(dllexport)
		#else
			#define GV_API __declspec(dllimport)
		#endif // GV_DLL_BUILD
	#else
		#define GV_STATIC_BUILD
		#define GV_API
	#endif
#else
	#error Only Winodws is currently supported in Stulu
#endif // GV_PLATFORM_WINDOWS