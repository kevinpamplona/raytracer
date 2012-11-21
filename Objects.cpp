#include "Objects.h"
#include "variables.h"

// helper function to create a vertex
glm::vec3 Objects::makeVertex(float * values) {
    glm::vec3 v;
    
    v.x = values[0];
    v.y = values[1];
    v.z = values[2];
    
    return v;
}
 

// helper function to create a vertex with specified normals
vertexNormal Objects::makeVertNormal(float * values) {
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
sphere Objects::makeSphere(float * values) {
    sphere s;
    glm::vec3 center;
    
    center.x = values[0];
    center.y = values[1];
    center.z = values[2];

    s.radius = values[3];
    s.center = center;
    
    return s;
}

// helper function to create a triangle
tri Objects::makeTriangle(float * values) {
    tri t;
    
    int v1 = values[0];
    int v2 = values[1];
    int v3 = values[2];
    
    t.v1 = vertices[v1];
    t.v2 = vertices[v2];
    t.v3 = vertices[v3];
    
    t.normal = glm::normalize(glm::cross(t.v2-t.v1, t.v3-t.v1));
    
    return t;
}

// helper function to create triangle with vertices that have specified normals
triNormal Objects::makeTriNormal(float * values) {
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

glm::vec3 Objects::scale(glm::vec3 v, float s) {
    v.x = v.x*s;
    v.y = v.y*s;
    v.z = v.z*s;
    return v;
}

