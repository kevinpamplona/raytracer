#include "Objects.h"
#include "variables.h"

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
    
    glm::vec3 temp_vec;
    glm::vec3 temp_n;
    
    temp_vec.x = values[0];
    temp_vec.y = values[1];
    temp_vec.z = values[2];
    
    temp_n.x = values[3];
    temp_n.x = values[4];
    temp_n.x = values[5];
    
    vn.v = temp_vec;
    vn.n = temp_n;
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
    
    int v1 = values[0];
    int v2 = values[1];
    int v3 = values[2];
    
    t.v1 = vertices[v1];
    t.v2 = vertices[v2];
    t.v3 = vertices[v3];
    return t;
}

// helper function to create triangle with vertices that have specified normals
triNormal makeTriNormal(float * values) {
    triNormal tn;
    
    int v1 = values[0];
    int v2 = values[1];
    int v3 = values[2];
    
    vertexNormal a;
    vertexNormal b;
    vertexNormal c;
    
    a = vertnormals[v1];
    b = vertnormals[v2];
    c = vertnormals[v3];
    
    tn.v1 = a.v;
    tn.v2 = b.v;
    tn.v3 = c.v;
    
    tn.vn1 = a.n;
    tn.vn2 = b.n;
    tn.vn3 = c.n;
    
    return tn;
}
