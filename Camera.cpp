#include <math.h>
#include "variables.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

ray Camera::shootRay(int i, int j) {
    raycount += 1;
    ray r;
    glm::vec3 dir;
    float alpha, beta;
    
    float fovx = width;
    float fovy = fov;
    
    alpha = tan(fovx/2)*((j-(width/2))/(width/2));
    beta = tan(fovy/2)*(((height/2)-i)/(height/2));
    
    dir = glm::normalize(alpha*u+beta*v-w);
    r.dir = dir;
    return r;
}