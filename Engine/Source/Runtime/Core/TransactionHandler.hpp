#include "Runtime/Core/TransactionType.hpp"
#include "Runtime/Core/Delegate.hpp"

namespace RendererDemo {

// 事务处理器类
class TransactionHandler {
public:
    // 添加事务处理函数
    template <typename... Args>
    void AddHandler(TransactionType transactionType, typename Delegate<Args...>::FunctionType handler) {
        // 如果事务类型不存在，则创建新的委托
        if (handlers.find(transactionType) == handlers.end()) {
            handlers[transactionType] = Delegate<Args...>();
        }
        handlers[transactionType].Add(std::move(handler));
    }

    // 移除事务处理函数
    template <typename... Args>
    void RemoveHandler(TransactionType transactionType, typename Delegate<Args...>::FunctionType handler) {
        auto it = handlers.find(transactionType);
        if (it != handlers.end()) {
            it->second.Remove(std::move(handler));
        }
    }

    // 处理事务
    template <typename... Args>
    void ProcessTransaction(TransactionType transactionType, Args... args) {
        auto it = handlers.find(transactionType);
        if (it != handlers.end()) {
            it->second.Broadcast(args...);
        }
    }

private:
    std::unordered_map<TransactionType, Delegate<>> handlers;
};

} // namespace RendererDemo
