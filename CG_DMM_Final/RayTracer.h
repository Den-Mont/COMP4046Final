#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include <random>
#include "Vector3D.h"
#include "Color.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Light.h"

//
// Inline random number generation for project-wide use
// Provides random doubles in the range [0.0, 1.0].
//
inline static std::mt19937 rng(std::random_device{}());                 // Random number generator
inline static std::uniform_real_distribution<double> dist(0.0, 1.0);   // Uniform distribution

//
// Function: randDouble
// Generates a random double in the range [0.0, 1.0].
// Returns: A random double.
//
inline double randDouble() {
    return dist(rng);
}

// Global scene data
extern std::vector<Sphere> spheres;       // List of spheres in the scene
extern std::vector<Triangle> triangles;   // List of triangles in the scene
extern std::vector<Light> lights;         // List of lights in the scene
extern Color backgroundColor;             // Background color for the scene

//
// Function: setupScene
// Configures the scene by adding objects and lights.
//
void setupScene();

//
// Function: computeLighting
// Calculates the lighting at a specific point in the scene.
// Parameters:
//   - point: The 3D point being shaded.
//   - normal: The normal vector at the point.
//   - view: The view direction vector.
//   - specular: The specular reflection coefficient.
// Returns: The calculated lighting color at the point.
//
Color computeLighting(const Vector3D& point, const Vector3D& normal, const Vector3D& view, double specular);

//
// Function: TraceRay
// Traces a ray through the scene to determine its color based on intersections and lighting.
// Parameters:
//   - ray: The ray being traced.
//   - t_min: Minimum intersection distance.
//   - t_max: Maximum intersection distance.
//   - depth: Current recursion depth for reflections.
// Returns: The color of the traced ray.
//
Color TraceRay(const Ray& ray, double t_min, double t_max, int depth);

#endif // RAYTRACER_H