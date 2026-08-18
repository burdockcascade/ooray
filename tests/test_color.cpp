#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "color.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Color - Constructors and Interoperability", "[Color]") {
    SECTION("Default constructor initializes to black with full opacity") {
        ooray::Color c;
        REQUIRE(c.r == 0);
        REQUIRE(c.g == 0);
        REQUIRE(c.b == 0);
        REQUIRE(c.a == 255);
    }

    SECTION("Explicit component constructor with default alpha") {
        ooray::Color c(128, 64, 32);
        REQUIRE(c.r == 128);
        REQUIRE(c.g == 64);
        REQUIRE(c.b == 32);
        REQUIRE(c.a == 255);
    }

    SECTION("Hex value constructor") {
        ooray::Color c(0xFF8844FF);
        REQUIRE(c.r == 0xFF);
        REQUIRE(c.g == 0x88);
        REQUIRE(c.b == 0x44);
        REQUIRE(c.a == 0xFF);
    }

    SECTION("Conversion to and from C-struct ::Color") {
        ::Color raw{200, 100, 50, 255};
        ooray::Color wrapped = raw;

        REQUIRE(wrapped.r == 200);
        REQUIRE(wrapped.g == 100);
        REQUIRE(wrapped.b == 50);
        REQUIRE(wrapped.a == 255);

        ::Color extracted = wrapped;
        REQUIRE(extracted.r == 200);
        REQUIRE(extracted.g == 100);
        REQUIRE(extracted.b == 50);
        REQUIRE(extracted.a == 255);
    }

    SECTION("Static Color Presets") {
        REQUIRE(ooray::Color::Red() == ooray::Color(230, 41, 55, 255));
        REQUIRE(ooray::Color::Green() == ooray::Color(0, 228, 48, 255));
        REQUIRE(ooray::Color::White() == ooray::Color(255, 255, 255, 255));
        REQUIRE(ooray::Color::Black() == ooray::Color(0, 0, 0, 255));
    }
}

TEST_CASE("ooray::Color - Conversions and Utility Methods", "[Color]") {
    SECTION("Conversion to Vector4 (Normalized float components)") {
        ooray::Color c(255, 0, 0, 255);
        Vector4 norm = c.ToVector4();

        REQUIRE_THAT(norm.x, WithinRel(1.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinRel(0.0f, 0.0001f));
        REQUIRE_THAT(norm.z, WithinRel(0.0f, 0.0001f));
        REQUIRE_THAT(norm.w, WithinRel(1.0f, 0.0001f));
    }

    SECTION("Normalized Vector4 back to Color") {
        Vector4 norm{0.0f, 1.0f, 0.0f, 1.0f};
        ooray::Color c = ooray::Color::FromNormalized(norm);

        REQUIRE(c == ooray::Color(0, 255, 0, 255));
    }

}

TEST_CASE("ooray::Color - Color Transformations and Operations", "[Color]") {
    SECTION("Fade method creates color with scaled alpha") {
        ooray::Color red = ooray::Color::Red();
        ooray::Color faded = red.Fade(0.5f);

        REQUIRE(faded.r == red.r);
        REQUIRE(faded.g == red.g);
        REQUIRE(faded.b == red.b);
        REQUIRE(faded.a == 127);
    }

    SECTION("In-place ApplyFade mutates color directly") {
        ooray::Color c = ooray::Color::White();
        c.ApplyFade(0.2f);

        REQUIRE(c.a == 51);
    }

    SECTION("Linear Interpolation (Lerp)") {
        ooray::Color black = ooray::Color::Black();
        ooray::Color white = ooray::Color::White();

        ooray::Color gray = black.Lerp(white, 0.5f);
        REQUIRE(gray.r == 127);
        REQUIRE(gray.g == 127);
        REQUIRE(gray.b == 127);
        REQUIRE(gray.a == 255);
    }

    SECTION("Color Tinting") {
        ooray::Color white = ooray::Color::White();
        ooray::Color red = ooray::Color::Red();

        ooray::Color tinted = white.Tint(red);
        REQUIRE(tinted == red);
    }

    SECTION("Contrast and Brightness adjustment") {
        ooray::Color c(100, 100, 100, 255);
        ooray::Color brighter = c.Brightness(0.5f);

        REQUIRE(brighter.r > c.r);
        REQUIRE(brighter.g > c.g);
        REQUIRE(brighter.b > c.b);
    }
}