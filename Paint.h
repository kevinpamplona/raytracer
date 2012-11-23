#include "variables.h"

class Paint
{
public:
    Paint();
    virtual ~Paint();
    
    static bool computeShadow(glm::vec3 x, glm::vec3 lp, glm::vec3 lightpos, bool lightflag, int m, int n);
    
    static glm::vec3 computeLight(glm::vec3 direction, glm::vec3 lightcolor, glm::vec3 normal, glm::vec3 halfvec, glm::vec3 diffuse, glm::vec3 specular, float shininess, glm::vec3 attenuation, float r, glm::vec3 isect, bool doShadow, glm::vec3 lightpos, glm::vec3 lightpos, int m, int n);
    
    static Color computeColor(Hit h, int i, int j);
};