#pragma once
#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/basic_file_sink.h>

#ifdef GV_PLATFORM_ANDROID
#include <spdlog/sinks/android_sink.h>
#endif

namespace GV {
	enum class LogLevel {
		Trace = SPDLOG_LEVEL_TRACE,
		Debug = SPDLOG_LEVEL_DEBUG,
		Info = SPDLOG_LEVEL_INFO,
		Warn = SPDLOG_LEVEL_WARN,
		Error = SPDLOG_LEVEL_ERROR,
		Critical = SPDLOG_LEVEL_CRITICAL,
		Off = SPDLOG_LEVEL_OFF
	};

	class Logger {
	public:
		template<class SinkType = spdlog::sinks::stdout_color_sink_mt, class ...SinkArgs>
		static inline Ref<Logger> Create(const std::string& name, SinkArgs&&... sinkargs) {
			return createRef<Logger>(createRef<spdlog::logger>(name, createRef<SinkType>(std::forward<SinkArgs>(sinkargs)...)));
		}

		Logger(const Ref<spdlog::logger>& logger)
			: m_logger(logger) {
			if (!m_logger)
				return;

			spdlog::details::registry::instance().initialize_logger(m_logger);
			m_logger->set_pattern("%^[%T][%n]: %v%$");
			m_logger->flush_on(spdlog::level::trace);
			m_logger->set_level(spdlog::level::trace);
		}
		~Logger() {
			if (m_logger) {
				m_logger->flush();
			}
		}

		const Ref<spdlog::logger>& getLogger() const {
			return m_logger;
		}

		template<typename FormatString, typename... Args>
		void Trace(const FormatString& fmt, Args &&...args) {
			m_logger->trace(fmt, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args>
		void Info(const FormatString& fmt, Args &&...args) {
			m_logger->info(fmt, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args>
		void Warn(const FormatString& fmt, Args &&...args) {
			m_logger->warn(fmt, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args>
		void Error(const FormatString& fmt, Args &&...args) {
			m_logger->error(fmt, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args>
		void Critical(const FormatString& fmt, Args &&...args) {
			m_logger->critical(fmt, std::forward<Args>(args)...);
		}
		template<typename FormatString, typename... Args>
		void Log(LogLevel level, const FormatString& fmt, Args &&...args) {
			m_logger->log((spdlog::level::level_enum)level, fmt, std::forward<Args>(args)...);
		}
		template<typename T>
		void Trace(const T& msg) {
			m_logger->trace<T>(msg);
		}
		template<typename T>
		void Info(const T& msg) {
			m_logger->info<T>(msg);
		}
		template<typename T>
		void Warn(const T& msg) {
			m_logger->warn<T>(msg);
		}
		template<typename T>
		void Error(const T& msg) {
			m_logger->error<T>(msg);
		}
		template<typename T>
		void Critical(const T& msg) {
			m_logger->critical<T>(msg);
		}
		template<typename T>
		void Log(LogLevel level, const T& msg) {
			m_logger->log<T>((spdlog::level::level_enum)level, msg);
		}
	private:
		Ref<spdlog::logger> m_logger;
	};

	class Log {
	public:
		static inline void Init(){
			s_coreLogger = Logger::Create<spdlog::sinks::stdout_color_sink_mt>("Core");
			s_gfxLogger = Logger::Create<spdlog::sinks::stdout_color_sink_mt>("GFX");
		}

		template <typename ...Args>
		static inline void GFXTrace(const std::string& format, Args&& ...args) {
#ifdef GV_ENABLE_TRACE_LOGGING
			s_gfxLogger->Trace(format, std::forward<Args>(args)...);
#endif
		}
		template <typename ...Args>
		static inline void GFXInfo(const std::string& format, Args&& ...args) {
			s_gfxLogger->Info(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void GFXWarn(const std::string& format, Args&& ...args) {
			s_gfxLogger->Warn(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void GFXError(const std::string& format, Args&& ...args) {
			s_gfxLogger->Error(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void GFXCritical(const std::string& format, Args&& ...args) {
			s_gfxLogger->Critical(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void Trace(const std::string& format, Args&& ...args) {
#ifdef GV_ENABLE_TRACE_LOGGING
			s_coreLogger->Trace(format, std::forward<Args>(args)...);
#endif
		}
		template <typename ...Args>
		static inline void Info(const std::string& format, Args&& ...args) {
			s_coreLogger->Info(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void Warn(const std::string& format, Args&& ...args) {
			s_coreLogger->Warn(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void Error(const std::string& format, Args&& ...args) {
			s_coreLogger->Error(format, std::forward<Args>(args)...);
		}
		template <typename ...Args>
		static inline void Critical(const std::string& format, Args&& ...args) {
			s_coreLogger->Critical(format, std::forward<Args>(args)...);
		}
		static Ref<Logger> getCoreLogger() { return s_coreLogger; }
		static Ref<Logger> getGFXLogger() { return s_gfxLogger; }
	private:
		static inline Ref<Logger> s_coreLogger;
		static inline Ref<Logger> s_gfxLogger;
	};

	#define GV_CRITICAL(msg, ...) ::GV::Log::Critical(msg, __VA_ARGS__)
	#define GV_ERROR(msg, ...) ::GV::Log::Error(msg, __VA_ARGS__)
	#define GV_WARN(msg, ...) ::GV::Log::Warn(msg, __VA_ARGS__)
	#define GV_INFO(msg, ...) ::GV::Log::Info(msg, __VA_ARGS__)
	#define GV_TRACE(msg, ...) ::GV::Log::Trace(msg, __VA_ARGS__)

	#define GV_GFX_CRITICAL(msg, ...) ::GV::Log::GFXCritical(msg, __VA_ARGS__)
	#define GV_GFX_ERROR(msg, ...) ::GV::Log::GFXError(msg, __VA_ARGS__)
	#define GV_GFX_WARN(msg, ...) ::GV::Log::GFXWarn(msg, __VA_ARGS__)
	#define GV_GFX_INFO(msg, ...) ::GV::Log::GFXInfo(msg, __VA_ARGS__)
	#define GV_GFX_TRACE(msg, ...) ::GV::Log::GFXTrace(msg, __VA_ARGS__)
}