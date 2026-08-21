#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ooray.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Vector3 - Constructors and Interoperability", "[Vector3]") {
    SECTION("Default constructor initializes to Zero") {
        OORAY::Vector3 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
        REQUIRE(v.z == 0.0f);
    }

    SECTION("Single scalar value constructor sets all components") {
        OORAY::Vector3 v(5.0f);
        REQUIRE(v.x == 5.0f);
        REQUIRE(v.y == 5.0f);
        REQUIRE(v.z == 5.0f);
    }

    SECTION("Explicit components constructor") {
        OORAY::Vector3 v(3.0f, -4.0f, 2.0f);
        REQUIRE(v.x == 3.0f);
        REQUIRE(v.y == -4.0f);
        REQUIRE(v.z == 2.0f);
    }

    SECTION("Conversion to and from C-struct ::Vector3") {
        ::Vector3 raw{10.0f, 20.0f, 30.0f};
        OORAY::Vector3 wrapped = raw;

        REQUIRE(wrapped.x == 10.0f);
        REQUIRE(wrapped.y == 20.0f);
        REQUIRE(wrapped.z == 30.0f);

        // Implicit pass to C struct
        ::Vector3 extracted = wrapped;
        REQUIRE(extracted.x == 10.0f);
        REQUIRE(extracted.y == 20.0f);
        REQUIRE(extracted.z == 30.0f);
    }

    SECTION("Static direction helpers") {
        REQUIRE(OORAY::Vector3::Zero() == OORAY::Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(OORAY::Vector3::One() == OORAY::Vector3(1.0f, 1.0f, 1.0f));
        REQUIRE(OORAY::Vector3::Up() == OORAY::Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(OORAY::Vector3::Down() == OORAY::Vector3(0.0f, -1.0f, 0.0f));
        REQUIRE(OORAY::Vector3::Left() == OORAY::Vector3(-1.0f, 0.0f, 0.0f));
        REQUIRE(OORAY::Vector3::Right() == OORAY::Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(OORAY::Vector3::Forward() == OORAY::Vector3(0.0f, 0.0f, 1.0f));
        REQUIRE(OORAY::Vector3::Back() == OORAY::Vector3(0.0f, 0.0f, -1.0f));
    }
}

TEST_CASE("ooray::Vector3 - Arithmetic Operators", "[Vector3]") {
    OORAY::Vector3 a(2.0f, 3.0f, 6.0f);
    OORAY::Vector3 b(1.0f, -2.0f, 3.0f);

    SECTION("Addition & Subtraction") {
        REQUIRE((a + b) == OORAY::Vector3(3.0f, 1.0f, 9.0f));
        REQUIRE((a - b) == OORAY::Vector3(1.0f, 5.0f, 3.0f));
    }

    SECTION("Multiplication & Division by scalar") {
        REQUIRE((a * 2.0f) == OORAY::Vector3(4.0f, 6.0f, 12.0f));
        REQUIRE((2.0f * a) == OORAY::Vector3(4.0f, 6.0f, 12.0f));
        REQUIRE((a / 2.0f) == OORAY::Vector3(1.0f, 1.5f, 3.0f));
    }

    SECTION("Component-wise Multiplication & Division") {
        REQUIRE((a * b) == OORAY::Vector3(2.0f, -6.0f, 18.0f));
        REQUIRE((a / b) == OORAY::Vector3(2.0f, -1.5f, 2.0f));
    }

    SECTION("Unary Negation") {
        REQUIRE(-a == OORAY::Vector3(-2.0f, -3.0f, -6.0f));
    }

    SECTION("Compound Assignment Operators") {
        OORAY::Vector3 v(1.0f, 2.0f, 3.0f);
        v += OORAY::Vector3(2.0f, 3.0f, 4.0f);
        REQUIRE(v == OORAY::Vector3(3.0f, 5.0f, 7.0f));

        v -= OORAY::Vector3(1.0f, 1.0f, 1.0f);
        REQUIRE(v == OORAY::Vector3(2.0f, 4.0f, 6.0f));

        v *= 2.0f;
        REQUIRE(v == OORAY::Vector3(4.0f, 8.0f, 12.0f));

        v /= 4.0f;
        REQUIRE(v == OORAY::Vector3(1.0f, 2.0f, 3.0f));
    }
}

TEST_CASE("ooray::Vector3 - Geometric & Mathematical Methods", "[Vector3]") {
    SECTION("Length and Squared Length") {
        OORAY::Vector3 v(2.0f, 3.0f, 6.0f);
        REQUIRE_THAT(v.GetLength(), WithinRel(7.0f, 0.0001f));
        REQUIRE_THAT(v.GetLengthSqr(), WithinRel(49.0f, 0.0001f));
    }

    SECTION("Distance and Squared Distance") {
        OORAY::Vector3 a(1.0f, 2.0f, 3.0f);
        OORAY::Vector3 b(3.0f, 5.0f, 9.0f); // diff = (2, 3, 6) -> len = 7
        REQUIRE_THAT(a.GetDistance(b), WithinRel(7.0f, 0.0001f));
        REQUIRE_THAT(a.GetDistanceSqr(b), WithinRel(49.0f, 0.0001f));
    }

    SECTION("Normalization") {
        OORAY::Vector3 v(0.0f, 0.0f, 10.0f);
        OORAY::Vector3 norm = v.GetNormalized();

        REQUIRE_THAT(norm.x, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.z, WithinRel(1.0f, 0.0001f));

        // Mutating in-place version
        v.ApplyNormalize();
        REQUIRE(v == norm);
    }

    SECTION("Dot & Cross Products") {
        OORAY::Vector3 a(1.0f, 0.0f, 0.0f);
        OORAY::Vector3 b(0.0f, 1.0f, 0.0f);

        REQUIRE_THAT(a.GetDot(b), WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(a.GetDot(a), WithinRel(1.0f, 0.0001f));

        // Right-hand rule cross product: X cross Y = Z
        REQUIRE(a.GetCross(b) == OORAY::Vector3(0.0f, 0.0f, 1.0f));
    }

    SECTION("Linear Interpolation (Lerp)") {
        OORAY::Vector3 start(0.0f, 0.0f, 0.0f);
        OORAY::Vector3 end(10.0f, 20.0f, 30.0f);

        OORAY::Vector3 mid = start.GetLerp(end, 0.5f);
        REQUIRE_THAT(mid.x, WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(mid.y, WithinRel(10.0f, 0.0001f));
        REQUIRE_THAT(mid.z, WithinRel(15.0f, 0.0001f));
    }

    SECTION("Clamping") {
        OORAY::Vector3 val(15.0f, -5.0f, 5.0f);
        OORAY::Vector3 min(0.0f, 0.0f, 0.0f);
        OORAY::Vector3 max(10.0f, 10.0f, 10.0f);

        OORAY::Vector3 clamped = val.GetClamp(min, max);
        REQUIRE(clamped == OORAY::Vector3(10.0f, 0.0f, 5.0f));
    }
}