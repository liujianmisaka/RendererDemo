#pragma once

#include <vector>

namespace RendererDemo {

constexpr int KMouseButtonCount = 8;
constexpr int KKeyboardKeyCount = 1024;
constexpr int KWindowEventCount = 8;

// NOTE: RendererDemo event code is not is one enum class, and status space may not be used at some position.
struct EventStatus {
    std::vector<bool> mouse_status;
    std::vector<bool> keyboard_status;
    std::vector<bool> keyboard_repeat_status;
    std::vector<bool> window_status;

    EventStatus() {
        mouse_status.resize(KMouseButtonCount, false);
        keyboard_status.resize(KKeyboardKeyCount, false);
        keyboard_repeat_status.resize(KKeyboardKeyCount, false);
        window_status.resize(KWindowEventCount, false);
    }
};

} // namespace RendererDemo
