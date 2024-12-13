#include "Sphere.h"
#include <cmath>

//
// Constructor: Sphere
// Initializes a sphere with the specified parameters.
// Parameters:
//   - center: The center of the sphere.
//   - radius: The radius of the sphere.
//   - color: The color of the sphere.
//   - specular: The specular reflection coefficient.
//   - reflective: The reflectivity of the sphere.
//   - subsurfaceRadius: The radius for subsurface scattering effects.
//   - scatteringCoefficient: The scattering coefficient for subsurface scattering.
//
Sphere::Sphere(const Vector3D& center, double radius, const Color& color,
               double specular, double reflective,
               double subsurfaceRadius, double scatteringCoefficient)
    : center(center), 
      radius(radius), 
      color(color), 
      specular(specular), 
      reflective(reflective), 
      subsurfaceRadius(subsurfaceRadius), 
      scatteringCoefficient(scatteringCoefficient) {}

//
// Default Constructor: Sphere
// Initializes a default sphere at the origin with a radius of 1, black color, and no reflectivity or scattering.
//
Sphere::Sphere()
    : center(Vector3D()), 
      radius(1.0), 
      color(Color()), 
      specular(0.0), 
      reflective(0.0), 
      subsurfaceRadius(0.0), 
      scatteringCoefficient(0.0) {}

//
// Destructor: ~Sphere
// Default destructor for the Sphere class.
//
Sphere::~Sphere() {}

//
// Method: intersect
// Determines if a ray intersects with the sphere.
// Parameters:
//   - ray: The ray to test for intersection.
//   - t: The distance from the ray's origin to the intersection point (output).
// Returns:
//   - true if the ray intersects the sphere, false otherwise.
//
bool Sphere::intersect(const Ray& ray, double& t) const {
    Vector3D oc = ray.origin - center;                 // Vector from ray origin to sphere center
    double k1 = ray.direction.dot(ray.direction);      // Quadratic term coefficient
    double k2 = 2 * oc.dot(ray.direction);            // Linear term coefficient
    double k3 = oc.dot(oc) - radius * radius;         // Constant term
    double discriminant = k2 * k2 - 4 * k1 * k3;      // Discriminant of the quadratic equation

    if (discriminant < 0) {
        return false;                                 // No intersection if discriminant is negative
    }

    double sqrtDiscriminant = std::sqrt(discriminant); // Square root of the discriminant
    double t1 = (-k2 + sqrtDiscriminant) / (2 * k1);   // First root
    double t2 = (-k2 - sqrtDiscriminant) / (2 * k1);   // Second root

    if (t1 >= 0 && t2 >= 0) {
        t = std::min(t1, t2);                         // Choose the closest positive root
    } else if (t1 >= 0) {
        t = t1;                                       // Only t1 is valid
    } else if (t2 >= 0) {
        t = t2;                                       // Only t2 is valid
    } else {
        return false;                                 // No valid intersection
    }

    return true;
}

//
// Method: getNormal
// Computes the normal vector at a given point on the sphere's surface.
// Parameters:
//   - point: The point on the sphere's surface.
// Returns:
//   - The normalized normal vector at the given point.
//
Vector3D Sphere::getNormal(const Vector3D& point) const {
    return (point - center).normalize();              // Normal vector is the direction from the center to the point
}