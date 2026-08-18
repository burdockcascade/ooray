#pragma once

#include <raylib.h>
#include <raymath.h>
#include <cstdint>
#include <ostream>

namespace ooray {

    class Color : public ::Color {
    public:
        // Constructors
        constexpr Color() noexcept : ::Color{0, 0, 0, 255} {}
        constexpr Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255) noexcept
            : ::Color{r_, g_, b_, a_} {}
        constexpr Color(const ::Color& color) noexcept
            : ::Color{color.r, color.g, color.b, color.a} {}

        // Construct from packed 32-bit int or hex (e.g., Color(0xFF0000FF))
        explicit constexpr Color(std::uint32_t hexValue) noexcept
            : ::Color{
                static_cast<unsigned char>((hexValue >> 24) & 0xFF),
                static_cast<unsigned char>((hexValue >> 16) & 0xFF),
                static_cast<unsigned char>((hexValue >> 8) & 0xFF),
                static_cast<unsigned char>(hexValue & 0xFF)
            } {}

        // Implicit conversion back to Raylib's C struct
        constexpr operator ::Color() const noexcept { return {r, g, b, a}; }

        // Static Common Preset Colors
        [[nodiscard]] static constexpr Color LightGray() noexcept { return ::LIGHTGRAY; }
        [[nodiscard]] static constexpr Color Gray() noexcept      { return ::GRAY; }
        [[nodiscard]] static constexpr Color DarkGray() noexcept  { return ::DARKGRAY; }
        [[nodiscard]] static constexpr Color Yellow() noexcept    { return ::YELLOW; }
        [[nodiscard]] static constexpr Color Gold() noexcept      { return ::GOLD; }
        [[nodiscard]] static constexpr Color Orange() noexcept    { return ::ORANGE; }
        [[nodiscard]] static constexpr Color Pink() noexcept      { return ::PINK; }
        [[nodiscard]] static constexpr Color Red() noexcept       { return ::RED; }
        [[nodiscard]] static constexpr Color Maroon() noexcept    { return ::MAROON; }
        [[nodiscard]] static constexpr Color Green() noexcept     { return ::GREEN; }
        [[nodiscard]] static constexpr Color Lime() noexcept      { return ::LIME; }
        [[nodiscard]] static constexpr Color DarkGreen() noexcept { return ::DARKGREEN; }
        [[nodiscard]] static constexpr Color SkyBlue() noexcept   { return ::SKYBLUE; }
        [[nodiscard]] static constexpr Color Blue() noexcept      { return ::BLUE; }
        [[nodiscard]] static constexpr Color DarkBlue() noexcept  { return ::DARKBLUE; }
        [[nodiscard]] static constexpr Color Purple() noexcept    { return ::PURPLE; }
        [[nodiscard]] static constexpr Color Violet() noexcept    { return ::VIOLET; }
        [[nodiscard]] static constexpr Color DarkPurple() noexcept{ return ::DARKPURPLE; }
        [[nodiscard]] static constexpr Color Beige() noexcept     { return ::BEIGE; }
        [[nodiscard]] static constexpr Color Brown() noexcept     { return ::BROWN; }
        [[nodiscard]] static constexpr Color DarkBrown() noexcept { return ::DARKBROWN; }
        [[nodiscard]] static constexpr Color White() noexcept     { return ::WHITE; }
        [[nodiscard]] static constexpr Color Black() noexcept     { return ::BLACK; }
        [[nodiscard]] static constexpr Color Blank() noexcept     { return ::BLANK; }
        [[nodiscard]] static constexpr Color Magenta() noexcept   { return ::MAGENTA; }
        [[nodiscard]] static constexpr Color RayWhite() noexcept  { return ::RAYWHITE; }

        // Color Conversion & Generators
        [[nodiscard]] Vector4 ToVector4() const noexcept { return ColorNormalize(*this); }
        [[nodiscard]] std::uint32_t ToInt() const noexcept { return ColorToInt(*this); }

        [[nodiscard]] static Color FromNormalized(Vector4 normalized) noexcept {
            return ColorFromNormalized(normalized);
        }

        [[nodiscard]] static Color FromHSV(float hue, float saturation, float value) noexcept {
            return ColorFromHSV(hue, saturation, value);
        }

        [[nodiscard]] Vector3 ToHSV() const noexcept { return ColorToHSV(*this); }

        // Color Operations & Modifications (Const / Immutable)
        [[nodiscard]] Color Fade(float alpha) const noexcept { return ::Fade(*this, alpha); }
        [[nodiscard]] Color Alpha(float alpha) const noexcept { return ColorAlpha(*this, alpha); }
        [[nodiscard]] Color AlphaBlend(Color src, Color tint) const noexcept { return ColorAlphaBlend(*this, src, tint); }
        [[nodiscard]] Color Lerp(Color target, float factor) const noexcept { return ColorLerp(*this, target, factor); }
        [[nodiscard]] Color Tint(Color tint) const noexcept { return ColorTint(*this, tint); }
        [[nodiscard]] Color Contrast(float contrast) const noexcept { return ColorContrast(*this, contrast); }
        [[nodiscard]] Color Brightness(float factor) const noexcept { return ColorBrightness(*this, factor); }

        // In-place Mutating Operations
        Color& ApplyFade(float alpha) noexcept { *this = Fade(alpha); return *this; }
        Color& ApplyAlpha(float alpha) noexcept { *this = Alpha(alpha); return *this; }
        Color& ApplyTint(Color tint) noexcept { *this = Tint(tint); return *this; }
        Color& ApplyContrast(float contrast) noexcept { *this = Contrast(contrast); return *this; }
        Color& ApplyBrightness(float factor) noexcept { *this = Brightness(factor); return *this; }

        // Operators
        bool operator==(const Color& rhs) const noexcept {
            return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
        }

        // Stream operator for debugging
        friend std::ostream& operator<<(std::ostream& os, const Color& c) {
            return os << "Color(" << static_cast<int>(c.r) << ", "
                      << static_cast<int>(c.g) << ", "
                      << static_cast<int>(c.b) << ", "
                      << static_cast<int>(c.a) << ")";
        }
    };

} // namespace ooray