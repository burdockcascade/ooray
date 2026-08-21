#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <concepts>
#include <ostream>

namespace OORAY {

#pragma region Color

    class Color : public ::Color {
    public:
        // Constructors
        constexpr Color() noexcept : ::Color{0, 0, 0, 255} {}
        constexpr Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255) noexcept
            : ::Color{r_, g_, b_, a_} {}
        constexpr Color(const ::Color& color) noexcept
            : ::Color{color.r, color.g, color.b, color.a} {}

        // Construct from packed 32-bit int or hex (e.g., Color(0xFF0000FF))
        explicit constexpr Color(std::uint32_t hexValue) noexcept
            : ::Color{
                static_cast<unsigned char>((hexValue >> 24) & 0xFF),
                static_cast<unsigned char>((hexValue >> 16) & 0xFF),
                static_cast<unsigned char>((hexValue >> 8) & 0xFF),
                static_cast<unsigned char>(hexValue & 0xFF)
            } {}

        // Implicit conversion back to Raylib's C struct
        constexpr operator ::Color() const noexcept { return {r, g, b, a}; }

        // Static Common Preset Colors
        [[nodiscard]] static constexpr Color LightGray() noexcept { return ::LIGHTGRAY; }
        [[nodiscard]] static constexpr Color Gray() noexcept      { return ::GRAY; }
        [[nodiscard]] static constexpr Color DarkGray() noexcept  { return ::DARKGRAY; }
        [[nodiscard]] static constexpr Color Yellow() noexcept    { return ::YELLOW; }
        [[nodiscard]] static constexpr Color Gold() noexcept      { return ::GOLD; }
        [[nodiscard]] static constexpr Color Orange() noexcept    { return ::ORANGE; }
        [[nodiscard]] static constexpr Color Pink() noexcept      { return ::PINK; }
        [[nodiscard]] static constexpr Color Red() noexcept       { return ::RED; }
        [[nodiscard]] static constexpr Color Maroon() noexcept    { return ::MAROON; }
        [[nodiscard]] static constexpr Color Green() noexcept     { return ::GREEN; }
        [[nodiscard]] static constexpr Color Lime() noexcept      { return ::LIME; }
        [[nodiscard]] static constexpr Color DarkGreen() noexcept { return ::DARKGREEN; }
        [[nodiscard]] static constexpr Color SkyBlue() noexcept   { return ::SKYBLUE; }
        [[nodiscard]] static constexpr Color Blue() noexcept      { return ::BLUE; }
        [[nodiscard]] static constexpr Color DarkBlue() noexcept  { return ::DARKBLUE; }
        [[nodiscard]] static constexpr Color Purple() noexcept    { return ::PURPLE; }
        [[nodiscard]] static constexpr Color Violet() noexcept    { return ::VIOLET; }
        [[nodiscard]] static constexpr Color DarkPurple() noexcept{ return ::DARKPURPLE; }
        [[nodiscard]] static constexpr Color Beige() noexcept     { return ::BEIGE; }
        [[nodiscard]] static constexpr Color Brown() noexcept     { return ::BROWN; }
        [[nodiscard]] static constexpr Color DarkBrown() noexcept { return ::DARKBROWN; }
        [[nodiscard]] static constexpr Color White() noexcept     { return ::WHITE; }
        [[nodiscard]] static constexpr Color Black() noexcept     { return ::BLACK; }
        [[nodiscard]] static constexpr Color Blank() noexcept     { return ::BLANK; }
        [[nodiscard]] static constexpr Color Magenta() noexcept   { return ::MAGENTA; }
        [[nodiscard]] static constexpr Color RayWhite() noexcept  { return ::RAYWHITE; }

        // Color Conversion & Generators
        [[nodiscard]] Vector4 ToVector4() const noexcept { return ColorNormalize(*this); }
        [[nodiscard]] std::uint32_t ToInt() const noexcept { return ColorToInt(*this); }

        [[nodiscard]] static Color FromNormalized(Vector4 normalized) noexcept {
            return ColorFromNormalized(normalized);
        }

        [[nodiscard]] static Color FromHSV(float hue, float saturation, float value) noexcept {
            return ColorFromHSV(hue, saturation, value);
        }

        [[nodiscard]] Vector3 ToHSV() const noexcept { return ColorToHSV(*this); }

        // Color Operations & Modifications (Const / Immutable)
        [[nodiscard]] Color GetFade(float alpha) const noexcept { return ::Fade(*this, alpha); }
        [[nodiscard]] Color GetAlpha(float alpha) const noexcept { return ColorAlpha(*this, alpha); }
        [[nodiscard]] Color GetAlphaBlend(Color src, Color tint) const noexcept { return ColorAlphaBlend(*this, src, tint); }
        [[nodiscard]] Color GetLerp(Color target, float factor) const noexcept { return ColorLerp(*this, target, factor); }
        [[nodiscard]] Color GetTint(Color tint) const noexcept { return ColorTint(*this, tint); }
        [[nodiscard]] Color GetContrast(float contrast) const noexcept { return ColorContrast(*this, contrast); }
        [[nodiscard]] Color GetBrightness(float factor) const noexcept { return ColorBrightness(*this, factor); }

        // In-place Mutating Operations
        Color& ApplyFade(float alpha) noexcept { *this = GetFade(alpha); return *this; }
        Color& ApplyAlpha(float alpha) noexcept { *this = GetAlpha(alpha); return *this; }
        Color& ApplyTint(Color tint) noexcept { *this = GetTint(tint); return *this; }
        Color& ApplyContrast(float contrast) noexcept { *this = GetContrast(contrast); return *this; }
        Color& ApplyBrightness(float factor) noexcept { *this = GetBrightness(factor); return *this; }

        // Operators
        bool operator==(const Color& rhs) const noexcept {
            return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
        }

        // Stream operator for debugging
        friend std::ostream& operator<<(std::ostream& os, const Color& c) {
            return os << "Color(" << static_cast<int>(c.r) << ", "
                      << static_cast<int>(c.g) << ", "
                      << static_cast<int>(c.b) << ", "
                      << static_cast<int>(c.a) << ")";
        }
    };

#pragma endregion

#pragma region Math

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
        [[nodiscard]] float GetLength() const noexcept { return Vector2Length(*this); }
        [[nodiscard]] float GetLengthSqr() const noexcept { return Vector2LengthSqr(*this); }
        [[nodiscard]] float GetDistance(Vector2 other) const noexcept { return Vector2Distance(*this, other); }
        [[nodiscard]] float GetDistanceSqr(Vector2 other) const noexcept { return Vector2DistanceSqr(*this, other); }
        [[nodiscard]] float GetAngle(Vector2 other) const noexcept { return Vector2Angle(*this, other); }

        [[nodiscard]] Vector2 GetNormalized() const noexcept { return Vector2Normalize(*this); }
        [[nodiscard]] Vector2 GetRotated(float angleRad) const noexcept { return Vector2Rotate(*this, angleRad); }
        [[nodiscard]] Vector2 GetLerp(Vector2 target, float amount) const noexcept { return Vector2Lerp(*this, target, amount); }
        [[nodiscard]] Vector2 GetClamp(Vector2 min, Vector2 max) const noexcept { return Vector2Clamp(*this, min, max); }

        [[nodiscard]] float GetDot(Vector2 other) const noexcept { return Vector2DotProduct(*this, other); }
        [[nodiscard]] float GetCross(Vector2 other) const noexcept { return Vector2CrossProduct(*this, other); }

        // In-place Mutating Methods
        Vector2& ApplyNormalize() noexcept { *this = GetNormalized(); return *this; }
        Vector2& ApplyRotate(float angleRad) noexcept { *this = GetRotated(angleRad); return *this; }

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
        [[nodiscard]] float GetLength() const noexcept { return Vector3Length(*this); }
        [[nodiscard]] float GetLengthSqr() const noexcept { return Vector3LengthSqr(*this); }
        [[nodiscard]] float GetDistance(Vector3 other) const noexcept { return Vector3Distance(*this, other); }
        [[nodiscard]] float GetDistanceSqr(Vector3 other) const noexcept { return Vector3DistanceSqr(*this, other); }
        [[nodiscard]] float GetAngle(Vector3 other) const noexcept { return Vector3Angle(*this, other); }

        [[nodiscard]] Vector3 GetNormalized() const noexcept { return Vector3Normalize(*this); }
        [[nodiscard]] Vector3 GetLerp(Vector3 target, float amount) const noexcept { return Vector3Lerp(*this, target, amount); }
        [[nodiscard]] Vector3 GetClamp(Vector3 min, Vector3 max) const noexcept { return Vector3Clamp(*this, min, max); }

        [[nodiscard]] float GetDot(Vector3 other) const noexcept { return Vector3DotProduct(*this, other); }
        [[nodiscard]] Vector3 GetCross(Vector3 other) const noexcept { return Vector3CrossProduct(*this, other); }

        // In-place Mutating Methods
        Vector3& ApplyNormalize() noexcept { *this = GetNormalized(); return *this; }

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

    class Vector4 : public ::Vector4 {
    public:
        // Constructors
        constexpr Vector4() noexcept : ::Vector4{0.0f, 0.0f, 0.0f, 0.0f} {}
        constexpr Vector4(float val) noexcept : ::Vector4{val, val, val, val} {}
        constexpr Vector4(float x_, float y_, float z_, float w_) noexcept : ::Vector4{x_, y_, z_, w_} {}
        constexpr Vector4(const ::Vector4& vec) noexcept : ::Vector4{vec.x, vec.y, vec.z, vec.w} {}

        // Static Utility Constructors
        [[nodiscard]] static constexpr Vector4 Zero() noexcept { return {0.0f, 0.0f, 0.0f, 0.0f}; }
        [[nodiscard]] static constexpr Vector4 One() noexcept { return {1.0f, 1.0f, 1.0f, 1.0f}; }

        // Vector Operations (Const Methods)
        [[nodiscard]] float GetLength() const noexcept { return Vector4Length(*this); }
        [[nodiscard]] float GetLengthSqr() const noexcept { return Vector4LengthSqr(*this); }
        [[nodiscard]] float GetDistance(Vector4 other) const noexcept { return Vector4Distance(*this, other); }
        [[nodiscard]] float GetDistanceSqr(Vector4 other) const noexcept { return Vector4DistanceSqr(*this, other); }

        [[nodiscard]] Vector4 GetNormalized() const noexcept { return Vector4Normalize(*this); }
        [[nodiscard]] Vector4 GetLerp(Vector4 target, float amount) const noexcept { return Vector4Lerp(*this, target, amount); }

        [[nodiscard]] float GetDot(Vector4 other) const noexcept { return Vector4DotProduct(*this, other); }

        // In-place Mutating Methods
        Vector4& ApplyNormalize() noexcept { *this = GetNormalized(); return *this; }

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

    class Matrix : public ::Matrix {
    public:
        // Default Constructor initializes to Identity matrix
        constexpr Matrix() noexcept
            : ::Matrix{ 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f } {}

        constexpr Matrix(float m0_, float m4_, float m8_,  float m12_,
                         float m1_, float m5_, float m9_,  float m13_,
                         float m2_, float m6_, float m10_, float m14_,
                         float m3_, float m7_, float m11_, float m15_) noexcept
            : ::Matrix{ m0_, m4_, m8_,  m12_,
                        m1_, m5_, m9_,  m13_,
                        m2_, m6_, m10_, m14_,
                        m3_, m7_, m11_, m15_ } {}

        constexpr Matrix(const ::Matrix& mat) noexcept
            : ::Matrix{ mat.m0, mat.m4, mat.m8,  mat.m12,
                        mat.m1, mat.m5, mat.m9,  mat.m13,
                        mat.m2, mat.m6, mat.m10, mat.m14,
                        mat.m3, mat.m7, mat.m11, mat.m15 } {}

        // C-struct implicit conversion for Raylib API interop
        constexpr operator ::Matrix() const noexcept { return *this; }

        // C++23 Multidimensional Subscript Operator
        constexpr float operator[](std::size_t row, std::size_t col) const noexcept {
            const float elements[16] = {
                m0, m4, m8,  m12,
                m1, m5, m9,  m13,
                m2, m6, m10, m14,
                m3, m7, m11, m15
            };
            return elements[row * 4 + col];
        }

        // Static Generators
        [[nodiscard]] static constexpr Matrix Identity() noexcept { return Matrix{}; }
        [[nodiscard]] static Matrix Translate(float x, float y, float z) noexcept { return MatrixTranslate(x, y, z); }
        [[nodiscard]] static Matrix Translate(Vector3 v) noexcept { return MatrixTranslate(v.x, v.y, v.z); }
        [[nodiscard]] static Matrix Scale(float x, float y, float z) noexcept { return MatrixScale(x, y, z); }
        [[nodiscard]] static Matrix RotateX(float angleRad) noexcept { return MatrixRotateX(angleRad); }
        [[nodiscard]] static Matrix RotateY(float angleRad) noexcept { return MatrixRotateY(angleRad); }
        [[nodiscard]] static Matrix RotateZ(float angleRad) noexcept { return MatrixRotateZ(angleRad); }
        [[nodiscard]] static Matrix Rotate(Vector3 axis, float angleRad) noexcept { return MatrixRotate(axis, angleRad); }
        [[nodiscard]] static Matrix Perspective(double fovY, double aspect, double nearPlane, double farPlane) noexcept {
            return MatrixPerspective(fovY, aspect, nearPlane, farPlane);
        }
        [[nodiscard]] static Matrix Ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane) noexcept {
            return MatrixOrtho(left, right, bottom, top, nearPlane, farPlane);
        }

        // Operations
        [[nodiscard]] float GetDeterminant() const noexcept { return MatrixDeterminant(*this); }
        [[nodiscard]] Matrix GetTransposed() const noexcept { return MatrixTranspose(*this); }
        [[nodiscard]] Matrix GetInverted() const noexcept { return MatrixInvert(*this); }

        Matrix& ApplyTranspose() noexcept { *this = GetTransposed(); return *this; }
        Matrix& ApplyInvert() noexcept { *this = GetInverted(); return *this; }

        // Operators
        constexpr Matrix operator+(Matrix rhs) const noexcept { return MatrixAdd(*this, rhs); }
        constexpr Matrix operator-(Matrix rhs) const noexcept { return MatrixSubtract(*this, rhs); }
        constexpr Matrix operator*(Matrix rhs) const noexcept { return MatrixMultiply(*this, rhs); }

        constexpr Matrix& operator+=(Matrix rhs) noexcept { *this = *this + rhs; return *this; }
        constexpr Matrix& operator-=(Matrix rhs) noexcept { *this = *this - rhs; return *this; }
        constexpr Matrix& operator*=(Matrix rhs) noexcept { *this = *this * rhs; return *this; }

        constexpr bool operator==(const Matrix& rhs) const noexcept {
            return m0 == rhs.m0 && m4 == rhs.m4 && m8  == rhs.m8  && m12 == rhs.m12 &&
                   m1 == rhs.m1 && m5 == rhs.m5 && m9  == rhs.m9  && m13 == rhs.m13 &&
                   m2 == rhs.m2 && m6 == rhs.m6 && m10 == rhs.m10 && m14 == rhs.m14 &&
                   m3 == rhs.m3 && m7 == rhs.m7 && m11 == rhs.m11 && m15 == rhs.m15;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
            return os << "Matrix[\n"
                      << "  " << m.m0 << ", " << m.m4 << ", " << m.m8  << ", " << m.m12 << "\n"
                      << "  " << m.m1 << ", " << m.m5 << ", " << m.m9  << ", " << m.m13 << "\n"
                      << "  " << m.m2 << ", " << m.m6 << ", " << m.m10 << ", " << m.m14 << "\n"
                      << "  " << m.m3 << ", " << m.m7 << ", " << m.m11 << ", " << m.m15 << "\n]";
        }
    };

    // Global scalar multiplication overload (e.g., 2.0f * vec)
    constexpr Vector2 operator*(float scalar, Vector2 vec) noexcept {
        return vec * scalar;
    }

    // Global scalar multiplication overload (e.g., 2.0f * vec)
    constexpr Vector3 operator*(float scalar, Vector3 vec) noexcept {
        return vec * scalar;
    }

    // Global scalar multiplication overload (e.g., 2.0f * vec)
    constexpr Vector4 operator*(float scalar, Vector4 vec) noexcept {
        return vec * scalar;
    }

#pragma endregion

#pragma region Geometry

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
        [[nodiscard]] constexpr Vector2 GetPosition() const noexcept { return {x, y}; }
        constexpr void SetPosition(Vector2 pos) noexcept { x = pos.x; y = pos.y; }

        [[nodiscard]] constexpr Vector2 GetSize() const noexcept { return {width, height}; }
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

#pragma endregion

}