#pragma once

#include <cmath>
#include <algorithm>

namespace ooray {

    struct Vector2 {
        float x{ 0.0f };
        float y{ 0.0f };

        constexpr Vector2() = default;
        constexpr Vector2(float x, float y) : x(x), y(y) {}

        // Static Constructors
        [[nodiscard]] static constexpr Vector2 Zero() { return { 0.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector2 One()  { return { 1.0f, 1.0f }; }

        // Operators
        [[nodiscard]] constexpr Vector2 operator+(Vector2 rhs) const { return { x + rhs.x, y + rhs.y }; }
        [[nodiscard]] constexpr Vector2 operator-(Vector2 rhs) const { return { x - rhs.x, y - rhs.y }; }
        [[nodiscard]] constexpr Vector2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
        [[nodiscard]] constexpr Vector2 operator/(float scalar) const {
            const float inv = 1.0f / scalar;
            return { x * inv, y * inv };
        }

        constexpr Vector2& operator+=(Vector2 rhs) { x += rhs.x; y += rhs.y; return *this; }
        constexpr Vector2& operator-=(Vector2 rhs) { x -= rhs.x; y -= rhs.y; return *this; }
        constexpr Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
        constexpr Vector2& operator/=(float scalar) {
            const float inv = 1.0f / scalar;
            x *= inv; y *= inv;
            return *this;
        }

        [[nodiscard]] constexpr bool operator==(Vector2 rhs) const { return x == rhs.x && y == rhs.y; }
        [[nodiscard]] constexpr bool operator!=(Vector2 rhs) const { return !(*this == rhs); }

        // Basic Math
        [[nodiscard]] constexpr float Dot(Vector2 rhs) const { return (x * rhs.x) + (y * rhs.y); }
        [[nodiscard]] constexpr float LengthSqr() const { return Dot(*this); }
        [[nodiscard]] float Length() const { return std::hypot(x, y); }
        [[nodiscard]] constexpr Vector2 Negate() const { return { -x, -y }; }
        [[nodiscard]] constexpr Vector2 Invert() const { return { 1.0f / x, 1.0f / y }; }

        [[nodiscard]] float Distance(Vector2 v2) const { return (*this - v2).Length(); }
        [[nodiscard]] constexpr float DistanceSqr(Vector2 v2) const { return (*this - v2).LengthSqr(); }

        [[nodiscard]] Vector2 Normalized() const {
            const float len = Length();
            return (len > 0.0f) ? (*this * (1.0f / len)) : Zero();
        }

        // Trigonometric & Geometric Functions
        [[nodiscard]] float Angle(Vector2 v2) const {
            return std::atan2(v2.y, v2.x) - std::atan2(y, x);
        }

        [[nodiscard]] float LineAngle(Vector2 end) const {
            return std::atan2(end.y - y, end.x - x);
        }

        [[nodiscard]] Vector2 Rotate(float angle) const {
            const float cosA = std::cos(angle);
            const float sinA = std::sin(angle);
            return { x * cosA - y * sinA, x * sinA + y * cosA };
        }

        [[nodiscard]] constexpr Vector2 Lerp(Vector2 v2, float amount) const {
            return { std::lerp(x, v2.x, amount), std::lerp(y, v2.y, amount) };
        }

        [[nodiscard]] constexpr Vector2 Reflect(Vector2 normal) const {
            return *this - (normal * (2.0f * Dot(normal)));
        }

        [[nodiscard]] Vector2 Refract(Vector2 normal, float r) const {
            const float d = Dot(normal);
            const float k = 1.0f - r * r * (1.0f - d * d);
            if (k < 0.0f) return Zero();
            return (*this * r) - (normal * (r * d + std::sqrt(k)));
        }

        [[nodiscard]] Vector2 MoveTowards(Vector2 target, float maxDistance) const {
            const Vector2 delta = target - *this;
            const float sqrDist = delta.LengthSqr();
            if (sqrDist == 0.0f || (maxDistance >= 0.0f && sqrDist <= maxDistance * maxDistance)) {
                return target;
            }
            const float dist = std::sqrt(sqrDist);
            return *this + delta / dist * maxDistance;
        }

        // Clamping & Comparisons
        [[nodiscard]] constexpr Vector2 Clamp(Vector2 min, Vector2 max) const {
            return { std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y) };
        }

        [[nodiscard]] Vector2 ClampValue(float min, float max) const {
            const float len = Length();
            if (len == 0.0f) return Zero();
            const float clamped = std::clamp(len, min, max);
            return *this * (clamped / len);
        }

        [[nodiscard]] bool Equals(Vector2 q, float epsilon = 0.000001f) const {
            return (std::abs(x - q.x) <= epsilon) && (std::abs(y - q.y) <= epsilon);
        }
    };

}