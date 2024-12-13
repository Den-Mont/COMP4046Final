#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"

//
// Enum: LightType
// Represents the type of the light source.
//
enum class LightType {
    AMBIENT,     // Ambient light, uniform intensity with no direction or position.
    POINT,       // Point light, emanates from a specific position in all directions.
    DIRECTIONAL  // Directional light, has a direction but no specific position.
};

//
// Class: Light
// Represents a light source with various types (ambient, point, directional).
//
class Light {
public:
    LightType type;          // The type of the light (AMBIENT, POINT, or DIRECTIONAL).
    double intensity;        // The intensity of the light.
    Vector3D position;       // The position of the light (applicable for POINT lights).
    Vector3D direction;      // The direction of the light (applicable for DIRECTIONAL lights).
    double radius;           // The radius of influence (applicable for POINT lights).

    //
    // Constructor: Light (Ambient)
    // Creates an ambient light with the specified intensity.
    // Parameters:
    //   - intensity: The intensity of the ambient light.
    //
    Light(double intensity);

    //
    // Constructor: Light (Point)
    // Creates a point light with the specified intensity, position, and optional radius.
    // Parameters:
    //   - intensity: The intensity of the point light.
    //   - position: The position of the point light in 3D space.
    //   - radius: (Optional) The radius of influence for the point light. Default is 0.0.
    //
    Light(double intensity, const Vector3D& position, double radius = 0.0);

    //
    // Constructor: Light (Directional)
    // Creates a directional light with the specified direction and intensity.
    // Parameters:
    //   - direction: The direction of the directional light.
    //   - intensity: The intensity of the directional light.
    //
    Light(const Vector3D& direction, double intensity);

    //
    // Destructor: ~Light
    // Default destructor for the Light class.
    //
    ~Light();
};

#endif // LIGHT_H