#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ooray.hpp"

using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Color - Constructors and Interoperability", "[Color]") {
    SECTION("Default constructor initializes to black with full opacity") {
        OORAY::Color c;
        REQUIRE(c.r == 0);
        REQUIRE(c.g == 0);
        REQUIRE(c.b == 0);
        REQUIRE(c.a == 255);
    }

    SECTION("Explicit component constructor with default alpha") {
        OORAY::Color c(128, 64, 32);
        REQUIRE(c.r == 128);
        REQUIRE(c.g == 64);
        REQUIRE(c.b == 32);
        REQUIRE(c.a == 255);
    }

    SECTION("Hex value constructor") {
        OORAY::Color c(0xFF8844FF);
        REQUIRE(c.r == 0xFF);
        REQUIRE(c.g == 0x88);
        REQUIRE(c.b == 0x44);
        REQUIRE(c.a == 0xFF);
    }

    SECTION("Conversion to and from C-struct ::Color") {
        ::Color raw{200, 100, 50, 255};
        OORAY::Color wrapped = raw;

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
        REQUIRE(OORAY::Color::Red() == OORAY::Color(230, 41, 55, 255));
        REQUIRE(OORAY::Color::Green() == OORAY::Color(0, 228, 48, 255));
        REQUIRE(OORAY::Color::White() == OORAY::Color(255, 255, 255, 255));
        REQUIRE(OORAY::Color::Black() == OORAY::Color(0, 0, 0, 255));
    }
}

TEST_CASE("ooray::Color - Conversions and Utility Methods", "[Color]") {
    SECTION("Conversion to Vector4 (Normalized float components)") {
        OORAY::Color c(255, 0, 0, 255);
        Vector4 norm = c.ToVector4();

        REQUIRE_THAT(norm.x, WithinRel(1.0f, 0.0001f));
        REQUIRE_THAT(norm.y, WithinRel(0.0f, 0.0001f));
        REQUIRE_THAT(norm.z, WithinRel(0.0f, 0.0001f));
        REQUIRE_THAT(norm.w, WithinRel(1.0f, 0.0001f));
    }

    SECTION("Normalized Vector4 back to Color") {
        Vector4 norm{0.0f, 1.0f, 0.0f, 1.0f};
        OORAY::Color c = OORAY::Color::FromNormalized(norm);

        REQUIRE(c == OORAY::Color(0, 255, 0, 255));
    }

}

TEST_CASE("ooray::Color - Color Transformations and Operations", "[Color]") {
    SECTION("Fade method creates color with scaled alpha") {
        OORAY::Color red = OORAY::Color::Red();
        OORAY::Color faded = red.GetFade(0.5f);

        REQUIRE(faded.r == red.r);
        REQUIRE(faded.g == red.g);
        REQUIRE(faded.b == red.b);
        REQUIRE(faded.a == 127);
    }

    SECTION("In-place ApplyFade mutates color directly") {
        OORAY::Color c = OORAY::Color::White();
        c.ApplyFade(0.2f);

        REQUIRE(c.a == 51);
    }

    SECTION("Linear Interpolation (Lerp)") {
        OORAY::Color black = OORAY::Color::Black();
        OORAY::Color white = OORAY::Color::White();

        OORAY::Color gray = black.GetLerp(white, 0.5f);
        REQUIRE(gray.r == 127);
        REQUIRE(gray.g == 127);
        REQUIRE(gray.b == 127);
        REQUIRE(gray.a == 255);
    }

    SECTION("Color Tinting") {
        OORAY::Color white = OORAY::Color::White();
        OORAY::Color red = OORAY::Color::Red();

        OORAY::Color tinted = white.GetTint(red);
        REQUIRE(tinted == red);
    }

    SECTION("Contrast and Brightness adjustment") {
        OORAY::Color c(100, 100, 100, 255);
        OORAY::Color brighter = c.GetBrightness(0.5f);

        REQUIRE(brighter.r > c.r);
        REQUIRE(brighter.g > c.g);
        REQUIRE(brighter.b > c.b);
    }
}