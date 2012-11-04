#include <glm/glm.hpp>

typedef glm::vec3 vec3;

class Transform
{
public:
    Transform();
    virtual ~Transform();
    
    static vec3 makeVertex(float * values);
    static struct vertexNormal makeVertNormal(float * values);
    static struct sphere makeSphere(float * values);
    static struct tri makeTriangle(float * values);
    static struct triNormal makeTriNormal(float * values);
}