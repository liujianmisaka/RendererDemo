#include "Misaka/Event/TransactionType.hpp"
#include "Misaka/Event/Delegate.hpp"


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


// // 事件委托
// class EventDelegate {
// public:
//     // 事务处理函数类型
//     using TransactionHandler = std::function<void(std::shared_ptr<Event>)>;

//     // 添加事务处理函数
//     template <typename T>
//     void AddHandler(TransactionType type, void (T::*handler)(std::shared_ptr<T>)) {
//         handlers_[type] = [this, handler](std::shared_ptr<Event> event) {
//             // 尝试进行 dynamic_cast
//             if (auto castedEvent = std::dynamic_pointer_cast<T>(event)) {
//                 // 如果转换成功，调用处理函数
//                 (castedEvent.get()->*handler)(castedEvent);
//             }
//         };
//     }

//     // 触发事务
//     void TriggerTransaction(TransactionType type, std::shared_ptr<Event> event) {
//         auto it = handlers_.find(type);
//         if (it != handlers_.end()) {
//             // 调用注册的处理函数
//             it->second(event);
//         }
//     }

// private:
//     // 存储处理函数的映射
//     std::unordered_map<TransactionType, TransactionHandler> handlers_;
// };

} // namespace RendererDemo