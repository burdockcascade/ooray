#pragma once

#include <cmath>
#include <algorithm>

namespace ooray {

    struct Vector4 {
        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };
        float w{ 0.0f };

        constexpr Vector4() = default;
        constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        // Static Constructors
        [[nodiscard]] static constexpr Vector4 Zero() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector4 One()  { return { 1.0f, 1.0f, 1.0f, 1.0f }; }

        // Operators
        [[nodiscard]] constexpr Vector4 operator+(Vector4 rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w }; }
        [[nodiscard]] constexpr Vector4 operator-(Vector4 rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w }; }
        [[nodiscard]] constexpr Vector4 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar, w * scalar }; }
        [[nodiscard]] constexpr Vector4 operator*(Vector4 rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w }; }
        [[nodiscard]] constexpr Vector4 operator/(float scalar) const {
            const float inv = 1.0f / scalar;
            return { x * inv, y * inv, z * inv, w * inv };
        }
        [[nodiscard]] constexpr Vector4 operator/(Vector4 rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w }; }

        constexpr Vector4& operator+=(Vector4 rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
        constexpr Vector4& operator-=(Vector4 rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
        constexpr Vector4& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
        constexpr Vector4& operator*=(Vector4 rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
        constexpr Vector4& operator/=(float scalar) {
            const float inv = 1.0f / scalar;
            x *= inv; y *= inv; z *= inv; w *= inv;
            return *this;
        }
        constexpr Vector4& operator/=(Vector4 rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w; return *this; }

        [[nodiscard]] constexpr bool operator==(Vector4 rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w; }
        [[nodiscard]] constexpr bool operator!=(Vector4 rhs) const { return !(*this == rhs); }

        // Basic Math
        [[nodiscard]] constexpr float Dot(Vector4 rhs) const { return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w); }
        [[nodiscard]] constexpr float LengthSqr() const { return Dot(*this); }
        [[nodiscard]] float Length() const { return std::sqrt(LengthSqr()); }
        [[nodiscard]] constexpr Vector4 Negate() const { return { -x, -y, -z, -w }; }
        [[nodiscard]] constexpr Vector4 Invert() const { return { 1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w }; }

        [[nodiscard]] float Distance(Vector4 v2) const { return (*this - v2).Length(); }
        [[nodiscard]] constexpr float DistanceSqr(Vector4 v2) const { return (*this - v2).LengthSqr(); }

        [[nodiscard]] Vector4 Normalized() const {
            const float len = Length();
            return (len > 0.0f) ? (*this * (1.0f / len)) : Zero();
        }

        [[nodiscard]] constexpr Vector4 Lerp(Vector4 v2, float amount) const {
            return {
                std::lerp(x, v2.x, amount),
                std::lerp(y, v2.y, amount),
                std::lerp(z, v2.z, amount),
                std::lerp(w, v2.w, amount)
            };
        }

        [[nodiscard]] Vector4 MoveTowards(Vector4 target, float maxDistance) const {
            const Vector4 delta = target - *this;
            const float sqrDist = delta.LengthSqr();
            if (sqrDist == 0.0f || (maxDistance >= 0.0f && sqrDist <= maxDistance * maxDistance)) {
                return target;
            }
            const float dist = std::sqrt(sqrDist);
            return *this + delta / dist * maxDistance;
        }

        // Clamping & Comparisons
        [[nodiscard]] constexpr Vector4 Clamp(Vector4 min, Vector4 max) const {
            return {
                std::clamp(x, min.x, max.x),
                std::clamp(y, min.y, max.y),
                std::clamp(z, min.z, max.z),
                std::clamp(w, min.w, max.w)
            };
        }

        [[nodiscard]] Vector4 ClampValue(float min, float max) const {
            const float len = Length();
            if (len == 0.0f) return Zero();
            const float clamped = std::clamp(len, min, max);
            return *this * (clamped / len);
        }

        [[nodiscard]] bool Equals(Vector4 q, float epsilon = 0.000001f) const {
            return (std::abs(x - q.x) <= epsilon) &&
                   (std::abs(y - q.y) <= epsilon) &&
                   (std::abs(z - q.z) <= epsilon) &&
                   (std::abs(w - q.w) <= epsilon);
        }
    };

    // Alias following Raylib naming convention
    using Quaternion = Vector4;

}