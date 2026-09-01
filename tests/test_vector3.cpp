#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numbers>

#include "oor_vector3.hpp"

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using ooray::Vector3;

TEST_CASE("Vector3 - Construction and Static Helpers", "[Vector3]") {
    SECTION("Default and parameterized constructors") {
        constexpr Vector3 def;
        STATIC_REQUIRE(def.x == 0.0f);
        STATIC_REQUIRE(def.y == 0.0f);
        STATIC_REQUIRE(def.z == 0.0f);

        constexpr Vector3 custom(1.5f, -2.5f, 3.0f);
        STATIC_REQUIRE(custom.x == 1.5f);
        STATIC_REQUIRE(custom.y == -2.5f);
        STATIC_REQUIRE(custom.z == 3.0f);
    }

    SECTION("Static direction and factory methods") {
        STATIC_REQUIRE(Vector3::Zero() == Vector3(0.0f, 0.0f, 0.0f));
        STATIC_REQUIRE(Vector3::One() == Vector3(1.0f, 1.0f, 1.0f));
        STATIC_REQUIRE(Vector3::Up() == Vector3(0.0f, 1.0f, 0.0f));
        STATIC_REQUIRE(Vector3::Down() == Vector3(0.0f, -1.0f, 0.0f));
        STATIC_REQUIRE(Vector3::Left() == Vector3(-1.0f, 0.0f, 0.0f));
        STATIC_REQUIRE(Vector3::Right() == Vector3(1.0f, 0.0f, 0.0f));
        STATIC_REQUIRE(Vector3::Forward() == Vector3(0.0f, 0.0f, 1.0f));
        STATIC_REQUIRE(Vector3::Back() == Vector3(0.0f, 0.0f, -1.0f));
    }
}

TEST_CASE("Vector3 - Arithmetic Operators", "[Vector3]") {
    Vector3 a(2.0f, 4.0f, -6.0f);
    Vector3 b(1.0f, -2.0f, 3.0f);

    SECTION("Binary operators") {
        Vector3 sum = a + b;
        REQUIRE(sum == Vector3(3.0f, 2.0f, -3.0f));

        Vector3 diff = a - b;
        REQUIRE(diff == Vector3(1.0f, 6.0f, -9.0f));

        Vector3 scalarMul = a * 2.0f;
        REQUIRE(scalarMul == Vector3(4.0f, 8.0f, -12.0f));

        Vector3 vecMul = a * b;
        REQUIRE(vecMul == Vector3(2.0f, -8.0f, -18.0f));

        Vector3 scalarDiv = a / 2.0f;
        REQUIRE(scalarDiv == Vector3(1.0f, 2.0f, -3.0f));

        Vector3 vecDiv = a / b;
        REQUIRE(vecDiv == Vector3(2.0f, -2.0f, -2.0f));
    }

    SECTION("Compound assignment operators") {
        Vector3 v(1.0f, 2.0f, 3.0f);

        v += Vector3(1.0f, 1.0f, 1.0f);
        REQUIRE(v == Vector3(2.0f, 3.0f, 4.0f));

        v -= Vector3(1.0f, 2.0f, 3.0f);
        REQUIRE(v == Vector3(1.0f, 1.0f, 1.0f));

        v *= 4.0f;
        REQUIRE(v == Vector3(4.0f, 4.0f, 4.0f));

        v *= Vector3(1.0f, 2.0f, 0.5f);
        REQUIRE(v == Vector3(4.0f, 8.0f, 2.0f));

        v /= 2.0f;
        REQUIRE(v == Vector3(2.0f, 4.0f, 1.0f));

        v /= Vector3(2.0f, 2.0f, 1.0f);
        REQUIRE(v == Vector3(1.0f, 2.0f, 1.0f));
    }

    SECTION("Equality and inequality") {
        REQUIRE(Vector3(1.0f, 2.0f, 3.0f) == Vector3(1.0f, 2.0f, 3.0f));
        REQUIRE(Vector3(1.0f, 2.0f, 3.0f) != Vector3(1.0f, 2.0f, 4.0f));
        REQUIRE(Vector3(1.0f, 2.0f, 3.0f) != Vector3(1.0f, 0.0f, 3.0f));
    }
}

TEST_CASE("Vector3 - Basic Math Operations", "[Vector3]") {
    SECTION("Dot, Cross, Length, and LengthSqr") {
        constexpr Vector3 u(1.0f, 0.0f, 0.0f);
        constexpr Vector3 v(0.0f, 1.0f, 0.0f);

        STATIC_REQUIRE(u.Dot(v) == 0.0f);
        STATIC_REQUIRE(u.Cross(v) == Vector3(0.0f, 0.0f, 1.0f));
        STATIC_REQUIRE(v.Cross(u) == Vector3(0.0f, 0.0f, -1.0f));

        constexpr Vector3 d(2.0f, 3.0f, 6.0f);
        STATIC_REQUIRE(d.LengthSqr() == 49.0f);
        REQUIRE_THAT(d.Length(), WithinAbs(7.0f, 1e-6f));
    }

    SECTION("Negate and Invert") {
        constexpr Vector3 v(2.0f, -4.0f, 8.0f);

        STATIC_REQUIRE(v.Negate() == Vector3(-2.0f, 4.0f, -8.0f));
        STATIC_REQUIRE(v.Invert() == Vector3(0.5f, -0.25f, 0.125f));
    }

    SECTION("Distance and DistanceSqr") {
        constexpr Vector3 a(1.0f, 2.0f, 3.0f);
        constexpr Vector3 b(3.0f, 5.0f, 9.0f);

        STATIC_REQUIRE(a.DistanceSqr(b) == 49.0f);
        REQUIRE_THAT(a.Distance(b), WithinAbs(7.0f, 1e-6f));
    }

    SECTION("Normalized") {
        Vector3 v(0.0f, 0.0f, 5.0f);
        Vector3 norm = v.Normalized();
        REQUIRE_THAT(norm.x, WithinAbs(0.0f, 1e-6f));
        REQUIRE_THAT(norm.y, WithinAbs(0.0f, 1e-6f));
        REQUIRE_THAT(norm.z, WithinAbs(1.0f, 1e-6f));

        REQUIRE(Vector3::Zero().Normalized() == Vector3::Zero());
    }
}

TEST_CASE("Vector3 - Geometric and Spatial Functions", "[Vector3]") {
    SECTION("Angle") {
        Vector3 right = Vector3::Right();
        Vector3 up = Vector3::Up();
        constexpr float halfPi = std::numbers::pi_v<float> / 2.0f;

        REQUIRE_THAT(right.Angle(up), WithinAbs(halfPi, 1e-6f));
        REQUIRE_THAT(right.Angle(right), WithinAbs(0.0f, 1e-6f));
    }

    SECTION("Lerp") {
        Vector3 start(0.0f, 10.0f, 20.0f);
        Vector3 end(10.0f, 20.0f, 40.0f);

        Vector3 mid = start.Lerp(end, 0.5f);
        REQUIRE(mid == Vector3(5.0f, 15.0f, 30.0f));
    }

    SECTION("Reflect and Refract") {
        Vector3 incident(1.0f, -1.0f, 0.0f);
        Vector3 normal(0.0f, 1.0f, 0.0f);
        REQUIRE(incident.Reflect(normal) == Vector3(1.0f, 1.0f, 0.0f));

        Vector3 perpIncident(0.0f, -1.0f, 0.0f);
        Vector3 refracted = perpIncident.Refract(normal, 1.0f);
        REQUIRE_THAT(refracted.y, WithinAbs(-1.0f, 1e-6f));

        Vector3 critical(1.0f, 0.0f, 0.0f);
        REQUIRE(critical.Refract(normal, 2.0f) == Vector3::Zero());
    }

    SECTION("RotateByAxisAngle") {
        Vector3 point(1.0f, 0.0f, 0.0f);
        Vector3 axis(0.0f, 1.0f, 0.0f);
        constexpr float halfPi = std::numbers::pi_v<float> / 2.0f;

        Vector3 rotated = point.RotateByAxisAngle(axis, halfPi);
        REQUIRE_THAT(rotated.x, WithinAbs(0.0f, 1e-5f));
        REQUIRE_THAT(rotated.y, WithinAbs(0.0f, 1e-5f));
        REQUIRE_THAT(rotated.z, WithinAbs(-1.0f, 1e-5f));
    }

    SECTION("MoveTowards") {
        Vector3 current(0.0f, 0.0f, 0.0f);
        Vector3 target(0.0f, 10.0f, 0.0f);

        REQUIRE(current.MoveTowards(target, 4.0f) == Vector3(0.0f, 4.0f, 0.0f));
        REQUIRE(current.MoveTowards(target, 12.0f) == target);
    }
}

TEST_CASE("Vector3 - Clamping and Tolerances", "[Vector3]") {
    SECTION("Component-wise and Magnitude Clamp") {
        Vector3 v(-5.0f, 5.0f, 15.0f);
        Vector3 min(0.0f, 0.0f, 0.0f);
        Vector3 max(10.0f, 10.0f, 10.0f);

        REQUIRE(v.Clamp(min, max) == Vector3(0.0f, 5.0f, 10.0f));

        Vector3 dir(0.0f, 0.0f, 10.0f);
        REQUIRE(dir.ClampValue(2.0f, 5.0f) == Vector3(0.0f, 0.0f, 5.0f));
        REQUIRE(dir.ClampValue(12.0f, 20.0f) == Vector3(0.0f, 0.0f, 12.0f));
        REQUIRE(Vector3::Zero().ClampValue(1.0f, 5.0f) == Vector3::Zero());
    }

    SECTION("Fuzzy Equals") {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(1.0000005f, 2.0f, 2.9999995f);
        Vector3 c(1.01f, 2.0f, 3.0f);

        REQUIRE(a.Equals(b));
        REQUIRE_FALSE(a.Equals(c));
        REQUIRE(a.Equals(c, 0.02f));
    }
}