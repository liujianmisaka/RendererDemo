#pragma once

#include <functional>
#include <vector>

namespace RendererDemo {

// 通用的委托类
template <typename... Args>
class Delegate {
public:
    using FunctionType = std::function<void(Args...)>;

    void Add(FunctionType func);        // 添加回调函数
    void Remove(FunctionType func);     // 移除回调函数
    void Broadcast(Args... args) const; // 触发委托

private:
    std::vector<FunctionType> functions;
};

// template must be completed in declaration
template <typename... Args>
void Delegate<Args...>::Add(FunctionType func) {
    functions.push_back(std::move(func));
}

// template must be completed in declaration
template <typename... Args>
void Delegate<Args...>::Remove(FunctionType func) {
    auto it = std::remove(functions.begin(), functions.end(), func);
    functions.erase(it, functions.end());
}

// template must be completed in declaration
template <typename... Args>
void Delegate<Args...>::Broadcast(Args... args) const {
    for (const auto& func : functions) {
        func(args...);
    }
}

} // namespace RendererDemo
