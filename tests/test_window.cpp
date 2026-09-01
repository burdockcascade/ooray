#include <catch2/catch_test_macros.hpp>
#include "ooray.hpp"
#include <raylib.h>

TEST_CASE("Window lifecycle and property tests", "[window]") {
    SetConfigFlags(FLAG_WINDOW_HIDDEN);

    constexpr int testWidth = 640;
    constexpr int testHeight = 480;
    const std::string testTitle = "Catch2 Test Window";

    ooray::Window window(testWidth, testHeight, testTitle);

    SECTION("Initialization checks") {
        REQUIRE(window.IsReady() == true);
        REQUIRE(window.ShouldClose() == false);
        REQUIRE(window.GetWidth() == testWidth);
        REQUIRE(window.GetHeight() == testHeight);
        REQUIRE(window.IsHidden() == true);
    }

    SECTION("Window resizing and dimension updates") {
        constexpr int newWidth = 800;
        constexpr int newHeight = 600;

        window.SetSize(newWidth, newHeight);

        REQUIRE(window.GetWidth() == newWidth);
        REQUIRE(window.GetHeight() == newHeight);
    }

    SECTION("Cursor visibility controls") {
        window.HideCursor();
        REQUIRE(window.IsCursorHidden() == true);

        window.ShowCursor();
        REQUIRE(window.IsCursorHidden() == false);
    }

    SECTION("Render cycle execution") {
        REQUIRE_NOTHROW([&]() {
            window.BeginDrawing();
            window.ClearBackground(255, 0, 0);
            window.EndDrawing();
        }());
    }
}