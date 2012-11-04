#include "Objects.h"


// helper function to create a vertex
glm::vec3 makeVertex(float * values) {
    glm::vec3 v;
    
    v.x = values[0];
    v.y = values[1];
    v.z = values[2];
    
    return v;
}
 

// helper function to create a vertex with specified normals
vertexNormal makeVertNormal(float * values) {
    vertexNormal vn;
    
    vn.x = values[0];
    vn.y = values[1];
    vn.z = values[2];
    
    vn.nx = values[3];
    vn.ny = values[4];
    vn.nz = values[5];
    
    return vn;
}

// helper function to create a sphere
sphere makeSphere(float * values) {
    sphere s;
    
    s.x = values[0];
    s.y = values[1];
    s.z = values[2];
    
    s.radius = values[3];
    
    return s;
}

// helper function to create a triangle
tri makeTriangle(float * values) {
    tri t;
    
    t.v1 = values[0];
    t.v2 = values[1];
    t.v3 = values[2];
    
    return t;
}

// helper function to create triangle with vertices that have specified normals
triNormal makeTriNormal(float * values) {
    triNormal tn;
    
    tn.v1 = values[0];
    tn.v2 = values[1];
    tn.v3 = values[2];
    
    return tn;
}
