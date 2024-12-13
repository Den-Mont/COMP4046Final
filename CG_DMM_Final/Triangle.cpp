#include "Triangle.h"
#include <cmath>

//
// Constructor: Triangle
// Initializes a triangle with specified vertices and material properties.
// Parameters:
//   - A, B, C: The vertices of the triangle in 3D space.
//   - color: The color of the triangle.
//   - specular: The specular reflection coefficient.
//   - reflective: The reflectivity of the triangle.
//   - subsurfaceRadius: The radius for subsurface scattering effects.
//   - scatteringCoefficient: The scattering coefficient for subsurface scattering.
//
Triangle::Triangle(const Vector3D& A, const Vector3D& B, const Vector3D& C,
                   const Color& color, double specular, double reflective,
                   double subsurfaceRadius, double scatteringCoefficient)
    : A(A), 
      B(B), 
      C(C), 
      color(color), 
      specular(specular), 
      reflective(reflective), 
      subsurfaceRadius(subsurfaceRadius), 
      scatteringCoefficient(scatteringCoefficient) {}

//
// Destructor: ~Triangle
// Default destructor for the Triangle class.
//
Triangle::~Triangle() {}

//
// Method: intersect
// Determines if a ray intersects with the triangle using the Möller-Trumbore algorithm.
// Parameters:
//   - ray: The ray to test for intersection.
//   - t: The distance from the ray's origin to the intersection point (output).
// Returns:
//   - true if the ray intersects the triangle, false otherwise.
//
bool Triangle::intersect(const Ray& ray, double& t) const {
    const double EPSILON = 1e-8;             // Small threshold to avoid floating-point errors
    Vector3D edge1 = B - A;                 // Edge vector 1
    Vector3D edge2 = C - A;                 // Edge vector 2
    Vector3D h = ray.direction.cross(edge2);
    double a = edge1.dot(h);

    if (fabs(a) < EPSILON)                  // Check if the ray is parallel to the triangle
        return false;

    double f = 1.0 / a;
    Vector3D s = ray.origin - A;
    double u = f * s.dot(h);                // Barycentric coordinate u
    if (u < 0.0 || u > 1.0)                 // Check if the intersection is outside the triangle
        return false;

    Vector3D q = s.cross(edge1);
    double v = f * ray.direction.dot(q);    // Barycentric coordinate v
    if (v < 0.0 || u + v > 1.0)             // Check if the intersection is outside the triangle
        return false;

    double tempT = f * edge2.dot(q);        // Calculate the distance to the intersection point
    if (tempT > EPSILON) {                  // Valid intersection if t > EPSILON
        t = tempT;
        return true;
    } else {
        return false;                       // Intersection is behind the ray origin
    }
}

//
// Method: getNormal
// Computes the normal vector of the triangle.
// Returns:
//   - The normalized normal vector of the triangle.
// Notes:
//   - Ensures that the normal faces away from the camera (assumes camera is near the origin).
//
Vector3D Triangle::getNormal() const {
    Vector3D normal = (B - A).cross(C - A).normalize(); // Compute the normal using cross product
    if (normal.dot(A) > 0) {                           // Flip the normal if it faces the wrong way
        normal = -normal;
    }
    return normal;
}