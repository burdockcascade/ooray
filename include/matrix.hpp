#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <concepts>
#include <ostream>

#include "vector3.hpp"

namespace ooray {

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
        [[nodiscard]] float Determinant() const noexcept { return MatrixDeterminant(*this); }
        [[nodiscard]] Matrix Transposed() const noexcept { return MatrixTranspose(*this); }
        [[nodiscard]] Matrix Inverted() const noexcept { return MatrixInvert(*this); }

        Matrix& Transpose() noexcept { *this = Transposed(); return *this; }
        Matrix& Invert() noexcept { *this = Inverted(); return *this; }

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

} // namespace ooray