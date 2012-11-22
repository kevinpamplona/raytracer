
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
    
    glm::mat4 transmat = s.tmat;
    glm::mat4 invtransmat = glm::inverse(s.tmat);
    
    glm::vec4 rori = glm::vec4(r.ori, 1);
    glm::vec4 rdir = glm::vec4(ray_direction, 0);
    
    rori = rori*invtransmat;
    rdir = rdir*invtransmat;
    
    ray_origin = glm::vec3(rori);
    ray_direction = glm::vec3(rdir);
    
    
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
        hitS.isect = ray_origin + (ray_direction * hitS.depth);
        return hitS;
        
    }

    if (((first_root>0) && (second_root<0)) || ((first_root<0) && (second_root>0))) {
        // max(first_root, second_root)
        hitS.depth = max(first_root, second_root);
        hitS.hit = true;
        hitS.isect = ray_origin + (ray_direction * hitS.depth);
        return hitS;
    } else {
        hitS.hit = false;
        return hitS;
    }
}  

glm::vec3 Sphere::getNormal (sphere s, glm::vec3 isect) {
    glm::vec3 n;
    glm::vec3 final;
    glm::vec3 c = s.center;
    float r = s.radius;
    
    n.x = (isect.x-c.x)/r;
    n.y = (isect.y-c.y)/r;
    n.z = (isect.z-c.z)/r;
    
    n = glm::normalize(n);
    
    /*
    glm::vec4 _n = glm::vec4(n, 0);
    
    glm::mat4 invtransmat = glm::inverse(s.tmat);

    
    glm::mat3 temp = glm::mat3( m4[0][0], m4[0][1], m4[0][2],
                                m4[1][0], m4[1][1], m4[1][2],
                                m4[2][0], m4[2][1], m4[2][2]);
    
    glm::mat3 temp2 = glm::inverse(temp);
    glm::mat3 intr = glm::transpose(temp2);        
    final = final * intr;
    
    return glm::normalize(final);
    //return n;
    */
    
    glm::mat4 m4 = s.tmat;
    glm::mat3 temp = glm::mat3( m4[0][0], m4[0][1], m4[0][2],
                                m4[1][0], m4[1][1], m4[1][2],
                                m4[2][0], m4[2][1], m4[2][2]);
    glm::mat3 temp2 = glm::inverse(temp);
    glm::mat3 intr = glm::transpose(temp2);
    
    return glm::normalize(n*intr);
    
}







