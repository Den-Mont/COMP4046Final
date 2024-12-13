#include "RayTracer.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <iostream>

std::vector<Sphere> spheres;
std::vector<Triangle> triangles;
std::vector<Light> lights;
Color backgroundColor(0.2, 0.3, 0.5); // Soft blue background

void setupScene() {
    // Add spheres with enhanced SSS parameters
    spheres.push_back(Sphere(
        Vector3D(0, -1, 3),
        1,
        Color(1, 0.5, 0.5), // Light reddish color
        500,
        0.2,
        2.0, // Larger subsurfaceRadius for more light bleeding
        0.5  // Lower scatteringCoefficient for stronger effect
    ));

    spheres.push_back(Sphere(
        Vector3D(2, 0, 4),
        1,
        Color(0.5, 0.5, 1), // Light bluish color
        500,
        0.3,
        3.0, // Larger subsurfaceRadius to enhance SSS
        0.3  // Reduced scatteringCoefficient
    ));

    spheres.push_back(Sphere(
        Vector3D(-2, 0, 4),
        1,
        Color(0.5, 1, 0.5), // Light greenish color
        10,
        0.4,
        1.5, // Moderate subsurfaceRadius
        0.3  // Reduced scatteringCoefficient for softer effect
    ));

    // Ground plane (large sphere)
    spheres.push_back(Sphere(
        Vector3D(0, -5002, 0), // Lower ground plane for better contrast
        5000,
        Color(1.0, 0.9, 0.6), // Bright yellow base
        1000,
        0.2, // Reflectivity for glossy ground effect
        0.0  // No subsurface scattering
    ));

    // Add triangle with magenta color and reflectivity
    triangles.push_back(Triangle(
        Vector3D(0, 0, 2),
        Vector3D(1, 2, 2),
        Vector3D(-1, 2, 2),
        Color(1, 0, 1), // Magenta color
        1000,
        0.4, // Add reflectivity
        3.0, // Larger subsurfaceRadius
        0.3  // Stronger scattering effect
    ));

    // Lights
    lights.push_back(Light(0.3)); // Ambient light (reduced intensity for subtle effect)
    lights.push_back(Light(0.8, Vector3D(-4, 3, 3), 1.0)); // Stronger point light from the side
    lights.push_back(Light(Vector3D(1, 4, 4), 0.5)); // Directional light
    lights.push_back(Light(1.0, Vector3D(0, 1.5, -2), 0.5)); // Backlight for enhanced translucency
}

Color computeLighting(const Vector3D& point, const Vector3D& normal, const Vector3D& view, double specular) {
    Color result(0, 0, 0);
    const int numSamples = 128; // High for soft shadows

    for (const Light& light : lights) {
        if (light.type == LightType::AMBIENT) {
            result = result + Color(light.intensity, light.intensity, light.intensity);
        } else {
            Color sampleColor(0, 0, 0);

            for (int i = 0; i < numSamples; i++) {
                Vector3D lightSample = light.position;
                if (light.radius > 0) {
                    // Sample area light
                    double r = light.radius * std::sqrt(randDouble());
                    double theta = 2.0 * M_PI * randDouble();
                    double x = r * std::cos(theta);
                    double y = r * std::sin(theta);
                    double z = 0.0;
                    lightSample = light.position + Vector3D(x, y, z);
                }

                Vector3D lightDir = (lightSample - point).normalize();
                double t_max = (light.type == LightType::POINT) ? 1.0 : std::numeric_limits<double>::infinity();

                Vector3D shadowOrig = (lightDir.dot(normal) < 0) ? point - normal * 1e-5 : point + normal * 1e-5;
                Ray shadowRay(shadowOrig, lightDir);

                bool inShadow = false;
                for (const Sphere& sphere : spheres) {
                    double t;
                    if (sphere.intersect(shadowRay, t) && t > 0 && t < t_max) {
                        inShadow = true;
                        break;
                    }
                }

                if (!inShadow) {
                    for (const Triangle& triangle : triangles) {
                        double t;
                        if (triangle.intersect(shadowRay, t) && t > 0 && t < t_max) {
                            inShadow = true;
                            break;
                        }
                    }
                }

                if (inShadow) continue;

                double n_dot_l = normal.dot(lightDir);
                if (n_dot_l > 0) {
                    double diffuseIntensity = light.intensity * n_dot_l;
                    sampleColor = sampleColor + Color(diffuseIntensity, diffuseIntensity, diffuseIntensity) * 0.8;
                }

                if (specular >= 0) {
                    Vector3D reflectDir = 2 * normal * normal.dot(lightDir) - lightDir;
                    double r_dot_v = reflectDir.dot(view);
                    if (r_dot_v > 0) {
                        double specularIntensity = light.intensity * std::pow(r_dot_v, specular);
                        sampleColor = sampleColor + Color(specularIntensity, specularIntensity, specularIntensity) * 0.5;
                    }
                }
            }

            result = result + (sampleColor * (1.0 / numSamples));
        }
    }

    return result;
}

Color TraceRay(const Ray& ray, double t_min, double t_max, int depth) {
    if (depth <= 0) return Color(0, 0, 0);

    double closest_t = std::numeric_limits<double>::infinity();
    const Sphere* closest_sphere = nullptr;
    const Triangle* closest_triangle = nullptr;

    for (const Sphere& sphere : spheres) {
        double t;
        if (sphere.intersect(ray, t) && t > t_min && t < t_max && t < closest_t) {
            closest_t = t;
            closest_sphere = &sphere;
            closest_triangle = nullptr;
        }
    }

    for (const Triangle& triangle : triangles) {
        double t;
        if (triangle.intersect(ray, t) && t > t_min && t < t_max && t < closest_t) {
            closest_t = t;
            closest_triangle = &triangle;
            closest_sphere = nullptr;
        }
    }

    if (!closest_sphere && !closest_triangle) return backgroundColor;

    Vector3D point = ray.origin + ray.direction * closest_t;
    Vector3D normal;
    Color objectColor;
    double specular;
    double reflective;
    double sssRadius;
    double sssScatter;

    if (closest_sphere) {
        normal = closest_sphere->getNormal(point);
        objectColor = closest_sphere->color;
        specular = closest_sphere->specular;
        reflective = closest_sphere->reflective;
        sssRadius = closest_sphere->subsurfaceRadius;
        sssScatter = closest_sphere->scatteringCoefficient;
    } else {
        normal = closest_triangle->getNormal();
        objectColor = closest_triangle->color;
        specular = closest_triangle->specular;
        reflective = closest_triangle->reflective;
        sssRadius = closest_triangle->subsurfaceRadius;
        sssScatter = closest_triangle->scatteringCoefficient;
    }

    Color localLighting = computeLighting(point, normal, -ray.direction, specular);
    Color localColor = objectColor * localLighting;

    // Reflection
    Color reflectionColor(0, 0, 0);
    if (reflective > 0) {
        Vector3D reflectDir = ray.direction - normal * 2 * ray.direction.dot(normal);
        Ray reflectRay(point + normal * 1e-5, reflectDir);
        reflectionColor = TraceRay(reflectRay, 0.001, t_max, depth - 1) * reflective;
    }

    // Indirect lighting (simple diffuse)
    Color indirectColor(0, 0, 0);
    if (depth > 1) {
        double terminationProbability = 0.2; // Russian roulette
        if (randDouble() > terminationProbability) {
            Vector3D randomDir = normal.randomHemisphere();
            Ray indirectRay(point + normal * 1e-5, randomDir);
            indirectColor = TraceRay(indirectRay, 0.001, t_max, depth - 1) * 0.1;
        }
    }

    // Approximate Subsurface Scattering
    if (sssRadius > 0.0 && sssScatter > 0.0) {
        const int sssSamples = 16;
        Color sssAccum(0,0,0);
        double totalWeight = 0.0;

        Vector3D N = normal;
        Vector3D helper = (std::fabs(N.x) > 0.1) ? Vector3D(0,1,0) : Vector3D(1,0,0);
        Vector3D T = helper.cross(N).normalize();
        Vector3D B = N.cross(T);

        for (int i = 0; i < sssSamples; i++) {
            double r = sssRadius * std::sqrt(randDouble());
            double theta = 2.0 * M_PI * randDouble();
            double dx = r * std::cos(theta);
            double dy = r * std::sin(theta);

            Vector3D offsetPoint = point + T * dx + B * dy;
            Ray probeRay(offsetPoint + N*1e-5, N);
            // Compute simple local lighting at offset
            Color probeLight = computeLighting(offsetPoint, N, -probeRay.direction, specular) * objectColor;

            double dist = (offsetPoint - point).length();
            double weight = std::exp(-dist / (sssScatter * sssRadius));
            sssAccum = sssAccum + probeLight * weight;
            totalWeight += weight;
        }

        if (totalWeight > 0.0) {
            Color sssResult = sssAccum * (1.0 / totalWeight);
            double blendFactor = 0.5; // Adjust how much SSS affects the final color
            localColor = localColor * (1.0 - blendFactor) + sssResult * blendFactor;
        }
    }

    Color finalColor = localColor + reflectionColor + indirectColor;
    finalColor.clamp();
    return finalColor;
}