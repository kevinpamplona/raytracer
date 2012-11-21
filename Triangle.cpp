#include "Triangle.h"
#include "Intersect.h"
//NOTE: NEED TO FIGURE OUT HOW TO SOLVE BARYMETRIC EQUATION

// Return true if ray intersects triangle, else return false
hitShape Triangle::intersect(tri t, ray r) {
    
    hitShape hitS;
    
    glm::vec3 normal = t.normal;
    float plane = glm::dot(r.dir, normal);
    
    if (plane == 0) {
        hitS.hit = false;
        return hitS;
    }
    
    float param = (glm::dot(t.v1,normal) - glm::dot(r.ori,normal)) / (float)glm::dot(r.dir,normal);
    hitS.depth = param;
    
    glm::vec3 hit = r.ori + r.dir*param;
    glm::vec3 PA = hit - t.v1;
    glm::vec3 PB = hit - t.v2;
    glm::vec3 PC = hit - t.v3;
    glm::vec3 BA = t.v2 - t.v1;
    glm::vec3 CB = t.v3 - t.v2;
    glm::vec3 AC = t.v1 - t.v3;
    
    float check_one = glm::dot(glm::cross(BA,PA),normal);
    float check_two = glm::dot(glm::cross(CB,PB), normal);
    float check_three = glm::dot(glm::cross(AC,PC), normal);
    
    if (check_one >= 0 && check_two >= 0 && check_three >= 0) {
        hitS.hit = true;
        return hitS;
    }
    
    hitS.hit = false;
    return hitS;
}