#include "variables.h"

class Film
{
public:
    Film();
    virtual ~Film();
    
    static void write(glm::vec3 color, glm::vec2 position);
    static void output();
};