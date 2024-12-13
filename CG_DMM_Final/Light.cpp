#include "Light.h"

//
// Constructor: Light
// Creates an ambient light with a specified intensity.
// Parameters:
//   - intensity: The intensity of the light.
//
Light::Light(double intensity)
    : type(LightType::AMBIENT),          // Set the light type to AMBIENT.
      intensity(intensity),             // Set the light's intensity.
      position(Vector3D()),             // Ambient light has no position.
      direction(Vector3D()),            // Ambient light has no direction.
      radius(0.0) {}                    // Radius is not applicable for ambient light.

//
// Constructor: Light
// Creates a point light with a specified intensity, position, and radius.
// Parameters:
//   - intensity: The intensity of the light.
//   - position: The position of the point light in 3D space.
//   - radius: The radius of the light's influence.
//
Light::Light(double intensity, const Vector3D& position, double radius)
    : type(LightType::POINT),           // Set the light type to POINT.
      intensity(intensity),             // Set the light's intensity.
      position(position),               // Set the light's position.
      direction(Vector3D()),            // Point light has no direction.
      radius(radius) {}                 // Set the light's radius.

//
// Constructor: Light
// Creates a directional light with a specified direction and intensity.
// Parameters:
//   - direction: The direction of the light (normalized automatically).
//   - intensity: The intensity of the light.
//
Light::Light(const Vector3D& direction, double intensity)
    : type(LightType::DIRECTIONAL),     // Set the light type to DIRECTIONAL.
      intensity(intensity),             // Set the light's intensity.
      position(Vector3D()),             // Directional light has no position.
      direction(direction.normalize()), // Normalize and set the light's direction.
      radius(0.0) {}                    // Radius is not applicable for directional light.

//
// Destructor: ~Light
// Default destructor for the Light class.
//
Light::~Light() {}