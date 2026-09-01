#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numbers>

#include "oor_vector2.hpp"

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;
using ooray::Vector2;

TEST_CASE("Vector2 - Construction and Static Helpers", "[Vector2]") {
    SECTION("Default and parameterized constructors") {
        constexpr Vector2 def;
        STATIC_REQUIRE(def.x == 0.0f);
        STATIC_REQUIRE(def.y == 0.0f);

        constexpr Vector2 custom(3.5f, -2.1f);
        STATIC_REQUIRE(custom.x == 3.5f);
        STATIC_REQUIRE(custom.y == -2.1f);
    }

    SECTION("Static factory methods") {
        constexpr Vector2 zero = Vector2::Zero();
        STATIC_REQUIRE(zero.x == 0.0f);
        STATIC_REQUIRE(zero.y == 0.0f);

        constexpr Vector2 one = Vector2::One();
        STATIC_REQUIRE(one.x == 1.0f);
        STATIC_REQUIRE(one.y == 1.0f);
    }
}

TEST_CASE("Vector2 - Arithmetic Operators", "[Vector2]") {
    Vector2 a(4.0f, -2.0f);
    Vector2 b(1.0f, 3.0f);

    SECTION("Binary operators") {
        Vector2 sum = a + b;
        REQUIRE(sum.x == 5.0f);
        REQUIRE(sum.y == 1.0f);

        Vector2 diff = a - b;
        REQUIRE(diff.x == 3.0f);
        REQUIRE(diff.y == -5.0f);

        Vector2 scaled = a * 2.5f;
        REQUIRE(scaled.x == 10.0f);
        REQUIRE(scaled.y == -5.0f);

        Vector2 divided = a / 2.0f;
        REQUIRE(divided.x == 2.0f);
        REQUIRE(divided.y == -1.0f);
    }

    SECTION("Compound assignment operators") {
        Vector2 v(2.0f, 4.0f);

        v += Vector2(1.0f, 1.0f);
        REQUIRE(v == Vector2(3.0f, 5.0f));

        v -= Vector2(2.0f, 1.0f);
        REQUIRE(v == Vector2(1.0f, 4.0f));

        v *= 3.0f;
        REQUIRE(v == Vector2(3.0f, 12.0f));

        v /= 2.0f;
        REQUIRE(v == Vector2(1.5f, 6.0f));
    }

    SECTION("Equality and inequality") {
        REQUIRE(Vector2(2.0f, 3.0f) == Vector2(2.0f, 3.0f));
        REQUIRE(Vector2(2.0f, 3.0f) != Vector2(2.0f, 4.0f));
        REQUIRE(Vector2(2.0f, 3.0f) != Vector2(1.0f, 3.0f));
    }
}

TEST_CASE("Vector2 - Basic Math Operations", "[Vector2]") {
    SECTION("Dot product, Length, and LengthSqr") {
        Vector2 v(3.0f, 4.0f);
        Vector2 u(2.0f, -1.0f);

        STATIC_REQUIRE(Vector2(3.0f, 4.0f).Dot(Vector2(2.0f, -1.0f)) == 2.0f);
        STATIC_REQUIRE(Vector2(3.0f, 4.0f).LengthSqr() == 25.0f);
        REQUIRE_THAT(v.Length(), WithinAbs(5.0f, 1e-6f));
    }

    SECTION("Negate and Invert") {
        constexpr Vector2 v(2.0f, -4.0f);

        constexpr Vector2 neg = v.Negate();
        STATIC_REQUIRE(neg.x == -2.0f);
        STATIC_REQUIRE(neg.y == 4.0f);

        constexpr Vector2 inv = v.Invert();
        STATIC_REQUIRE(inv.x == 0.5f);
        STATIC_REQUIRE(inv.y == -0.25f);
    }

    SECTION("Distance and DistanceSqr") {
        constexpr Vector2 a(1.0f, 2.0f);
        constexpr Vector2 b(4.0f, 6.0f);

        STATIC_REQUIRE(a.DistanceSqr(b) == 25.0f);
        REQUIRE_THAT(a.Distance(b), WithinAbs(5.0f, 1e-6f));
    }

    SECTION("Normalized") {
        Vector2 v(0.0f, 5.0f);
        Vector2 normalized = v.Normalized();
        REQUIRE_THAT(normalized.x, WithinAbs(0.0f, 1e-6f));
        REQUIRE_THAT(normalized.y, WithinAbs(1.0f, 1e-6f));

        Vector2 zero = Vector2::Zero().Normalized();
        REQUIRE(zero == Vector2::Zero());
    }
}

TEST_CASE("Vector2 - Geometric and Trigonometric Functions", "[Vector2]") {
    SECTION("Angle and LineAngle") {
        Vector2 right(1.0f, 0.0f);
        Vector2 up(0.0f, 1.0f);
        constexpr float halfPi = std::numbers::pi_v<float> / 2.0f;

        REQUIRE_THAT(right.Angle(up), WithinAbs(halfPi, 1e-6f));
        REQUIRE_THAT(right.LineAngle(Vector2(1.0f, 2.0f)), WithinAbs(halfPi, 1e-6f));
    }

    SECTION("Rotate") {
        Vector2 v(1.0f, 0.0f);
        constexpr float halfPi = std::numbers::pi_v<float> / 2.0f;
        Vector2 rotated = v.Rotate(halfPi);

        REQUIRE_THAT(rotated.x, WithinAbs(0.0f, 1e-6f));
        REQUIRE_THAT(rotated.y, WithinAbs(1.0f, 1e-6f));
    }

    SECTION("Lerp") {
        Vector2 start(0.0f, 10.0f);
        Vector2 end(10.0f, 20.0f);

        Vector2 mid = start.Lerp(end, 0.5f);
        REQUIRE(mid.x == 5.0f);
        REQUIRE(mid.y == 15.0f);
    }

    SECTION("Reflect") {
        Vector2 incident(1.0f, -1.0f);
        Vector2 normal(0.0f, 1.0f); // Upward floor normal
        Vector2 reflected = incident.Reflect(normal);

        REQUIRE(reflected.x == 1.0f);
        REQUIRE(reflected.y == 1.0f);
    }

    SECTION("Refract") {
        Vector2 incident(0.0f, -1.0f);
        Vector2 normal(0.0f, 1.0f);

        // Perpendicular entry transmits straight through
        Vector2 refracted = incident.Refract(normal, 1.0f);
        REQUIRE_THAT(refracted.x, WithinAbs(0.0f, 1e-6f));
        REQUIRE_THAT(refracted.y, WithinAbs(-1.0f, 1e-6f));

        // Total internal reflection condition returns Zero
        Vector2 criticalIncident(1.0f, 0.0f);
        Vector2 totalReflect = criticalIncident.Refract(normal, 2.0f);
        REQUIRE(totalReflect == Vector2::Zero());
    }

    SECTION("MoveTowards") {
        Vector2 current(0.0f, 0.0f);
        Vector2 target(10.0f, 0.0f);

        // Step within remaining distance
        Vector2 step1 = current.MoveTowards(target, 4.0f);
        REQUIRE(step1.x == 4.0f);
        REQUIRE(step1.y == 0.0f);

        // Overshoot clamps to target
        Vector2 step2 = current.MoveTowards(target, 15.0f);
        REQUIRE(step2 == target);
    }
}

TEST_CASE("Vector2 - Clamping and Tolerances", "[Vector2]") {
    SECTION("Component-wise Clamp") {
        Vector2 v(-5.0f, 15.0f);
        Vector2 min(-1.0f, 0.0f);
        Vector2 max(2.0f, 10.0f);

        Vector2 clamped = v.Clamp(min, max);
        REQUIRE(clamped.x == -1.0f);
        REQUIRE(clamped.y == 10.0f);
    }

    SECTION("Magnitude ClampValue") {
        Vector2 v(0.0f, 10.0f);

        // Max magnitude clamp
        Vector2 clampedMax = v.ClampValue(1.0f, 5.0f);
        REQUIRE_THAT(clampedMax.Length(), WithinAbs(5.0f, 1e-6f));
        REQUIRE(clampedMax.y == 5.0f);

        // Min magnitude clamp
        Vector2 clampedMin = v.ClampValue(15.0f, 20.0f);
        REQUIRE_THAT(clampedMin.Length(), WithinAbs(15.0f, 1e-6f));
        REQUIRE(clampedMin.y == 15.0f);

        // Zero vector clamp returns Zero
        Vector2 clampedZero = Vector2::Zero().ClampValue(1.0f, 5.0f);
        REQUIRE(clampedZero == Vector2::Zero());
    }

    SECTION("Fuzzy Equals") {
        Vector2 a(1.0f, 2.0f);
        Vector2 b(1.0000005f, 1.9999995f);
        Vector2 c(1.01f, 2.0f);

        REQUIRE(a.Equals(b));
        REQUIRE_FALSE(a.Equals(c));
        REQUIRE(a.Equals(c, 0.02f));
    }
}