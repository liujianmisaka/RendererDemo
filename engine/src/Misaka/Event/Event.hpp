
namespace RendererDemo {

// 事件基类
class Event {
public:
    virtual ~Event() = default;

    virtual void EventHandler() = 0;
};



} // namespace RendererDemo