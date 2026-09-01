#include "ooray.hpp"
#include <raylib.h>

namespace ooray {

#pragma region Window

    Window::Window(int width, int height, const std::string& title) {
        ::InitWindow(width, height, title.c_str());
    }

    Window::~Window() {
        ::CloseWindow();
    }

    // Lifecycle & State
    bool Window::ShouldClose() const {
        return ::WindowShouldClose();
    }

    bool Window::IsReady() const {
        return ::IsWindowReady();
    }

    bool Window::IsFullscreen() const {
        return ::IsWindowFullscreen();
    }

    bool Window::IsHidden() const {
        return ::IsWindowHidden();
    }

    bool Window::IsMinimized() const {
        return ::IsWindowMinimized();
    }

    bool Window::IsMaximized() const {
        return ::IsWindowMaximized();
    }

    bool Window::IsFocused() const {
        return ::IsWindowFocused();
    }

    bool Window::IsResized() const {
        return ::IsWindowResized();
    }

    // Window Manipulation
    void Window::SetTitle(const std::string& title) {
        ::SetWindowTitle(title.c_str());
    }

    void Window::SetPosition(int x, int y) {
        ::SetWindowPosition(x, y);
    }

    void Window::SetSize(int width, int height) {
        ::SetWindowSize(width, height);
    }

    void Window::SetMinSize(int width, int height) {
        ::SetWindowMinSize(width, height);
    }

    void Window::SetTargetFPS(int fps) {
        ::SetTargetFPS(fps);
    }

    void Window::ToggleFullscreen() {
        ::ToggleFullscreen();
    }

    void Window::Maximize() {
        ::MaximizeWindow();
    }

    void Window::Minimize() {
        ::MinimizeWindow();
    }

    void Window::Restore() {
        ::RestoreWindow();
    }

    // Drawing & Frame Control
    void Window::ClearBackground(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        ::ClearBackground(Color{ r, g, b, a });
    }

    void Window::BeginDrawing() {
        ::BeginDrawing();
    }

    void Window::EndDrawing() {
        ::EndDrawing();
    }

    // Metrics
    int Window::GetWidth() const {
        return ::GetScreenWidth();
    }

    int Window::GetHeight() const {
        return ::GetScreenHeight();
    }

    int Window::GetRenderWidth() const {
        return ::GetRenderWidth();
    }

    int Window::GetRenderHeight() const {
        return ::GetRenderHeight();
    }

    float Window::GetFrameTime() const {
        return ::GetFrameTime();
    }

    double Window::GetTime() const {
        return ::GetTime();
    }

    int Window::GetFPS() const {
        return ::GetFPS();
    }

    // Cursor
    void Window::ShowCursor() {
        ::ShowCursor();
    }

    void Window::HideCursor() {
        ::HideCursor();
    }

    bool Window::IsCursorHidden() const {
        return ::IsCursorHidden();
    }

    void Window::EnableCursor() {
        ::EnableCursor();
    }

    void Window::DisableCursor() {
        ::DisableCursor();
    }

    bool Window::IsCursorOnScreen() const {
        return ::IsCursorOnScreen();
    }

#pragma endregion

}