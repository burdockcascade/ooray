#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "vector3.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Vector3 - Constructors and Interoperability", "[Vector3]") {
    SECTION("Default constructor initializes to Zero") {
        ooray::Vector3 v;
        REQUIRE(v.x == 0.0f);
        REQUIRE(v.y == 0.0f);
        REQUIRE(v.z == 0.0f);
    }

    SECTION("Single scalar value constructor sets all components") {
        ooray::Vector3 v(5.0f);
        REQUIRE(v.x == 5.0f);
        REQUIRE(v.y == 5.0f);
        REQUIRE(v.z == 5.0f);
    }

    SECTION("Explicit components constructor") {
        ooray::Vector3 v(3.0f, -4.0f, 2.0f);
        REQUIRE(v.x == 3.0f);
        REQUIRE(v.y == -4.0f);
        REQUIRE(v.z == 2.0f);
    }

    SECTION("Conversion to and from C-struct ::Vector3") {
        ::Vector3 raw{10.0f, 20.0f, 30.0f};
        ooray::Vector3 wrapped = raw;

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
        REQUIRE(ooray::Vector3::Zero() == ooray::Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(ooray::Vector3::One() == ooray::Vector3(1.0f, 1.0f, 1.0f));
        REQUIRE(ooray::Vector3::Up() == ooray::Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(ooray::Vector3::Down() == ooray::Vector3(0.0f, -1.0f, 0.0f));
        REQUIRE(ooray::Vector3::Left() == ooray::Vector3(-1.0f, 0.0f, 0.0f));
        REQUIRE(ooray::Vector3::Right() == ooray::Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(ooray::Vector3::Forward() == ooray::Vector3(0.0f, 0.0f, 1.0f));
        REQUIRE(ooray::Vector3::Back() == ooray::Vector3(0.0f, 0.0f, -1.0f));
    }
}

TEST_CASE("ooray::Vector3 - Arithmetic Operators", "[Vector3]") {
    ooray::Vector3 a(2.0f, 3.0f, 6.0f);
    ooray::Vector3 b(1.0f, -2.0f, 3.0f);

    SECTION("Addition & Subtraction") {
        REQUIRE((a + b) == ooray::Vector3(3.0f, 1.0f, 9.0f));
        REQUIRE((a - b) == ooray::Vector3(1.0f, 5.0f, 3.0f));
    }

    SECTION("Multiplication & Division by scalar") {
        REQUIRE((a * 2.0f) == ooray::Vector3(4.0f, 6.0f, 12.0f));
        REQUIRE((2.0f * a) == ooray::Vector3(4.0f, 6.0f, 12.0f));
        REQUIRE((a / 2.0f) == ooray::Vector3(1.0f, 1.5f, 3.0f));
    }

    SECTION("Component-wise Multiplication & Division") {
        REQUIRE((a * b) == ooray::Vector3(2.0f, -6.0f, 18.0f));
        REQUIRE((a / b) == ooray::Vector3(2.0f, -1.5f, 2.0f));
    }

    SECTION("Unary Negation") {
        REQUIRE(-a == ooray::Vector3(-2.0f, -3.0f, -6.0f));
    }

    SECTION("Compound Assignment Operators") {
        ooray::Vector3 v(1.0f, 2.0f, 3.0f);
        v += ooray::Vector3(2.0f, 3.0f, 4.0f);
        REQUIRE(v == ooray::Vector3(3.0f, 5.0f, 7.0f));

        v -= ooray::Vector3(1.0f, 1.0f, 1.0f);
        REQUIRE(v == ooray::Vector3(2.0f, 4.0f, 6.0f));

        v *= 2.0f;
        REQUIRE(v == ooray::Vector3(4.0f, 8.0f, 12.0f));

        v /= 4.0f;
        REQUIRE(v == ooray::Vector3(1.0f, 2.0f, 3.0f));
    }
}

TEST_CASE("ooray::Vector3 - Geometric & Mathematical Methods", "[Vector3]") {
    SECTION("Length and Squared Length") {
        ooray::Vector3 v(2.0f, 3.0f, 6.0f);
        REQUIRE_THAT(v.Length(), WithinRel(7.0f, 0.0001f));
        REQUIRE_THAT(v.LengthSqr(), WithinRel(49.0f, 0.0001f));
    }

    SECTION("Distance and Squared Distance") {
        ooray::Vector3 a(1.0f, 2.0f, 3.0f);
        ooray::Vector3 b(3.0f, 5.0f, 9.0f); // diff = (2, 3, 6) -> len = 7
        REQUIRE_THAT(a.Distance(b), WithinRel(7.0f, 0.0001f));
        REQUIRE_THAT(a.DistanceSqr(b), WithinRel(49.0f, 0.0001f));
    }

    SECTION("Normalization") {
        ooray::Vector3 v(0.0f, 0.0f, 10.0f);
        ooray::Vector3 norm = v.Normalized();

        REQUIRE_THAT(norm.x, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(norm.z, WithinRel(1.0f, 0.0001f));

        // Mutating in-place version
        v.Normalize();
        REQUIRE(v == norm);
    }

    SECTION("Dot & Cross Products") {
        ooray::Vector3 a(1.0f, 0.0f, 0.0f);
        ooray::Vector3 b(0.0f, 1.0f, 0.0f);

        REQUIRE_THAT(a.Dot(b), WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT(a.Dot(a), WithinRel(1.0f, 0.0001f));

        // Right-hand rule cross product: X cross Y = Z
        REQUIRE(a.Cross(b) == ooray::Vector3(0.0f, 0.0f, 1.0f));
    }

    SECTION("Linear Interpolation (Lerp)") {
        ooray::Vector3 start(0.0f, 0.0f, 0.0f);
        ooray::Vector3 end(10.0f, 20.0f, 30.0f);

        ooray::Vector3 mid = start.Lerp(end, 0.5f);
        REQUIRE_THAT(mid.x, WithinRel(5.0f, 0.0001f));
        REQUIRE_THAT(mid.y, WithinRel(10.0f, 0.0001f));
        REQUIRE_THAT(mid.z, WithinRel(15.0f, 0.0001f));
    }

    SECTION("Clamping") {
        ooray::Vector3 val(15.0f, -5.0f, 5.0f);
        ooray::Vector3 min(0.0f, 0.0f, 0.0f);
        ooray::Vector3 max(10.0f, 10.0f, 10.0f);

        ooray::Vector3 clamped = val.Clamp(min, max);
        REQUIRE(clamped == ooray::Vector3(10.0f, 0.0f, 5.0f));
    }
}