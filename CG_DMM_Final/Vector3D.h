#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>

//
// Class: Vector3D
// Represents a 3D vector with operations for vector arithmetic, normalization, and geometric calculations.
//
class Vector3D {
public:
    double x, y, z; // Components of the vector

    //
    // Constructor: Vector3D
    // Initializes a vector with the specified x, y, and z components.
    // Parameters:
    //   - x: The x-component of the vector.
    //   - y: The y-component of the vector.
    //   - z: The z-component of the vector.
    //
    Vector3D(double x, double y, double z);

    //
    // Default Constructor: Vector3D
    // Initializes a vector with all components set to 0.
    //
    Vector3D();

    //
    // Destructor: ~Vector3D
    // Default destructor for the Vector3D class.
    //
    ~Vector3D();

    //
    // Operator: -
    // Negates all components of the vector.
    // Returns:
    //   A new Vector3D with negated components.
    //
    Vector3D operator-() const;

    //
    // Operator: +
    // Adds the components of two vectors.
    // Parameters:
    //   - v: The vector to add.
    // Returns:
    //   A new Vector3D with the summed components.
    //
    Vector3D operator+(const Vector3D& v) const;

    //
    // Operator: -
    // Subtracts the components of another vector from this vector.
    // Parameters:
    //   - v: The vector to subtract.
    // Returns:
    //   A new Vector3D with the subtracted components.
    //
    Vector3D operator-(const Vector3D& v) const;

    //
    // Operator: *
    // Multiplies the vector components by a scalar.
    // Parameters:
    //   - scalar: The scalar to multiply with.
    // Returns:
    //   A new Vector3D with scaled components.
    //
    Vector3D operator*(double scalar) const;

    //
    // Operator: *
    // Multiplies a scalar with a vector (friend function).
    // Parameters:
    //   - scalar: The scalar to multiply with.
    //   - v: The vector to scale.
    // Returns:
    //   A new Vector3D with scaled components.
    //
    friend Vector3D operator*(double scalar, const Vector3D& v);

    //
    // Operator: /
    // Divides the vector components by a scalar.
    // Parameters:
    //   - scalar: The scalar to divide by.
    // Returns:
    //   A new Vector3D with divided components.
    //
    Vector3D operator/(double scalar) const;

    //
    // Method: dot
    // Calculates the dot product of this vector with another vector.
    // Parameters:
    //   - v: The vector to calculate the dot product with.
    // Returns:
    //   The dot product (a scalar value).
    //
    double dot(const Vector3D& v) const;

    //
    // Method: cross
    // Calculates the cross product of this vector with another vector.
    // Parameters:
    //   - v: The vector to calculate the cross product with.
    // Returns:
    //   A new Vector3D representing the cross product.
    //
    Vector3D cross(const Vector3D& v) const;

    //
    // Method: normalize
    // Normalizes the vector to have a length of 1.
    // Returns:
    //   A new Vector3D representing the normalized vector.
    // Notes:
    //   If the vector length is zero, returns a zero vector.
    //
    Vector3D normalize() const;

    //
    // Method: length
    // Calculates the length (magnitude) of the vector.
    // Returns:
    //   The length of the vector.
    //
    double length() const;

    //
    // Method: lengthSquared
    // Calculates the squared length of the vector (avoids square root for efficiency).
    // Returns:
    //   The squared length of the vector.
    //
    double lengthSquared() const;

    //
    // Operator: <<
    // Outputs the vector components in the format "<x, y, z>".
    // Parameters:
    //   - out: The output stream.
    //   - v: The vector to output.
    // Returns:
    //   The modified output stream.
    //
    friend std::ostream& operator<<(std::ostream& out, const Vector3D& v);

    //
    // Operator: ==
    // Compares two vectors for equality, within a small epsilon threshold.
    // Parameters:
    //   - v: The vector to compare with.
    // Returns:
    //   true if the vectors are equal, false otherwise.
    //
    bool operator==(const Vector3D& v) const;

    //
    // Operator: !=
    // Compares two vectors for inequality.
    // Parameters:
    //   - v: The vector to compare with.
    // Returns:
    //   true if the vectors are not equal, false otherwise.
    //
    bool operator!=(const Vector3D& v) const;

    //
    // Method: randomHemisphere
    // Generates a random direction within a hemisphere oriented around this vector.
    // Uses cosine-weighted sampling for realistic diffuse scattering.
    // Returns:
    //   A new Vector3D representing the random direction.
    //
    Vector3D randomHemisphere() const;
};

#endif // VECTOR3D_H