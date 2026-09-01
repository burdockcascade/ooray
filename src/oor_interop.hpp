#pragma once

#include "oor_vector2.hpp"
#include <raylib.h>
#include <bit>

namespace ooray::interop {

    // Converts ooray::Vector2 to raylib ::Vector2
    [[nodiscard]] constexpr ::Vector2 ToRay(Vector2 v) noexcept {
        return std::bit_cast<::Vector2>(v);
    }

    // Converts raylib ::Vector2 to ooray::Vector2
    [[nodiscard]] constexpr Vector2 FromRay(::Vector2 v) noexcept {
        return std::bit_cast<Vector2>(v);
    }

    // View-casting for pointers/arrays (zero copy)
    [[nodiscard]] inline const ::Vector2* AsRayPtr(const Vector2* v) noexcept {
        return reinterpret_cast<const ::Vector2*>(v);
    }

    [[nodiscard]] inline ::Vector2* AsRayPtr(Vector2* v) noexcept {
        return reinterpret_cast<::Vector2*>(v);
    }

}