#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "vector2.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Vector2 - Constructors and Interoperability", "[Vector2]") {
    SECTION("Default constructor initializes to Zero") {
        ooray::Vector2 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
    }

    SECTION("Single scalar value constructor sets both components") {
        ooray::Vector2 v(5.0f);
        REQUIRE(v.x == 5.0f);
        REQUIRE(v.y == 5.0f);
    }

    SECTION("Explicit components constructor") {
        ooray::Vector2 v(3.0f, -4.0f);
        REQUIRE(v.x == 3.0f);
        REQUIRE(v.y == -4.0f);
    }

    SECTION("Conversion to and from C-struct ::Vector2") {
        ::Vector2 raw{10.0f, 20.0f};
        ooray::Vector2 wrapped = raw;

        REQUIRE(wrapped.x == 10.0f);
        REQUIRE(wrapped.y == 20.0f);

        // Implicit pass to C struct
        ::Vector2 extracted = wrapped;
        REQUIRE(extracted.x == 10.0f);
        REQUIRE(extracted.y == 20.0f);
    }

    SECTION("Static direction helpers") {
        REQUIRE(ooray::Vector2::Zero() == ooray::Vector2(0.0f, 0.0f));
        REQUIRE(ooray::Vector2::One() == ooray::Vector2(1.0f, 1.0f));
        REQUIRE(ooray::Vector2::Up() == ooray::Vector2(0.0f, -1.0f));
        REQUIRE(ooray::Vector2::Down() == ooray::Vector2(0.0f, 1.0f));
        REQUIRE(ooray::Vector2::Left() == ooray::Vector2(-1.0f, 0.0f));
        REQUIRE(ooray::Vector2::Right() == ooray::Vector2(1.0f, 0.0f));
    }
}

TEST_CASE("ooray::Vector2 - Arithmetic Operators", "[Vector2]") {
    ooray::Vector2 a(3.0f, 4.0f);
    ooray::Vector2 b(1.0f, -2.0f);

    SECTION("Addition & Subtraction") {
        REQUIRE((a + b) == ooray::Vector2(4.0f, 2.0f));
        REQUIRE((a - b) == ooray::Vector2(2.0f, 6.0f));
    }

    SECTION("Multiplication & Division by scalar") {
        REQUIRE((a * 2.0f) == ooray::Vector2(6.0f, 8.0f));
        REQUIRE((2.0f * a) == ooray::Vector2(6.0f, 8.0f)); // Global oveoorayoad
        REQUIRE((a / 2.0f) == ooray::Vector2(1.5f, 2.0f));
    }

    SECTION("Component-wise Multiplication & Division") {
        REQUIRE((a * b) == ooray::Vector2(3.0f, -8.0f));
        REQUIRE((a / b) == ooray::Vector2(3.0f, -2.0f));
    }

    SECTION("Unary Negation") {
        REQUIRE(-a == ooray::Vector2(-3.0f, -4.0f));
    }

    SECTION("Compound Assignment Operators") {
        ooray::Vector2 v(1.0f, 2.0f);
        v += ooray::Vector2(2.0f, 3.0f);
        REQUIRE(v == ooray::Vector2(3.0f, 5.0f));

        v -= ooray::Vector2(1.0f, 1.0f);
        REQUIRE(v == ooray::Vector2(2.0f, 4.0f));

        v *= 2.0f;
        REQUIRE(v == ooray::Vector2(4.0f, 8.0f));

        v /= 4.0f;
        REQUIRE(v == ooray::Vector2(1.0f, 2.0f));
    }
}

TEST_CASE("ooray::Vector2 - Geometric & Mathematical Methods", "[Vector2]") {
    SECTION("Length and Squared Length") {
        ooray::Vector2 v(3.0f, 4.0f);
        REQUIRE_THAT(v.Length(), WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(v.LengthSqr(), WithinRel(25.0f, 0.0001f));
    }

    SECTION("Distance and Squared Distance") {
        ooray::Vector2 a(1.0f, 1.0f);
        ooray::Vector2 b(4.0f, 5.0f);
        REQUIRE_THAT(a.Distance(b), WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(a.DistanceSqr(b), WithinRel(25.0f, 0.0001f));
    }

    SECTION("Normalization") {
        ooray::Vector2 v(0.0f, 10.0f);
        ooray::Vector2 norm = v.Normalized();

        REQUIRE_THAT(norm.x, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinRel(1.0f, 0.0001f));

        // Mutating in-place version
        v.Normalize();
        REQUIRE(v == norm);
    }

    SECTION("Dot & Cross Products") {
        ooray::Vector2 a(1.0f, 0.0f);
        ooray::Vector2 b(0.0f, 1.0f);

        REQUIRE_THAT(a.Dot(b), WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(a.Dot(a), WithinRel(1.0f, 0.0001f));
        REQUIRE_THAT(a.Cross(b), WithinRel(1.0f, 0.0001f));
    }

    SECTION("Linear Interpolation (Lerp)") {
        ooray::Vector2 start(0.0f, 0.0f);
        ooray::Vector2 end(10.0f, 20.0f);

        ooray::Vector2 mid = start.Lerp(end, 0.5f);
        REQUIRE_THAT(mid.x, WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(mid.y, WithinRel(10.0f, 0.0001f));
    }

    SECTION("Clamping") {
        ooray::Vector2 val(15.0f, -5.0f);
        ooray::Vector2 min(0.0f, 0.0f);
        ooray::Vector2 max(10.0f, 10.0f);

        ooray::Vector2 clamped = val.Clamp(min, max);
        REQUIRE(clamped == ooray::Vector2(10.0f, 0.0f));
    }
}