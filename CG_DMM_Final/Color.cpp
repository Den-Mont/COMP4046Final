#include "Color.h"
#include <algorithm>

//
// Constructor: Initializes the color with the given red, green, and blue values.
// Parameters:
//   - r: Red component of the color.
//   - g: Green component of the color.
//   - b: Blue component of the color.
//
Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}

//
// Default Constructor: Initializes the color to black (RGB values are 0.0).
//
Color::Color() : r(0.0), g(0.0), b(0.0) {}

//
// Destructor: Default destructor for the Color class.
//
Color::~Color() {}

//
// Method: clamp
// Clamps the red, green, and blue values to the range [0.0, 1.0].
// Ensures that the color components remain within a valid range.
//
void Color::clamp() {
    r = std::min(1.0, std::max(0.0, r));
    g = std::min(1.0, std::max(0.0, g));
    b = std::min(1.0, std::max(0.0, b));
}

//
// Operator: +
// Adds the corresponding RGB components of two colors.
// Parameters:
//   - c: The color to be added.
// Returns:
//   A new Color object with the summed RGB values.
//
Color Color::operator+(const Color& c) const {
    return Color(r + c.r, g + c.g, b + c.b);
}

//
// Operator: *
// Scales the RGB components of the color by a scalar value.
// Parameters:
//   - scalar: The scalar value to multiply with.
// Returns:
//   A new Color object with the scaled RGB values.
//
Color Color::operator*(double scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

//
// Operator: *
// Multiplies the corresponding RGB components of two colors component-wise.
// Parameters:
//   - c: The color to be multiplied with.
// Returns:
//   A new Color object with the component-wise multiplied RGB values.
//
Color Color::operator*(const Color& c) const {
    return Color(r * c.r, g * c.g, b * c.b);
}