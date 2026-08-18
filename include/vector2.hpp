#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <concepts>
#include <ostream>

namespace ooray {

    class Vector2 : public ::Vector2 {
    public:
        // Constructors
        constexpr Vector2() noexcept : ::Vector2{0.0f, 0.0f} {}
        constexpr Vector2(float val) noexcept : ::Vector2{val, val} {}
        constexpr Vector2(float x_, float y_) noexcept : ::Vector2{x_, y_} {}
        constexpr Vector2(const ::Vector2& vec) noexcept : ::Vector2{vec.x, vec.y} {}

        // Implicit conversion back to Raylib's C struct for seamless API interoperability
        constexpr operator ::Vector2() const noexcept { return {x, y}; }

        // Static Utility Constructors
        [[nodiscard]] static constexpr Vector2 Zero() noexcept { return {0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector2 One() noexcept { return {1.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector2 Up() noexcept { return {0.0f, -1.0f}; }
        [[nodiscard]] static constexpr Vector2 Down() noexcept { return {0.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector2 Left() noexcept { return {-1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector2 Right() noexcept { return {1.0f, 0.0f}; }

        // Vector Operations (Const Methods)
        [[nodiscard]] float Length() const noexcept { return Vector2Length(*this); }
        [[nodiscard]] float LengthSqr() const noexcept { return Vector2LengthSqr(*this); }
        [[nodiscard]] float Distance(Vector2 other) const noexcept { return Vector2Distance(*this, other); }
        [[nodiscard]] float DistanceSqr(Vector2 other) const noexcept { return Vector2DistanceSqr(*this, other); }
        [[nodiscard]] float Angle(Vector2 other) const noexcept { return Vector2Angle(*this, other); }

        [[nodiscard]] Vector2 Normalized() const noexcept { return Vector2Normalize(*this); }
        [[nodiscard]] Vector2 Rotated(float angleRad) const noexcept { return Vector2Rotate(*this, angleRad); }
        [[nodiscard]] Vector2 Lerp(Vector2 target, float amount) const noexcept { return Vector2Lerp(*this, target, amount); }
        [[nodiscard]] Vector2 Clamp(Vector2 min, Vector2 max) const noexcept { return Vector2Clamp(*this, min, max); }

        [[nodiscard]] float Dot(Vector2 other) const noexcept { return Vector2DotProduct(*this, other); }
        [[nodiscard]] float Cross(Vector2 other) const noexcept { return Vector2CrossProduct(*this, other); }

        // In-place Mutating Methods
        Vector2& Normalize() noexcept { *this = Normalized(); return *this; }
        Vector2& Rotate(float angleRad) noexcept { *this = Rotated(angleRad); return *this; }

        // Operator Overloads
        constexpr Vector2 operator+(Vector2 rhs) const noexcept { return Vector2Add(*this, rhs); }
        constexpr Vector2 operator-(Vector2 rhs) const noexcept { return Vector2Subtract(*this, rhs); }
        constexpr Vector2 operator*(Vector2 rhs) const noexcept { return Vector2Multiply(*this, rhs); }
        constexpr Vector2 operator*(float scalar) const noexcept { return Vector2Scale(*this, scalar); }
        constexpr Vector2 operator/(Vector2 rhs) const noexcept { return Vector2Divide(*this, rhs); }
        constexpr Vector2 operator/(float scalar) const noexcept { return Vector2Scale(*this, 1.0f / scalar); }
        constexpr Vector2 operator-() const noexcept { return Vector2Negate(*this); }

        constexpr Vector2& operator+=(Vector2 rhs) noexcept { *this = *this + rhs; return *this; }
        constexpr Vector2& operator-=(Vector2 rhs) noexcept { *this = *this - rhs; return *this; }
        constexpr Vector2& operator*=(Vector2 rhs) noexcept { *this = *this * rhs; return *this; }
        constexpr Vector2& operator*=(float scalar) noexcept { *this = *this * scalar; return *this; }
        constexpr Vector2& operator/=(Vector2 rhs) noexcept { *this = *this / rhs; return *this; }
        constexpr Vector2& operator/=(float scalar) noexcept { *this = *this / scalar; return *this; }

        // default equality operator
        bool operator==(const Vector2& rhs) const noexcept = default;

        // Stream operator for easy printing
        friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
            return os << "Vector2(" << v.x << ", " << v.y << ")";
        }
    };

    // Global scalar multiplication overload (e.g., 2.0f * vec)
    constexpr Vector2 operator*(float scalar, Vector2 vec) noexcept {
        return vec * scalar;
    }

} // namespace rl