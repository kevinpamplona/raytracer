#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef _sphere_h
#define _sphere_h
struct sphere
{
    glm::vec3 center;
    
    float radius;
};
#endif

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

#ifndef _vertexNormal_h
#define _vertexNormal_h
struct vertexNormal
{
    glm::vec3 v;
    glm::vec3 n;
};
#endif

#ifndef _ray_h
#define _ray_h
struct ray
{
    glm::vec3 dir;
    glm::vec3 ori;
    float t;
};
#endif

