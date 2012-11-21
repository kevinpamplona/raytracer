
#include "Sphere.h"
#include "Objects.h"
#include "Intersect.h"


hitShape Sphere::intersect (sphere s, ray r) {
    
    hitShape hitS;
    
    glm::vec3 sphere_center = s.center;
    glm::vec3 ray_origin = r.ori;
    glm::vec3 ray_direction = glm::normalize(r.dir);
    //glm::vec3 ray_direction = r.dir;
    float radius = s.radius;
    
    float a = glm::dot(ray_direction, ray_direction);
    float b = 2*glm::dot(ray_direction,ray_origin-sphere_center); // not sure about this
    float c = glm::dot(ray_origin-sphere_center, ray_origin-sphere_center) - pow(radius,2);
    
    // Discriminant 
    float disc = (b*b) - (4*a*c);
    
    if (disc < 0) {
        hitS.hit = false;
        return hitS;
    }
    
    float first_root = (-b + sqrt(disc))/(2*a);
    float second_root = (-b - sqrt(disc))/(2*a);
    
    //curve tangent to circle
    if (first_root == second_root) {
        hitS.hit = false;
        return hitS;
    }
    
    if ((first_root > 0) && (second_root > 0)) {
        // min (first_root, second_root)
        hitS.depth = min(first_root, second_root);
        hitS.hit = true;
        return hitS;
        
    }

    if (((first_root>0) && (second_root<0)) || ((first_root<0) && (second_root>0))) {
        // max(first_root, second_root)
        hitS.depth = max(first_root, second_root);
        hitS.hit = true;
        return hitS;
    } else {
        hitS.hit = false;
        return hitS;
    }
}