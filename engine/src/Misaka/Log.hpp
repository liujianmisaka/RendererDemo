#pragma once

// This ignores all warnings raised inside External headers
#include <memory>
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)
#include <glm/gtx/string_cast.hpp>


namespace RendererDemo {

    class Log {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector) {
    return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix) {
    return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion) {
    return os << glm::to_string(quaternion);
}

// Core log macros
#define LOGGER_CORE_TRACE(...)    ::RendererDemo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOGGER_CORE_INFO(...)     ::RendererDemo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOGGER_CORE_WARN(...)     ::RendererDemo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOGGER_CORE_ERROR(...)    ::RendererDemo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOGGER_CORE_CRITICAL(...) ::RendererDemo::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define LOGGER_TRACE(...)         ::RendererDemo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOGGER_INFO(...)          ::RendererDemo::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOGGER_WARN(...)          ::RendererDemo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOGGER_ERROR(...)         ::RendererDemo::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOGGER_CRITICAL(...)      ::RendererDemo::Log::GetClientLogger()->critical(__VA_ARGS__)
