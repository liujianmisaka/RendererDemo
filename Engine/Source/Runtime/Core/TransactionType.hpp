#pragma once

namespace RendererDemo {

enum class TransactionType {
    None = 0,
    // clang-format off
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    // clang-format on
};

}
