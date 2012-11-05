#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef _tri_h
#define _tri_h

struct tri
{
    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 v3;
    
    glm::vec3 normal;
};


#endif
