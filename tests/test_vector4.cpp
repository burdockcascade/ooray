#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numbers>

#include "oor_vector4.hpp"

using Catch::Matchers::WithinAbs;
using ooray::Vector4;
using ooray::Quaternion;

TEST_CASE("Vector4 - Construction and Static Helpers", "[Vector4]") {
    SECTION("Default and parameterized constructors") {
        constexpr Vector4 def;
        STATIC_REQUIRE(def.x == 0.0f);
        STATIC_REQUIRE(def.y == 0.0f);
        STATIC_REQUIRE(def.z == 0.0f);
        STATIC_REQUIRE(def.w == 0.0f);

        constexpr Vector4 custom(1.0f, 2.0f, 3.0f, 4.0f);
        STATIC_REQUIRE(custom.x == 1.0f);
        STATIC_REQUIRE(custom.y == 2.0f);
        STATIC_REQUIRE(custom.z == 3.0f);
        STATIC_REQUIRE(custom.w == 4.0f);
    }

    SECTION("Static factory methods and Alias") {
        STATIC_REQUIRE(Vector4::Zero() == Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        STATIC_REQUIRE(Vector4::One() == Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        constexpr Quaternion q(0.0f, 0.0f, 0.0f, 1.0f);
        STATIC_REQUIRE(q.w == 1.0f);
    }
}

TEST_CASE("Vector4 - Arithmetic Operators", "[Vector4]") {
    Vector4 a(2.0f, 4.0f, 6.0f, 8.0f);
    Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);

    SECTION("Binary operators") {
        REQUIRE(a + b == Vector4(3.0f, 6.0f, 9.0f, 12.0f));
        REQUIRE(a - b == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        REQUIRE(a * 2.0f == Vector4(4.0f, 8.0f, 12.0f, 16.0f));
        REQUIRE(a * b == Vector4(2.0f, 8.0f, 18.0f, 32.0f));
        REQUIRE(a / 2.0f == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        REQUIRE(a / b == Vector4(2.0f, 2.0f, 2.0f, 2.0f));
    }

    SECTION("Compound assignment operators") {
        Vector4 v(1.0f, 1.0f, 1.0f, 1.0f);

        v += Vector4(1.0f, 2.0f, 3.0f, 4.0f);
        REQUIRE(v == Vector4(2.0f, 3.0f, 4.0f, 5.0f));

        v -= Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(v == Vector4(1.0f, 2.0f, 3.0f, 4.0f));

        v *= 2.0f;
        REQUIRE(v == Vector4(2.0f, 4.0f, 6.0f, 8.0f));

        v *= Vector4(0.5f, 0.5f, 0.5f, 0.5f);
        REQUIRE(v == Vector4(1.0f, 2.0f, 3.0f, 4.0f));

        v /= 2.0f;
        REQUIRE(v == Vector4(0.5f, 1.0f, 1.5f, 2.0f));

        v /= Vector4(0.5f, 1.0f, 1.5f, 2.0f);
        REQUIRE(v == Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    SECTION("Equality and inequality") {
        REQUIRE(Vector4(1.0f, 2.0f, 3.0f, 4.0f) == Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        REQUIRE(Vector4(1.0f, 2.0f, 3.0f, 4.0f) != Vector4(1.0f, 2.0f, 3.0f, 5.0f));
    }
}

TEST_CASE("Vector4 - Basic Math Operations", "[Vector4]") {
    SECTION("Dot, Length, and LengthSqr") {
        Vector4 v(1.0f, 2.0f, 3.0f, 5.0f);
        STATIC_REQUIRE(Vector4(1.0f, 2.0f, 3.0f, 4.0f).Dot(Vector4(2.0f, 2.0f, 2.0f, 2.0f)) == 20.0f);
        STATIC_REQUIRE(Vector4(1.0f, 2.0f, 3.0f, 5.0f).LengthSqr() == 39.0f);
        REQUIRE_THAT(v.Length(), WithinAbs(std::sqrt(39.0f), 1e-6f));
    }

    SECTION("Negate and Invert") {
        constexpr Vector4 v(2.0f, -4.0f, 5.0f, -10.0f);
        STATIC_REQUIRE(v.Negate() == Vector4(-2.0f, 4.0f, -5.0f, 10.0f));
        STATIC_REQUIRE(v.Invert() == Vector4(0.5f, -0.25f, 0.2f, -0.1f));
    }

    SECTION("Distance and DistanceSqr") {
        constexpr Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr Vector4 b(2.0f, 4.0f, 5.0f, 6.0f);

        STATIC_REQUIRE(a.DistanceSqr(b) == 13.0f);
        REQUIRE_THAT(a.Distance(b), WithinAbs(std::sqrt(13.0f), 1e-6f));
    }

    SECTION("Normalized") {
        Vector4 v(0.0f, 0.0f, 4.0f, 0.0f);
        REQUIRE(v.Normalized() == Vector4(0.0f, 0.0f, 1.0f, 0.0f));
        REQUIRE(Vector4::Zero().Normalized() == Vector4::Zero());
    }
}

TEST_CASE("Vector4 - Geometric, Clamping, and Tolerances", "[Vector4]") {
    SECTION("Lerp and MoveTowards") {
        Vector4 start(0.0f, 10.0f, 20.0f, 30.0f);
        Vector4 end(10.0f, 20.0f, 30.0f, 40.0f);
        REQUIRE(start.Lerp(end, 0.5f) == Vector4(5.0f, 15.0f, 25.0f, 35.0f));

        Vector4 current(0.0f, 0.0f, 0.0f, 0.0f);
        Vector4 target(0.0f, 0.0f, 0.0f, 10.0f);
        REQUIRE(current.MoveTowards(target, 4.0f) == Vector4(0.0f, 0.0f, 0.0f, 4.0f));
        REQUIRE(current.MoveTowards(target, 15.0f) == target);
    }

    SECTION("Clamping") {
        Vector4 v(-5.0f, 5.0f, 15.0f, 25.0f);
        Vector4 min(0.0f, 0.0f, 0.0f, 0.0f);
        Vector4 max(10.0f, 10.0f, 10.0f, 10.0f);

        REQUIRE(v.Clamp(min, max) == Vector4(0.0f, 5.0f, 10.0f, 10.0f));

        Vector4 dir(0.0f, 0.0f, 0.0f, 10.0f);
        REQUIRE(dir.ClampValue(2.0f, 5.0f) == Vector4(0.0f, 0.0f, 0.0f, 5.0f));
        REQUIRE(dir.ClampValue(15.0f, 20.0f) == Vector4(0.0f, 0.0f, 0.0f, 15.0f));
        REQUIRE(Vector4::Zero().ClampValue(1.0f, 5.0f) == Vector4::Zero());
    }

    SECTION("Fuzzy Equals") {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(1.0000005f, 2.0f, 3.0f, 3.9999995f);
        Vector4 c(1.01f, 2.0f, 3.0f, 4.0f);

        REQUIRE(a.Equals(b));
        REQUIRE_FALSE(a.Equals(c));
        REQUIRE(a.Equals(c, 0.02f));
    }
}