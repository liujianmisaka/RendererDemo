#define LOG_HELPER(LOG_LEVEL, ...) g_runtime_context.m_log_system->log(LOG_LEVEL, "[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__);
#define LOG_DEBUG(...) LOG_HELPER(LogSystem::LogLevel::debug, __VA_ARGS__);
#define LOG_INFO(...) LOG_HELPER(LogSystem::LogLevel::info, __VA_ARGS__);
#define LOG_WARN(...) LOG_HELPER(LogSystem::LogLevel::warn, __VA_ARGS__);
#define LOG_ERROR(...) LOG_HELPER(LogSystem::LogLevel::error, __VA_ARGS__);
#define LOG_FATAL(...) LOG_HELPER(LogSystem::LogLevel::fatal, __VA_ARGS__);
