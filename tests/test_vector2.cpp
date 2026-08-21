#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ooray.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Vector2 - Constructors and Interoperability", "[Vector2]") {
    SECTION("Default constructor initializes to Zero") {
        OORAY::Vector2 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
    }

    SECTION("Single scalar value constructor sets both components") {
        OORAY::Vector2 v(5.0f);
        REQUIRE(v.x == 5.0f);
        REQUIRE(v.y == 5.0f);
    }

    SECTION("Explicit components constructor") {
        OORAY::Vector2 v(3.0f, -4.0f);
        REQUIRE(v.x == 3.0f);
        REQUIRE(v.y == -4.0f);
    }

    SECTION("Conversion to and from C-struct ::Vector2") {
        ::Vector2 raw{10.0f, 20.0f};
        OORAY::Vector2 wrapped = raw;

        REQUIRE(wrapped.x == 10.0f);
        REQUIRE(wrapped.y == 20.0f);

        // Implicit pass to C struct
        ::Vector2 extracted = wrapped;
        REQUIRE(extracted.x == 10.0f);
        REQUIRE(extracted.y == 20.0f);
    }

    SECTION("Static direction helpers") {
        REQUIRE(OORAY::Vector2::Zero() == OORAY::Vector2(0.0f, 0.0f));
        REQUIRE(OORAY::Vector2::One() == OORAY::Vector2(1.0f, 1.0f));
        REQUIRE(OORAY::Vector2::Up() == OORAY::Vector2(0.0f, -1.0f));
        REQUIRE(OORAY::Vector2::Down() == OORAY::Vector2(0.0f, 1.0f));
        REQUIRE(OORAY::Vector2::Left() == OORAY::Vector2(-1.0f, 0.0f));
        REQUIRE(OORAY::Vector2::Right() == OORAY::Vector2(1.0f, 0.0f));
    }
}

TEST_CASE("ooray::Vector2 - Arithmetic Operators", "[Vector2]") {
    OORAY::Vector2 a(3.0f, 4.0f);
    OORAY::Vector2 b(1.0f, -2.0f);

    SECTION("Addition & Subtraction") {
        REQUIRE((a + b) == OORAY::Vector2(4.0f, 2.0f));
        REQUIRE((a - b) == OORAY::Vector2(2.0f, 6.0f));
    }

    SECTION("Multiplication & Division by scalar") {
        REQUIRE((a * 2.0f) == OORAY::Vector2(6.0f, 8.0f));
        REQUIRE((2.0f * a) == OORAY::Vector2(6.0f, 8.0f)); // Global oveoorayoad
        REQUIRE((a / 2.0f) == OORAY::Vector2(1.5f, 2.0f));
    }

    SECTION("Component-wise Multiplication & Division") {
        REQUIRE((a * b) == OORAY::Vector2(3.0f, -8.0f));
        REQUIRE((a / b) == OORAY::Vector2(3.0f, -2.0f));
    }

    SECTION("Unary Negation") {
        REQUIRE(-a == OORAY::Vector2(-3.0f, -4.0f));
    }

    SECTION("Compound Assignment Operators") {
        OORAY::Vector2 v(1.0f, 2.0f);
        v += OORAY::Vector2(2.0f, 3.0f);
        REQUIRE(v == OORAY::Vector2(3.0f, 5.0f));

        v -= OORAY::Vector2(1.0f, 1.0f);
        REQUIRE(v == OORAY::Vector2(2.0f, 4.0f));

        v *= 2.0f;
        REQUIRE(v == OORAY::Vector2(4.0f, 8.0f));

        v /= 4.0f;
        REQUIRE(v == OORAY::Vector2(1.0f, 2.0f));
    }
}

TEST_CASE("ooray::Vector2 - Geometric & Mathematical Methods", "[Vector2]") {
    SECTION("Length and Squared Length") {
        OORAY::Vector2 v(3.0f, 4.0f);
        REQUIRE_THAT(v.GetLength(), WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(v.GetLengthSqr(), WithinRel(25.0f, 0.0001f));
    }

    SECTION("Distance and Squared Distance") {
        OORAY::Vector2 a(1.0f, 1.0f);
        OORAY::Vector2 b(4.0f, 5.0f);
        REQUIRE_THAT(a.GetDistance(b), WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(a.GetDistanceSqr(b), WithinRel(25.0f, 0.0001f));
    }

    SECTION("Normalization") {
        OORAY::Vector2 v(0.0f, 10.0f);
        OORAY::Vector2 norm = v.GetNormalized();

        REQUIRE_THAT(norm.x, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinRel(1.0f, 0.0001f));

        // Mutating in-place version
        v.ApplyNormalize();
        REQUIRE(v == norm);
    }

    SECTION("Dot & Cross Products") {
        OORAY::Vector2 a(1.0f, 0.0f);
        OORAY::Vector2 b(0.0f, 1.0f);

        REQUIRE_THAT(a.GetDot(b), WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(a.GetDot(a), WithinRel(1.0f, 0.0001f));
        REQUIRE_THAT(a.GetCross(b), WithinRel(1.0f, 0.0001f));
    }

    SECTION("Linear Interpolation (Lerp)") {
        OORAY::Vector2 start(0.0f, 0.0f);
        OORAY::Vector2 end(10.0f, 20.0f);

        OORAY::Vector2 mid = start.GetLerp(end, 0.5f);
        REQUIRE_THAT(mid.x, WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(mid.y, WithinRel(10.0f, 0.0001f));
    }

    SECTION("Clamping") {
        OORAY::Vector2 val(15.0f, -5.0f);
        OORAY::Vector2 min(0.0f, 0.0f);
        OORAY::Vector2 max(10.0f, 10.0f);

        OORAY::Vector2 clamped = val.GetClamp(min, max);
        REQUIRE(clamped == OORAY::Vector2(10.0f, 0.0f));
    }
}