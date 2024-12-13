#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3D.h"
#include "Color.h"
#include "Ray.h"

//
// Class: Sphere
// Represents a 3D sphere in the scene with properties for shading, reflection, and subsurface scattering.
//
class Sphere {
public:
    Vector3D center;               // The center of the sphere in 3D space.
    double radius;                 // The radius of the sphere.
    Color color;                   // The color of the sphere.
    double specular;               // The specular reflection coefficient.
    double reflective;             // The reflectivity of the sphere.
    double subsurfaceRadius;       // The radius for subsurface scattering (SSS) effects.
    double scatteringCoefficient;  // The scattering coefficient for subsurface scattering.

    //
    // Constructor: Sphere
    // Initializes a sphere with specified position, size, color, and material properties.
    // Parameters:
    //   - center: The center of the sphere.
    //   - radius: The radius of the sphere.
    //   - color: The color of the sphere.
    //   - specular: The specular reflection coefficient.
    //   - reflective: The reflectivity of the sphere.
    //   - subsurfaceRadius: (Optional) Radius for SSS effects. Default is 0.0.
    //   - scatteringCoefficient: (Optional) Scattering coefficient for SSS. Default is 0.0.
    //
    Sphere(const Vector3D& center, double radius, const Color& color,
           double specular, double reflective,
           double subsurfaceRadius = 0.0, double scatteringCoefficient = 0.0);

    //
    // Default Constructor: Sphere
    // Initializes a default sphere at the origin with a radius of 1, black color,
    // no reflectivity, and no subsurface scattering.
    //
    Sphere();

    //
    // Destructor: ~Sphere
    // Default destructor for the Sphere class.
    //
    ~Sphere();

    //
    // Method: intersect
    // Determines if a ray intersects with the sphere.
    // Parameters:
    //   - ray: The ray to test for intersection.
    //   - t: The distance from the ray's origin to the intersection point (output).
    // Returns:
    //   - true if the ray intersects the sphere, false otherwise.
    //
    bool intersect(const Ray& ray, double& t) const;

    //
    // Method: getNormal
    // Computes the normal vector at a given point on the sphere's surface.
    // Parameters:
    //   - point: The point on the sphere's surface.
    // Returns:
    //   - The normalized normal vector at the given point.
    //
    Vector3D getNormal(const Vector3D& point) const;
};

#endif // SPHERE_H