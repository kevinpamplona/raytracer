#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef _triNormal_h
#define _triNormal_h

struct triNormal
{
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    
    glm::vec3 vn1;
    glm::vec3 vn2;
    glm::vec3 vn3;
};

#endif
