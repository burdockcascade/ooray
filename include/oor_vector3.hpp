#pragma once

#include <cmath>
#include <algorithm>

namespace ooray {

    struct Vector3 {
        float x{ 0.0f };
        float y{ 0.0f };
        float z{ 0.0f };

        constexpr Vector3() = default;
        constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        // Static Constructors
        [[nodiscard]] static constexpr Vector3 Zero()    { return { 0.0f, 0.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector3 One()     { return { 1.0f, 1.0f, 1.0f }; }
        [[nodiscard]] static constexpr Vector3 Up()      { return { 0.0f, 1.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector3 Down()    { return { 0.0f, -1.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector3 Left()    { return { -1.0f, 0.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector3 Right()   { return { 1.0f, 0.0f, 0.0f }; }
        [[nodiscard]] static constexpr Vector3 Forward() { return { 0.0f, 0.0f, 1.0f }; }
        [[nodiscard]] static constexpr Vector3 Back()    { return { 0.0f, 0.0f, -1.0f }; }

        // Operators
        [[nodiscard]] constexpr Vector3 operator+(Vector3 rhs) const { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
        [[nodiscard]] constexpr Vector3 operator-(Vector3 rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
        [[nodiscard]] constexpr Vector3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
        [[nodiscard]] constexpr Vector3 operator*(Vector3 rhs) const { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
        [[nodiscard]] constexpr Vector3 operator/(float scalar) const {
            const float inv = 1.0f / scalar;
            return { x * inv, y * inv, z * inv };
        }
        [[nodiscard]] constexpr Vector3 operator/(Vector3 rhs) const { return { x / rhs.x, y / rhs.y, z / rhs.z }; }

        constexpr Vector3& operator+=(Vector3 rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
        constexpr Vector3& operator-=(Vector3 rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
        constexpr Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
        constexpr Vector3& operator*=(Vector3 rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
        constexpr Vector3& operator/=(float scalar) {
            const float inv = 1.0f / scalar;
            x *= inv; y *= inv; z *= inv;
            return *this;
        }
        constexpr Vector3& operator/=(Vector3 rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

        [[nodiscard]] constexpr bool operator==(Vector3 rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
        [[nodiscard]] constexpr bool operator!=(Vector3 rhs) const { return !(*this == rhs); }

        // Basic Math
        [[nodiscard]] constexpr float Dot(Vector3 rhs) const { return (x * rhs.x) + (y * rhs.y) + (z * rhs.z); }
        [[nodiscard]] constexpr Vector3 Cross(Vector3 rhs) const {
            return {
                (y * rhs.z) - (z * rhs.y),
                (z * rhs.x) - (x * rhs.z),
                (x * rhs.y) - (y * rhs.x)
            };
        }
        [[nodiscard]] constexpr float LengthSqr() const { return Dot(*this); }
        [[nodiscard]] float Length() const { return std::hypot(x, y, z); }
        [[nodiscard]] constexpr Vector3 Negate() const { return { -x, -y, -z }; }
        [[nodiscard]] constexpr Vector3 Invert() const { return { 1.0f / x, 1.0f / y, 1.0f / z }; }

        [[nodiscard]] float Distance(Vector3 v2) const { return (*this - v2).Length(); }
        [[nodiscard]] constexpr float DistanceSqr(Vector3 v2) const { return (*this - v2).LengthSqr(); }

        [[nodiscard]] Vector3 Normalized() const {
            const float len = Length();
            return (len > 0.0f) ? (*this * (1.0f / len)) : Zero();
        }

        [[nodiscard]] constexpr Vector3 Lerp(Vector3 v2, float amount) const {
            return { std::lerp(x, v2.x, amount), std::lerp(y, v2.y, amount), std::lerp(z, v2.z, amount) };
        }

        [[nodiscard]] constexpr Vector3 Reflect(Vector3 normal) const {
            return *this - (normal * (2.0f * Dot(normal)));
        }

        [[nodiscard]] Vector3 Refract(Vector3 normal, float r) const {
            const float d = Dot(normal);
            const float k = 1.0f - r * r * (1.0f - d * d);
            if (k < 0.0f) return Zero();
            return (*this * r) - (normal * (r * d + std::sqrt(k)));
        }

        [[nodiscard]] float Angle(Vector3 v2) const {
            const Vector3 cross = Cross(v2);
            const float len = cross.Length();
            const float dot = Dot(v2);
            return std::atan2(len, dot);
        }

        [[nodiscard]] Vector3 MoveTowards(Vector3 target, float maxDistance) const {
            const Vector3 delta = target - *this;
            const float sqrDist = delta.LengthSqr();
            if (sqrDist == 0.0f || (maxDistance >= 0.0f && sqrDist <= maxDistance * maxDistance)) {
                return target;
            }
            const float dist = std::sqrt(sqrDist);
            return *this + delta / dist * maxDistance;
        }

        [[nodiscard]] Vector3 RotateByAxisAngle(Vector3 axis, float angle) const {
            Vector3 a = axis.Normalized();
            const float halfAngle = angle * 0.5f;
            const float sinHalf = std::sin(halfAngle);
            const float cosHalf = std::cos(halfAngle);

            const Vector3 qVec = a * sinHalf;
            const float qW = cosHalf;

            const Vector3 cross1 = qVec.Cross(*this);
            const Vector3 cross2 = qVec.Cross(cross1 + (*this * qW));

            return *this + (cross2 * 2.0f);
        }

        // Clamping & Comparisons
        [[nodiscard]] constexpr Vector3 Clamp(Vector3 min, Vector3 max) const {
            return { std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y), std::clamp(z, min.z, max.z) };
        }

        [[nodiscard]] Vector3 ClampValue(float min, float max) const {
            const float len = Length();
            if (len == 0.0f) return Zero();
            const float clamped = std::clamp(len, min, max);
            return *this * (clamped / len);
        }

        [[nodiscard]] bool Equals(Vector3 q, float epsilon = 0.000001f) const {
            return (std::abs(x - q.x) <= epsilon) &&
                   (std::abs(y - q.y) <= epsilon) &&
                   (std::abs(z - q.z) <= epsilon);
        }
    };

}