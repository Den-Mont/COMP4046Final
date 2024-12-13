#include "Ray.h"

//
// Constructor: Ray
// Initializes a ray with a given origin and direction.
// The direction vector is automatically normalized.
// Parameters:
//   - origin: The starting point of the ray.
//   - direction: The direction in which the ray points.
//
Ray::Ray(const Vector3D& origin, const Vector3D& direction)
    : origin(origin),                     // Set the ray's origin.
      direction(direction.normalize()) {} // Normalize and set the ray's direction.

//
// Default Constructor: Ray
// Initializes a ray with the origin at (0, 0, 0) and the direction pointing along the positive Z-axis.
//
Ray::Ray() 
    : origin(Vector3D()),                 // Set the origin to (0, 0, 0).
      direction(Vector3D(0, 0, 1)) {}     // Set the direction to (0, 0, 1).

//
// Destructor: ~Ray
// Default destructor for the Ray class.
//
Ray::~Ray() {}