#include "vertexnormal.h"
#include "sphere.h"
#include "tri.h"
#include "trinormal.h"
#include "vec.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 makeVertex(float * values);
vertexNormal makeVertNormal(float * values);
sphere makeSphere(float * values);
tri makeTriangle(float * values);
triNormal makeTriNormal(float * values);
