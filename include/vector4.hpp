#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <concepts>
#include <ostream>

namespace ooray {

    class Vector4 : public ::Vector4 {
    public:
        // Constructors
        constexpr Vector4() noexcept : ::Vector4{0.0f, 0.0f, 0.0f, 0.0f} {}
        constexpr Vector4(float val) noexcept : ::Vector4{val, val, val, val} {}
        constexpr Vector4(float x_, float y_, float z_, float w_) noexcept : ::Vector4{x_, y_, z_, w_} {}
        constexpr Vector4(const ::Vector4& vec) noexcept : ::Vector4{vec.x, vec.y, vec.z, vec.w} {}

        // Implicit conversion back to Raylib's C struct for seamless API interoperability
        constexpr operator ::Vector4() const noexcept { return {x, y, z, w}; }

        // Static Utility Constructors
        [[nodiscard]] static constexpr Vector4 Zero() noexcept { return {0.0f, 0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector4 One() noexcept { return {1.0f, 1.0f, 1.0f, 1.0f}; }

        // Vector Operations (Const Methods)
        [[nodiscard]] float Length() const noexcept { return Vector4Length(*this); }
        [[nodiscard]] float LengthSqr() const noexcept { return Vector4LengthSqr(*this); }
        [[nodiscard]] float Distance(Vector4 other) const noexcept { return Vector4Distance(*this, other); }
        [[nodiscard]] float DistanceSqr(Vector4 other) const noexcept { return Vector4DistanceSqr(*this, other); }

        [[nodiscard]] Vector4 Normalized() const noexcept { return Vector4Normalize(*this); }
        [[nodiscard]] Vector4 Lerp(Vector4 target, float amount) const noexcept { return Vector4Lerp(*this, target, amount); }

        [[nodiscard]] float Dot(Vector4 other) const noexcept { return Vector4DotProduct(*this, other); }

        // In-place Mutating Methods
        Vector4& Normalize() noexcept { *this = Normalized(); return *this; }

        // Operator Overloads
        constexpr Vector4 operator+(Vector4 rhs) const noexcept { return Vector4Add(*this, rhs); }
        constexpr Vector4 operator-(Vector4 rhs) const noexcept { return Vector4Subtract(*this, rhs); }
        constexpr Vector4 operator*(Vector4 rhs) const noexcept { return Vector4Multiply(*this, rhs); }
        constexpr Vector4 operator*(float scalar) const noexcept { return Vector4Scale(*this, scalar); }
        constexpr Vector4 operator/(Vector4 rhs) const noexcept { return Vector4Divide(*this, rhs); }
        constexpr Vector4 operator/(float scalar) const noexcept { return Vector4Scale(*this, 1.0f / scalar); }
        constexpr Vector4 operator-() const noexcept { return Vector4Negate(*this); }

        constexpr Vector4& operator+=(Vector4 rhs) noexcept { *this = *this + rhs; return *this; }
        constexpr Vector4& operator-=(Vector4 rhs) noexcept { *this = *this - rhs; return *this; }
        constexpr Vector4& operator*=(Vector4 rhs) noexcept { *this = *this * rhs; return *this; }
        constexpr Vector4& operator*=(float scalar) noexcept { *this = *this * scalar; return *this; }
        constexpr Vector4& operator/=(Vector4 rhs) noexcept { *this = *this / rhs; return *this; }
        constexpr Vector4& operator/=(float scalar) noexcept { *this = *this / scalar; return *this; }

        // default equality operator
        bool operator==(const Vector4& rhs) const noexcept = default;

        // Stream operator for easy printing
        friend std::ostream& operator<<(std::ostream& os, const Vector4& v) {
            return os << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
        }
    };

    // Global scalar multiplication overload (e.g., 2.0f * vec)
    constexpr Vector4 operator*(float scalar, Vector4 vec) noexcept {
        return vec * scalar;
    }

} // namespace ooray