#include "Vector3D.h"
#include <cmath>
#include <cstdlib>
#include "RayTracer.h" // for randDouble()

//
// Constructor: Vector3D
// Initializes a 3D vector with the specified x, y, and z components.
// Parameters:
//   - x: The x-component of the vector.
//   - y: The y-component of the vector.
//   - z: The z-component of the vector.
//
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

//
// Default Constructor: Vector3D
// Initializes a 3D vector with all components set to 0.
//
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}

//
// Destructor: ~Vector3D
// Default destructor for the Vector3D class.
//
Vector3D::~Vector3D() {}

//
// Operator: -
// Negates all components of the vector.
// Returns:
//   A new Vector3D with negated components.
//
Vector3D Vector3D::operator-() const {
    return Vector3D(-x, -y, -z);
}

//
// Operator: +
// Adds the components of two vectors.
// Parameters:
//   - v: The vector to add.
// Returns:
//   A new Vector3D with the summed components.
//
Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

//
// Operator: -
// Subtracts the components of another vector from this vector.
// Parameters:
//   - v: The vector to subtract.
// Returns:
//   A new Vector3D with the subtracted components.
//
Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

//
// Operator: *
// Multiplies the vector components by a scalar.
// Parameters:
//   - scalar: The scalar to multiply with.
// Returns:
//   A new Vector3D with scaled components.
//
Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

//
// Operator: *
// Multiplies a scalar with a vector (friend function).
// Parameters:
//   - scalar: The scalar to multiply with.
//   - v: The vector to scale.
// Returns:
//   A new Vector3D with scaled components.
//
Vector3D operator*(double scalar, const Vector3D& v) {
    return Vector3D(v.x * scalar, v.y * scalar, v.z * scalar);
}

//
// Operator: /
// Divides the vector components by a scalar.
// Parameters:
//   - scalar: The scalar to divide by.
// Returns:
//   A new Vector3D with divided components.
//
Vector3D Vector3D::operator/(double scalar) const {
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

//
// Method: dot
// Calculates the dot product of this vector with another vector.
// Parameters:
//   - v: The vector to calculate the dot product with.
// Returns:
//   The dot product (a scalar value).
//
double Vector3D::dot(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

//
// Method: cross
// Calculates the cross product of this vector with another vector.
// Parameters:
//   - v: The vector to calculate the cross product with.
// Returns:
//   A new Vector3D representing the cross product.
//
Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

//
// Method: normalize
// Normalizes the vector to have a length of 1.
// Returns:
//   A new Vector3D representing the normalized vector.
// Notes:
//   If the vector length is zero, returns a zero vector.
//
Vector3D Vector3D::normalize() const {
    double len = length();
    if (len == 0) return Vector3D(0, 0, 0);
    return Vector3D(x / len, y / len, z / len);
}

//
// Method: length
// Calculates the length (magnitude) of the vector.
// Returns:
//   The length of the vector.
//
double Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

//
// Method: lengthSquared
// Calculates the squared length of the vector (avoids square root for efficiency).
// Returns:
//   The squared length of the vector.
//
double Vector3D::lengthSquared() const {
    return x * x + y * y + z * z;
}

//
// Operator: <<
// Outputs the vector components in the format "<x, y, z>".
// Parameters:
//   - out: The output stream.
//   - v: The vector to output.
// Returns:
//   The modified output stream.
//
std::ostream& operator<<(std::ostream& out, const Vector3D& v) {
    out << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return out;
}

//
// Operator: ==
// Compares two vectors for equality, within a small epsilon threshold.
// Parameters:
//   - v: The vector to compare with.
// Returns:
//   true if the vectors are equal, false otherwise.
//
bool Vector3D::operator==(const Vector3D& v) const {
    const double EPSILON = 1e-8;
    return (std::fabs(x - v.x) < EPSILON) &&
           (std::fabs(y - v.y) < EPSILON) &&
           (std::fabs(z - v.z) < EPSILON);
}

//
// Operator: !=
// Compares two vectors for inequality.
// Parameters:
//   - v: The vector to compare with.
// Returns:
//   true if the vectors are not equal, false otherwise.
//
bool Vector3D::operator!=(const Vector3D& v) const {
    return !(*this == v);
}

//
// Method: randomHemisphere
// Generates a random direction within a hemisphere oriented around this vector.
// Uses cosine-weighted sampling for realistic diffuse scattering.
// Returns:
//   A new Vector3D representing the random direction.
//
Vector3D Vector3D::randomHemisphere() const {
    double u1 = randDouble();
    double u2 = randDouble();

    double r = std::sqrt(u1);
    double theta = 2.0 * M_PI * u2;

    double x_ = r * std::cos(theta);
    double y_ = r * std::sin(theta);
    double z_ = std::sqrt(1.0 - u1);

    Vector3D N = this->normalize();

    Vector3D helper = (std::fabs(N.x) > 0.1) ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
    Vector3D T = helper.cross(N).normalize();
    Vector3D B = N.cross(T);

    return T * x_ + B * y_ + N * z_;
}