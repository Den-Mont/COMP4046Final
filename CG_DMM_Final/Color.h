#ifndef COLOR_H
#define COLOR_H

//
// Class: Color
// Represents a color using RGB components, with support for basic color operations.
//
class Color {
public:
    double r, g, b; 
    // Public Members:
    //   - r: Red component of the color (range: 0.0 to 1.0).
    //   - g: Green component of the color (range: 0.0 to 1.0).
    //   - b: Blue component of the color (range: 0.0 to 1.0).

    //
    // Constructor: Color
    // Initializes the color with the specified RGB values.
    // Parameters:
    //   - r: Initial red component value.
    //   - g: Initial green component value.
    //   - b: Initial blue component value.
    //
    Color(double r, double g, double b);

    //
    // Constructor: Color
    // Default constructor, initializes the color to black (r = g = b = 0.0).
    //
    Color();

    //
    // Destructor: ~Color
    // Default destructor for the Color class.
    //
    ~Color();

    //
    // Method: clamp
    // Clamps the RGB components to the range [0.0, 1.0].
    //
    void clamp();

    //
    // Operator: +
    // Adds the RGB components of two Color objects.
    // Parameters:
    //   - c: The Color object to be added.
    // Returns:
    //   A new Color object with the summed RGB values.
    //
    Color operator+(const Color& c) const;

    //
    // Operator: *
    // Multiplies the RGB components of the Color object by a scalar.
    // Parameters:
    //   - scalar: The scalar value for multiplication.
    // Returns:
    //   A new Color object with the scaled RGB values.
    //
    Color operator*(double scalar) const;

    //
    // Operator: *
    // Multiplies the RGB components of two Color objects component-wise.
    // Parameters:
    //   - c: The Color object to multiply with.
    // Returns:
    //   A new Color object with the component-wise multiplied RGB values.
    //
    Color operator*(const Color& c) const;
};

#endif // COLOR_H