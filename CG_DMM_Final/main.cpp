#include <iostream>
#include <fstream>
#include <limits>
#include "RayTracer.h"

//
// Main function
// Sets up the scene, performs ray tracing, and outputs the rendered image as a PPM file.
//
int main() {
    // Set up the scene
    setupScene();

    const int width = 1280;        // Image width in pixels
    const int height = 720;        // Image height in pixels
    const int maxDepth = 2;        // Maximum recursion depth for ray tracing

    // Samples per pixel (spp) for anti-aliasing
    const int spp = 4;

    // Open the output file for the rendered image
    std::ofstream outFile("output.ppm");
    if (!outFile) {
        std::cerr << "Error: Could not open output.ppm for writing.\n";
        return 1;
    }

    // Write the PPM file header
    outFile << "P3\n" << width << " " << height << "\n255\n";

    double aspectRatio = static_cast<double>(width) / height;  // Aspect ratio of the image
    double viewportHeight = 2.0;                              // Viewport height
    double viewportWidth = viewportHeight * aspectRatio;      // Viewport width

    // Camera setup
    Vector3D origin(0, 1, -3);            // Camera position
    Vector3D lookAt(0, 1, 2);             // Point the camera is looking at
    Vector3D cameraDirection = (lookAt - origin).normalize(); // Camera direction (normalized)

    Vector3D up(0, 1, 0);                         // Up direction vector
    Vector3D right = cameraDirection.cross(up).normalize(); // Right direction vector
    Vector3D cameraUp = right.cross(cameraDirection).normalize(); // Adjusted up vector

    // Render each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color pixelColor(0, 0, 0); // Initialize pixel color to black

            // Perform anti-aliasing by averaging multiple samples per pixel
            for (int s = 0; s < spp; s++) {
                double u = ((x + randDouble()) / width) - 0.5;  // Randomized horizontal offset
                double v = ((y + randDouble()) / height) - 0.5; // Randomized vertical offset

                // Compute the direction of the ray for this sample
                Vector3D direction = (cameraDirection +
                                      right * (u * viewportWidth) +
                                      cameraUp * (v * viewportHeight)).normalize();
                Ray ray(origin, direction);

                // Trace the ray and accumulate the resulting color
                Color sampleColor = TraceRay(ray, 1.0, std::numeric_limits<double>::infinity(), maxDepth);
                pixelColor = pixelColor + sampleColor;
            }

            // Average the samples to compute the final pixel color
            pixelColor = pixelColor * (1.0 / spp);
            pixelColor.clamp(); // Ensure the color values are in range [0.0, 1.0]

            // Convert color values to integers in range [0, 255]
            int r = static_cast<int>(pixelColor.r * 255);
            int g = static_cast<int>(pixelColor.g * 255);
            int b = static_cast<int>(pixelColor.b * 255);

            // Clamp the integer values to ensure they are within the valid range
            r = std::min(255, std::max(0, r));
            g = std::min(255, std::max(0, g));
            b = std::min(255, std::max(0, b));

            // Write the pixel color to the output file
            outFile << r << " " << g << " " << b << "\n";
        }
    }

    outFile.close(); // Close the output file
    std::cout << "Rendering completed. Image saved as output.ppm\n";

    return 0;
}