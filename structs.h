#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef _sphere_h
#define _sphere_h
struct sphere
{
    glm::vec3 center;
    float radius;
    
    glm::mat4 tmat;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    glm::vec3 emission;
    
    glm::vec3 scale;
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
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    glm::vec3 emission;
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
    int rec;
};
#endif

#ifndef _Hit_h
#define _Hit_h
struct Hit
{
    bool hit;
    int prim;
    int shape;
    glm::vec3 isect;
    ray r;
    float depthHit;
};
#endif

#ifndef _ShapeW_h
#define _ShapeW_h
struct ShapeW
{
    bool flag;
    sphere s;
    tri t;
};
#endif

#ifndef _hitShape_h
#define _hitShape_h
struct hitShape
{
    bool hit;
    float depth;
    int index;
    glm::vec3 isect;
    float depthHit;

};
#endif

#ifndef _dLight_h
#define _dLight_h
struct dLight
{
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec3 atten;
};
#endif

#ifndef _pLight_h
#define _pLight_h
struct pLight
{
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec3 atten;
};
#endif

#ifndef _Color_h
#define _Color_h
struct Color
{
    float red;
    float green;
    float blue;
};
#endif



