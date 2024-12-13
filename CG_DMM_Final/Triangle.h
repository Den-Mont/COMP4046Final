#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector3D.h"
#include "Color.h"
#include "Ray.h"

//
// Class: Triangle
// Represents a 3D triangle in the scene with properties for shading, reflection, and subsurface scattering.
//
class Triangle {
public:
    Vector3D A, B, C;              // The vertices of the triangle.
    Color color;                   // The color of the triangle.
    double specular;               // The specular reflection coefficient.
    double reflective;             // The reflectivity of the triangle.
    double subsurfaceRadius;       // The radius for subsurface scattering (SSS) effects.
    double scatteringCoefficient;  // The scattering coefficient for subsurface scattering.

    //
    // Constructor: Triangle
    // Initializes a triangle with specified vertices, color, and material properties.
    // Parameters:
    //   - A, B, C: The vertices of the triangle.
    //   - color: The color of the triangle.
    //   - specular: The specular reflection coefficient.
    //   - reflective: The reflectivity of the triangle.
    //   - subsurfaceRadius: (Optional) Radius for SSS effects. Default is 0.0.
    //   - scatteringCoefficient: (Optional) Scattering coefficient for SSS. Default is 0.0.
    //
    Triangle(const Vector3D& A, const Vector3D& B, const Vector3D& C,
             const Color& color, double specular, double reflective,
             double subsurfaceRadius = 0.0, double scatteringCoefficient = 0.0);

    //
    // Destructor: ~Triangle
    // Default destructor for the Triangle class.
    //
    ~Triangle();

    //
    // Method: intersect
    // Determines if a ray intersects with the triangle using the Möller-Trumbore algorithm.
    // Parameters:
    //   - ray: The ray to test for intersection.
    //   - t: The distance from the ray's origin to the intersection point (output).
    // Returns:
    //   - true if the ray intersects the triangle, false otherwise.
    //
    bool intersect(const Ray& ray, double& t) const;

    //
    // Method: getNormal
    // Computes the normal vector of the triangle.
    // Returns:
    //   - The normalized normal vector of the triangle.
    // Notes:
    //   - Ensures that the normal faces away from the camera (assumes camera is near the origin).
    //
    Vector3D getNormal() const;
};

#endif // TRIANGLE_H