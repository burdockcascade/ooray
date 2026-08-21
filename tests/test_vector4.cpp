#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ooray.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Vector4 - Constructors and Interoperability", "[Vector4]") {
    SECTION("Default constructor initializes to Zero") {
        OORAY::Vector4 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
        REQUIRE(v.z == 0.0f);
        REQUIRE(v.w == 0.0f);
    }

    SECTION("Single scalar value constructor sets all components") {
        OORAY::Vector4 v(5.0f);
        REQUIRE(v.x == 5.0f);
        REQUIRE(v.y == 5.0f);
        REQUIRE(v.z == 5.0f);
        REQUIRE(v.w == 5.0f);
    }

    SECTION("Explicit components constructor") {
        OORAY::Vector4 v(1.0f, -2.0f, 3.0f, -4.0f);
        REQUIRE(v.x == 1.0f);
        REQUIRE(v.y == -2.0f);
        REQUIRE(v.z == 3.0f);
        REQUIRE(v.w == -4.0f);
    }

    SECTION("Conversion to and from C-struct ::Vector4") {
        ::Vector4 raw{10.0f, 20.0f, 30.0f, 40.0f};
        OORAY::Vector4 wrapped = raw;

        REQUIRE(wrapped.x == 10.0f);
        REQUIRE(wrapped.y == 20.0f);
        REQUIRE(wrapped.z == 30.0f);
        REQUIRE(wrapped.w == 40.0f);

        // Implicit pass to C struct
        ::Vector4 extracted = wrapped;
        REQUIRE(extracted.x == 10.0f);
        REQUIRE(extracted.y == 20.0f);
        REQUIRE(extracted.z == 30.0f);
        REQUIRE(extracted.w == 40.0f);
    }

    SECTION("Static helpers") {
        REQUIRE(OORAY::Vector4::Zero() == OORAY::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        REQUIRE(OORAY::Vector4::One() == OORAY::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }
}

TEST_CASE("ooray::Vector4 - Arithmetic Operators", "[Vector4]") {
    OORAY::Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
    OORAY::Vector4 b(2.0f, -1.0f, 0.5f, -2.0f);

    SECTION("Addition & Subtraction") {
        REQUIRE((a + b) == OORAY::Vector4(3.0f, 1.0f, 3.5f, 2.0f));
        REQUIRE((a - b) == OORAY::Vector4(-1.0f, 3.0f, 2.5f, 6.0f));
    }

    SECTION("Multiplication & Division by scalar") {
        REQUIRE((a * 2.0f) == OORAY::Vector4(2.0f, 4.0f, 6.0f, 8.0f));
        REQUIRE((2.0f * a) == OORAY::Vector4(2.0f, 4.0f, 6.0f, 8.0f));
        REQUIRE((a / 2.0f) == OORAY::Vector4(0.5f, 1.0f, 1.5f, 2.0f));
    }

    SECTION("Component-wise Multiplication & Division") {
        REQUIRE((a * b) == OORAY::Vector4(2.0f, -2.0f, 1.5f, -8.0f));
        REQUIRE((a / b) == OORAY::Vector4(0.5f, -2.0f, 6.0f, -2.0f));
    }

    SECTION("Unary Negation") {
        REQUIRE(-a == OORAY::Vector4(-1.0f, -2.0f, -3.0f, -4.0f));
    }

    SECTION("Compound Assignment Operators") {
        OORAY::Vector4 v(1.0f, 2.0f, 3.0f, 4.0f);
        v += OORAY::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(v == OORAY::Vector4(2.0f, 3.0f, 4.0f, 5.0f));

        v -= OORAY::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
        REQUIRE(v == OORAY::Vector4(1.0f, 2.0f, 3.0f, 4.0f));

        v *= 2.0f;
        REQUIRE(v == OORAY::Vector4(2.0f, 4.0f, 6.0f, 8.0f));

        v /= 2.0f;
        REQUIRE(v == OORAY::Vector4(1.0f, 2.0f, 3.0f, 4.0f));
    }
}

TEST_CASE("ooray::Vector4 - Geometric & Mathematical Methods", "[Vector4]") {
    SECTION("Length and Squared Length") {
        OORAY::Vector4 v(1.0f, 2.0f, 3.0f, 5.0f); // sum of squares = 1 + 4 + 9 + 25 = 39
        REQUIRE_THAT(v.GetLengthSqr(), WithinRel(39.0f, 0.0001f));
        REQUIRE_THAT(v.GetLength(), WithinRel(std::sqrt(39.0f), 0.0001f));
    }

    SECTION("Distance and Squared Distance") {
        OORAY::Vector4 a(1.0f, 1.0f, 1.0f, 1.0f);
        OORAY::Vector4 b(2.0f, 3.0f, 4.0f, 6.0f); // diff = (1, 2, 3, 5)
        REQUIRE_THAT(a.GetDistanceSqr(b), WithinRel(39.0f, 0.0001f));
        REQUIRE_THAT(a.GetDistance(b), WithinRel(std::sqrt(39.0f), 0.0001f));
    }

    SECTION("Normalization") {
        OORAY::Vector4 v(0.0f, 0.0f, 0.0f, 10.0f);
        OORAY::Vector4 norm = v.GetNormalized();

        REQUIRE_THAT(norm.x, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.z, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.w, WithinRel(1.0f, 0.0001f));

        // Mutating in-place version
        v.ApplyNormalize();
        REQUIRE(v == norm);
    }

    SECTION("Dot Product") {
        OORAY::Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        OORAY::Vector4 b(2.0f, 0.0f, -1.0f, 1.0f);

        // 1*2 + 2*0 + 3*(-1) + 4*1 = 2 + 0 - 3 + 4 = 3
        REQUIRE_THAT(a.GetDot(b), WithinRel(3.0f, 0.0001f));
    }

    SECTION("Linear Interpolation (Lerp)") {
        OORAY::Vector4 start(0.0f, 0.0f, 0.0f, 0.0f);
        OORAY::Vector4 end(10.0f, 20.0f, 30.0f, 40.0f);

        OORAY::Vector4 mid = start.GetLerp(end, 0.5f);
        REQUIRE_THAT(mid.x, WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(mid.y, WithinRel(10.0f, 0.0001f));
        REQUIRE_THAT(mid.z, WithinRel(15.0f, 0.0001f));
        REQUIRE_THAT(mid.w, WithinRel(20.0f, 0.0001f));
    }
}