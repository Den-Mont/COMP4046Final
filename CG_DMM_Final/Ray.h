#ifndef RAY_H
#define RAY_H

#include "Vector3D.h"

//
// Class: Ray
// Represents a ray in 3D space, defined by an origin point and a direction vector.
//
class Ray {
public:
    Vector3D origin;     // The starting point of the ray.
    Vector3D direction;  // The direction of the ray (normalized).

    //
    // Constructor: Ray
    // Initializes a ray with a specified origin and direction.
    // The direction vector is normalized automatically.
    // Parameters:
    //   - origin: The starting point of the ray.
    //   - direction: The direction of the ray.
    //
    Ray(const Vector3D& origin, const Vector3D& direction);

    //
    // Default Constructor: Ray
    // Initializes a ray with the origin at (0, 0, 0) and the direction pointing along the positive Z-axis.
    //
    Ray();

    //
    // Destructor: ~Ray
    // Default destructor for the Ray class.
    //
    ~Ray();
};

#endif // RAY_H