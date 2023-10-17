#include <functional>
#include <vector>


namespace RendererDemo {

// 通用的委托类
template <typename... Args>
class Delegate {
public:
    using FunctionType = std::function<void(Args...)>;

    // 添加回调函数
    void Add(FunctionType func) { functions.push_back(std::move(func)); }

    // 移除回调函数
    void Remove(FunctionType func) {
        auto it = std::remove(functions.begin(), functions.end(), func);
        functions.erase(it, functions.end());
    }

    // 触发委托
    void Broadcast(Args... args) const {
        for (const auto& func : functions) {
            func(args...);
        }
    }

private:
    std::vector<FunctionType> functions;
};

} // namespace RendererDemo