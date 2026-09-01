#pragma once

#include <string>

namespace ooray {

    struct Window {
        Window(int width, int height, const std::string& title);
        ~Window();

        // Lifecycle & State
        [[nodiscard]] bool ShouldClose() const;
        [[nodiscard]] bool IsReady() const;
        [[nodiscard]] bool IsFullscreen() const;
        [[nodiscard]] bool IsHidden() const;
        [[nodiscard]] bool IsMinimized() const;
        [[nodiscard]] bool IsMaximized() const;
        [[nodiscard]] bool IsFocused() const;
        [[nodiscard]] bool IsResized() const;

        // Window Manipulation
        void SetTitle(const std::string& title);
        void SetPosition(int x, int y);
        void SetSize(int width, int height);
        void SetMinSize(int width, int height);
        void SetTargetFPS(int fps);
        void ToggleFullscreen();
        void Maximize();
        void Minimize();
        void Restore();

        // Drawing & Frame Control
        void ClearBackground(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        void BeginDrawing();
        void EndDrawing();

        // Metrics
        [[nodiscard]] int GetWidth() const;
        [[nodiscard]] int GetHeight() const;
        [[nodiscard]] int GetRenderWidth() const;
        [[nodiscard]] int GetRenderHeight() const;
        [[nodiscard]] float GetFrameTime() const;
        [[nodiscard]] double GetTime() const;
        [[nodiscard]] int GetFPS() const;

        // Cursor
        void ShowCursor();
        void HideCursor();
        [[nodiscard]] bool IsCursorHidden() const;
        void EnableCursor();
        void DisableCursor();
        [[nodiscard]] bool IsCursorOnScreen() const;
    };

}