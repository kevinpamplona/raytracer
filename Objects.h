#include "structs.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Objects
{
public:
    Objects();
    virtual ~Objects();
    static ray makeRay(glm::vec3 ori, glm::vec3 dir);
    static glm::vec3 makeVertex(float * values);
    static vertexNormal makeVertNormal(float * values);
    static sphere makeSphere(float * values);
    static tri makeTriangle(float * values);
    static triNormal makeTriNormal(float * values);
    static pLight makePLight(float * values);
    static dLight makeDLight(float * values);
    static ShapeW makeWrapper(Hit h);
    static glm::vec3 scale(glm::vec3 v, float s);
};