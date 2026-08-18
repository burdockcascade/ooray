#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <concepts>
#include <ostream>

namespace ooray {

    class Vector3 : public ::Vector3 {
    public:
        // Constructors
        constexpr Vector3() noexcept : ::Vector3{0.0f, 0.0f, 0.0f} {}
        constexpr Vector3(float val) noexcept : ::Vector3{val, val, val} {}
        constexpr Vector3(float x_, float y_, float z_) noexcept : ::Vector3{x_, y_, z_} {}
        constexpr Vector3(const ::Vector3& vec) noexcept : ::Vector3{vec.x, vec.y, vec.z} {}

        // Implicit conversion back to Raylib's C struct for seamless API interoperability
        constexpr operator ::Vector3() const noexcept { return {x, y, z}; }

        // Static Utility Constructors
        [[nodiscard]] static constexpr Vector3 Zero() noexcept { return {0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 One() noexcept { return {1.0f, 1.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector3 Up() noexcept { return {0.0f, 1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Down() noexcept { return {0.0f, -1.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Left() noexcept { return {-1.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Right() noexcept { return {1.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector3 Forward() noexcept { return {0.0f, 0.0f, 1.0f}; }
        [[nodiscard]] static constexpr Vector3 Back() noexcept { return {0.0f, 0.0f, -1.0f}; }

        // Vector Operations (Const Methods)
        [[nodiscard]] float Length() const noexcept { return Vector3Length(*this); }
        [[nodiscard]] float LengthSqr() const noexcept { return Vector3LengthSqr(*this); }
        [[nodiscard]] float Distance(Vector3 other) const noexcept { return Vector3Distance(*this, other); }
        [[nodiscard]] float DistanceSqr(Vector3 other) const noexcept { return Vector3DistanceSqr(*this, other); }
        [[nodiscard]] float Angle(Vector3 other) const noexcept { return Vector3Angle(*this, other); }

        [[nodiscard]] Vector3 Normalized() const noexcept { return Vector3Normalize(*this); }
        [[nodiscard]] Vector3 Lerp(Vector3 target, float amount) const noexcept { return Vector3Lerp(*this, target, amount); }
        [[nodiscard]] Vector3 Clamp(Vector3 min, Vector3 max) const noexcept { return Vector3Clamp(*this, min, max); }

        [[nodiscard]] float Dot(Vector3 other) const noexcept { return Vector3DotProduct(*this, other); }
        [[nodiscard]] Vector3 Cross(Vector3 other) const noexcept { return Vector3CrossProduct(*this, other); }

        // In-place Mutating Methods
        Vector3& Normalize() noexcept { *this = Normalized(); return *this; }

        // Operator Overloads
        constexpr Vector3 operator+(Vector3 rhs) const noexcept { return Vector3Add(*this, rhs); }
        constexpr Vector3 operator-(Vector3 rhs) const noexcept { return Vector3Subtract(*this, rhs); }
        constexpr Vector3 operator*(Vector3 rhs) const noexcept { return Vector3Multiply(*this, rhs); }
        constexpr Vector3 operator*(float scalar) const noexcept { return Vector3Scale(*this, scalar); }
        constexpr Vector3 operator/(Vector3 rhs) const noexcept { return Vector3Divide(*this, rhs); }
        constexpr Vector3 operator/(float scalar) const noexcept { return Vector3Scale(*this, 1.0f / scalar); }
        constexpr Vector3 operator-() const noexcept { return Vector3Negate(*this); }

        constexpr Vector3& operator+=(Vector3 rhs) noexcept { *this = *this + rhs; return *this; }
        constexpr Vector3& operator-=(Vector3 rhs) noexcept { *this = *this - rhs; return *this; }
        constexpr Vector3& operator*=(Vector3 rhs) noexcept { *this = *this * rhs; return *this; }
        constexpr Vector3& operator*=(float scalar) noexcept { *this = *this * scalar; return *this; }
        constexpr Vector3& operator/=(Vector3 rhs) noexcept { *this = *this / rhs; return *this; }
        constexpr Vector3& operator/=(float scalar) noexcept { *this = *this / scalar; return *this; }

        // default equality operator
        bool operator==(const Vector3& rhs) const noexcept = default;

        // Stream operator for easy printing
        friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
            return os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
        }
    };

    // Global scalar multiplication overload (e.g., 2.0f * vec)
    constexpr Vector3 operator*(float scalar, Vector3 vec) noexcept {
        return vec * scalar;
    }

} // namespace ooray