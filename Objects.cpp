#include "Objects.h"

// helper function to create a vertex
vec3 Objects::makeVertex(float * values) {
    return vec3(values[0], values[1], values[2]);
}

// helper function to create a vertex with specified normals
struct vertexNormal Objects::makeVertNormal(float * values) {
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
struct sphere Objects::makeSphere(float * values) {
    sphere s;
    
    s.x = values[0];
    s.y = values[1];
    s.z = values[2];
    
    s.radius = values[3];
    
    return s;
}

// helper function to create a triangle
struct tri Objects::makeTriangle(float * values) {
    tri t;
    
    t.x = values[0];
    t.y = values[1];
    t.z = values[2]
    // face normal calculated later
    
    return t;
}

// helper function to create triangle with vertices that have specified normals
struct triNormal Objects::makeTriNormal(float * values) {
    trinormal tn;
    
    tn.x = values[0];
    tn.y = values[1];
    tn.z = values[2];
    
    return tn;
}

Objects::Objects()
{
    
}

Objects::~Objects()
{
    
}