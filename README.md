# COMP4046Final
Repository for COMP 4046 (Computer Graphics projects) Final Exam.

## Features

- **Basic Objects**: Supports rendering spheres and triangles.
- **Lighting**: Handles ambient, point, and directional lights with soft shadows.
- **Reflections**: Implements recursive ray tracing for reflective surfaces.
- **Subsurface Scattering (SSS)**: Adds realistic light scattering effects for translucent materials.
- **Anti-Aliasing**: Includes multiple samples per pixel for smoother edges.
- **Customizable Scene**: Easily modify objects, materials, lights, and camera settings.

## Getting Started

### Prerequisites

- A C++ compiler with C++11 (or later) support.

### Building the Project

1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd <repository_directory>
   ```

2. Compile the project
   ```bash
     g++ -o raytracer main.cpp Vector3D.cpp Ray.cpp Color.cpp Sphere.cpp   Triangle.cpp Light.cpp RayTracer.cpp -std=c++11
   ```
3. Run the program
   ```bash
   ./

### Output

The program generates an image file named output.ppm in the project directory. You can open it with an image viewer that supports the PPM format or convert it to another format using tools like GIMP or ImageMagick.

### Configurable Settings

You can adjust the following settings directly in the code (typically in main.cpp or RayTracer.h):
	1.	Resolution:
	•	Adjust the width and height variables in main.cpp to set the resolution of the output image.
 ```C++
const int width = 1280;
const int height = 720;
```
  2. Samples Per Pixel (Anti-Aliasing):
Modify the spp variable in main.cpp to control the number of samples per pixel for anti-aliasing. Higher values produce smoother images but increase rendering time.
```C++
const int spp = 4; // Set higher for better quality
```

  3. Maximum Ray Depth:
Change the maxDepth variable in main.cpp to control the maximum recursion depth for reflections.
```C++
const int maxDepth = 2; // Increase for more reflections
```

  4. Background Color:
Update the backgroundColor variable in RayTracer.cpp to set the scene’s background color.
```C++
Color backgroundColor(0.2, 0.3, 0.5); // Soft blue background
```

  5. Scene Objects and Lights:
Edit the setupScene() function in RayTracer.cpp to customize objects, lights, and materials in the scene.
Example of adding a sphere:
```C++
spheres.push_back(Sphere(
    Vector3D(0, -1, 3),  // Center
    1,                   // Radius
    Color(1, 0.5, 0.5),  // Color
    500,                 // Specular coefficient
    0.2,                 // Reflectivity
    2.0,                 // Subsurface radius
    0.5                  // Scattering coefficient
));
```
  6. Camera Settings:
Modify the camera’s origin, lookAt, and other parameters in main.cpp.
```C++
Vector3D origin(0, 1, -3);
Vector3D lookAt(0, 1, 2);
```
### Extending the Project
 
Feel free to extend the engine by:
	•	Adding support for more geometric shapes.
	•	Implementing advanced features like texture mapping or motion blur.
	•	Experimenting with global illumination techniques like path tracing.

### License 
This project is licensed under the MIT License. See the LICENSE file for details.
