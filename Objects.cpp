#include "Objects.h"
#include "variables.h"

ray Objects::makeRay(glm::vec3 ori, glm::vec3 dir) {
    ray r;
    
    r.ori = ori;
    r.dir = dir;
}

glm::vec3 Objects::makeVertex(float * values) {
    glm::vec3 v;
    
    v.x = values[0];
    v.y = values[1];
    v.z = values[2];
    
    return v;
}
 
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

sphere Objects::makeSphere(float * values) {
    sphere s;
    glm::vec3 center;
    
    center.x = values[0];
    center.y = values[1];
    center.z = values[2];

    s.radius = values[3];
    s.center = center;
    
    s.ambient = ambient;
    s.diffuse = diffuse;
    s.specular = specular;
    s.shininess = shininess;
    s.emission = emission;
    
    s.tmat = trstack.top();
    
    s.scale = scaleV;
    
    return s;
}

tri Objects::makeTriangle(float * values) {
    tri t;
    
    glm::mat4 tmat = trstack.top();
    
    glm::mat4 m = tmat;
    
    glm::vec4 tv1 = glm::vec4(vertices[values[0]], 1);
    glm::vec4 tv2 = glm::vec4(vertices[values[1]], 1);
    glm::vec4 tv3 = glm::vec4(vertices[values[2]], 1);
    
    t.v1 = glm::vec3(tv1*tmat);
    t.v2 = glm::vec3(tv2*tmat);
    t.v3 = glm::vec3(tv3*tmat);
    
    t.normal = glm::normalize(glm::cross(t.v2-t.v1, t.v3-t.v1));
    
    t.ambient = ambient;
    t.diffuse = diffuse;
    t.specular = specular;
    t.shininess = shininess;
    t.emission = emission;
    
    return t;
}

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

dLight Objects::makeDLight(float * values) {
    dLight d;
    glm::vec3 pos;
    glm::vec3 col;
    
    pos.x = values[0];
    pos.y = values[1];
    pos.z = values[2];
    
    col.x = values[3];
    col.y = values[4];
    col.z = values[5];
    
    d.pos = pos;
    d.col = col;
    d.atten = glm::vec3(0,0,1);
    return d;
}

pLight Objects::makePLight(float * values) {
    pLight p;
    glm::vec3 pos;
    glm::vec3 col;
    
    pos.x = values[0];
    pos.y = values[1];
    pos.z = values[2];
    
    col.x = values[3];
    col.y = values[4];
    col.z = values[5];
    
    p.pos = pos;
    p.col = col;
    p.atten = attenuation;
    return p;
}

ShapeW Objects::makeWrapper(Hit h) {
    ShapeW w;
    if (h.prim == 0) {
        w.flag = false;
        sphere sp = spheres[h.shape];
        w.s = sp;
    } else if (h.prim == 1) {
        w.flag = true;
        tri tr = triangles[h.shape];
        w.t = tr;
    } else {
        cout << "Error in making shape wrapper";
        exit(1);
    }
    
    return w;
}

glm::vec3 Objects::scale(glm::vec3 v, float s) {
    v.x = v.x*s;
    v.y = v.y*s;
    v.z = v.z*s;
    return v;
}

