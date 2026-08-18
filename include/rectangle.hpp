#pragma once

#include <raylib.h>
#include <raymath.h>
#include <concepts>
#include <ostream>

#include "vector2.hpp"

namespace ooray {

    class Rectangle : public ::Rectangle {
    public:
        // Constructors
        constexpr Rectangle() noexcept : ::Rectangle{0.0f, 0.0f, 0.0f, 0.0f} {}
        constexpr Rectangle(float x_, float y_, float width_, float height_) noexcept: ::Rectangle{x_, y_, width_, height_} {}
        constexpr Rectangle(Vector2 position, Vector2 size) noexcept: ::Rectangle{position.x, position.y, size.x, size.y} {}
        constexpr Rectangle(const ::Rectangle& rect) noexcept: ::Rectangle{rect.x, rect.y, rect.width, rect.height} {}

        // Implicit conversion back to Raylib's C struct for seamless API interoperability
        constexpr operator ::Rectangle() const noexcept { return {x, y, width, height}; }

        // Position & Size Getters/Setters as Vector2
        [[nodiscard]] constexpr Vector2 Position() const noexcept { return {x, y}; }
        constexpr void SetPosition(Vector2 pos) noexcept { x = pos.x; y = pos.y; }

        [[nodiscard]] constexpr Vector2 Size() const noexcept { return {width, height}; }
        constexpr void SetSize(Vector2 size) noexcept { width = size.x; height = size.y; }

        // Helper Getters for Edges & Center
        [[nodiscard]] constexpr float Left() const noexcept { return x; }
        [[nodiscard]] constexpr float Right() const noexcept { return x + width; }
        [[nodiscard]] constexpr float Top() const noexcept { return y; }
        [[nodiscard]] constexpr float Bottom() const noexcept { return y + height; }
        [[nodiscard]] constexpr Vector2 Center() const noexcept { return {x + width * 0.5f, y + height * 0.5f}; }

        // Collision Checks
        [[nodiscard]] bool Contains(Vector2 point) const noexcept {
            return CheckCollisionPointRec(point, *this);
        }

        [[nodiscard]] bool Overlaps(Rectangle other) const noexcept {
            return CheckCollisionRecs(*this, other);
        }

        [[nodiscard]] Rectangle GetCollision(Rectangle other) const noexcept {
            return GetCollisionRec(*this, other);
        }

        // Default equality operator
        bool operator==(const Rectangle& rhs) const noexcept {
            return x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height;
        }

        // Stream operator for easy printing
        friend std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
            return os << "Rectangle(" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << ")";
        }
    };

} // namespace ooray