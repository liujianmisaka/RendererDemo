#include <functional>
#include <GLFW/glfw3.h>
#include "Runtime/Core/Handler/Delegate.hpp"

namespace RendererDemo {

enum class TransactionType {
    None = 0,
    // clang-format off
    WindowClose, WindowResize, 
	// WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased, KeyRepeated, 
	KeyTyped,   // Char
    MouseButtonPressed, MouseButtonReleased, 
	MouseMoved, MouseScrolled
    // clang-format on
};

// 事务处理器类
class TransactionHandler {
public:
    // 添加事务处理函数
    template <typename... Args>
    void AddHandler(TransactionType transactionType, typename std::function<void(Args...)> handler);

    // 移除事务处理函数
    template <typename... Args>
    void RemoveHandler(TransactionType transactionType, typename Delegate<Args...>::FunctionType handler);

    // 处理事务
    template <typename... Args>
    void ProcessTransaction(TransactionType transactionType, Args &&...args);

private:
    std::unordered_map<TransactionType, Delegate<>> handlers;
};

// template must be completed in declaration
template <typename... Args>
void TransactionHandler::AddHandler(TransactionType transactionType, typename std::function<void(Args...)> handler) {
    if (handlers.find(transactionType) == handlers.end()) {
        handlers[transactionType] = Delegate<Args...>();
    }
    handlers[transactionType].Add(std::move(handler));
}

// template must be completed in declaration
template <typename... Args>
void TransactionHandler::RemoveHandler(TransactionType transactionType, typename Delegate<Args...>::FunctionType handler) {
    auto it = handlers.find(transactionType);
    if (it != handlers.end()) {
        it->second.Remove(std::move(handler));
    }
}

// template must be completed in declaration
template <typename... Args>
void TransactionHandler::ProcessTransaction(TransactionType transactionType, Args &&...args) {
    auto it = handlers.find(transactionType);
    if (it != handlers.end()) {
        it->second.Broadcast(std::forward<Args>(args)...);
    }
}

} // namespace RendererDemo
