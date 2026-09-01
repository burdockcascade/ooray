#include <ooray.hpp>

int main() {

    ooray::Window window{800, 600, "Basic Window Example"};

    while (!window.ShouldClose()) {
        window.BeginDrawing();
        window.ClearBackground(255, 255, 255);
        window.EndDrawing();
    }

}