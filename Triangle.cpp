#include "Triangle.h"

//NOTE: NEED TO FIGURE OUT HOW TO SOLVE BARYMETRIC EQUATION

// Return true if ray intersects triangle, else return false
bool Triangle::intersect(tri t, ray r) {
    
    glm::vec3 normal = t.normal;
    float plane = glm::dot(r.dir, normal);
    
    if (plane == 0) {
        return false;
    }
    
    float param = (glm::dot(t.v1,normal) - glm::dot(r.ori,normal)) / glm::dot(r.dir,normal);
    
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
        return true;
    }
    
    return false;
    /*
    bool hitTriangle;
    glm::vec3 normal = t.normal;
    
    if (glm::dot(r.dir,normal) == 0) {
        return false;
    }
    
    
    float intersect;
    intersect = (float) (glm::dot(t.v2-t.v1, normal) - glm::dot(r.ori, normal)) / (glm::dot(r.dir,normal));
    
    // solve barymetric coordinates
    glm::vec3 point = r.ori + (r.dir)*intersect;
    
    glm::vec3 _prime = point-t.v1;
    glm::vec3 _BA = t.v2 - t.v1;
    glm::vec3 _CA = t.v3 - t.v1;
    
    glm::vec2 prime;
    prime.x = _prime.x;
    prime.y = _prime.y;
    
    glm::vec2 BA;
    BA.x = _BA.x;
    BA.y = _BA.y;
    
    glm::vec2 CA;
    CA.x = _CA.x;
    CA.y = _CA.y;
    
    glm::mat2 m (BA.x, BA.y, CA.x, CA.y);
    m = glm::inverse(m);
    glm::vec2 result = m*prime;
    
    float beta = result.x;
    float gamma = result.y;
    
    if (0 <= beta && 0 <= gamma) {
        if (beta <= 1 && gamma <= 1) {
            if ((beta+gamma) <= 1) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
    */
    

}