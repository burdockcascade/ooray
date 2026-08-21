#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ooray.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Rectangle - Constructors and Interoperability", "[Rectangle]") {
    SECTION("Default constructor initializes to zeros") {
        OORAY::Rectangle r;
        REQUIRE(r.x == 0.0f);
        REQUIRE(r.y == 0.0f);
        REQUIRE(r.width == 0.0f);
        REQUIRE(r.height == 0.0f);
    }

    SECTION("Scalar value constructor") {
        OORAY::Rectangle r(10.0f, 20.0f, 100.0f, 200.0f);
        REQUIRE(r.x == 10.0f);
        REQUIRE(r.y == 20.0f);
        REQUIRE(r.width == 100.0f);
        REQUIRE(r.height == 200.0f);
    }

    SECTION("Vector2 position and size constructor") {
        OORAY::Vector2 pos(15.0f, 25.0f);
        OORAY::Vector2 size(50.0f, 60.0f);
        OORAY::Rectangle r(pos, size);

        REQUIRE(r.GetPosition() == pos);
        REQUIRE(r.GetSize() == size);
    }

    SECTION("Conversion to and from C-struct ::Rectangle") {
        ::Rectangle raw{5.0f, 10.0f, 30.0f, 40.0f};
        OORAY::Rectangle wrapped = raw;

        REQUIRE(wrapped.x == 5.0f);
        REQUIRE(wrapped.y == 10.0f);
        REQUIRE(wrapped.width == 30.0f);
        REQUIRE(wrapped.height == 40.0f);

        ::Rectangle extracted = wrapped;
        REQUIRE(extracted.x == 5.0f);
        REQUIRE(extracted.y == 10.0f);
        REQUIRE(extracted.width == 30.0f);
        REQUIRE(extracted.height == 40.0f);
    }
}

TEST_CASE("ooray::Rectangle - Bounds and Edge Helpers", "[Rectangle]") {
    OORAY::Rectangle r(10.0f, 20.0f, 100.0f, 50.0f);

    SECTION("Edges and Bounds") {
        REQUIRE(r.Left() == 10.0f);
        REQUIRE(r.Right() == 110.0f);
        REQUIRE(r.Top() == 20.0f);
        REQUIRE(r.Bottom() == 70.0f);
    }

    SECTION("Center calculation") {
        OORAY::Vector2 center = r.Center();
        REQUIRE_THAT(center.x, WithinRel(60.0f, 0.0001f));
        REQUIRE_THAT(center.y, WithinRel(45.0f, 0.0001f));
    }

    SECTION("Setters via Vector2") {
        r.SetPosition({0.0f, 0.0f});
        r.SetSize({200.0f, 200.0f});
        REQUIRE(r.x == 0.0f);
        REQUIRE(r.y == 0.0f);
        REQUIRE(r.width == 200.0f);
        REQUIRE(r.height == 200.0f);
    }
}

TEST_CASE("ooray::Rectangle - Collisions", "[Rectangle]") {
    OORAY::Rectangle a(0.0f, 0.0f, 100.0f, 100.0f);
    OORAY::Rectangle b(50.0f, 50.0f, 100.0f, 100.0f);
    OORAY::Rectangle c(200.0f, 200.0f, 50.0f, 50.0f);

    SECTION("Point containment") {
        REQUIRE(a.Contains({50.0f, 50.0f}));
        REQUIRE_FALSE(a.Contains({150.0f, 50.0f}));
    }

    SECTION("Rectangle overlap check") {
        REQUIRE(a.Overlaps(b));
        REQUIRE_FALSE(a.Overlaps(c));
    }

    SECTION("Get collision intersection rectangle") {
        OORAY::Rectangle intersection = a.GetCollision(b);
        REQUIRE(intersection == OORAY::Rectangle(50.0f, 50.0f, 50.0f, 50.0f));
    }
}