#include "Intersect.h"
#include "variables.h"
#include "structs.h"
#include "Sphere.h"
#include "Triangle.h"

bool Intersect::hit(ray r) {
    int hitSphere = 0;
    int hitTri = 0;
    int hitTriN = 0;
    
    if (spherecount > 0) {
        for (int i = 0; i < spherecount; i++) {
            bool hit = false;
            sphere s = spheres[i];
            hit = Sphere::intersect(s, r);
            if (hit) {
                hitSphere += 1;
            }
        }
    }
    
    if (tricount > 0) {
        for (int i = 0; i < tricount; i++) {
            bool hit = false;
            tri t = triangles[i];
            hit = Triangle::intersect(t, r);
            if (hit) {
                hitTri += 1;
            }
        }
    }
    
    if (trinormcount > 0) {
        for (int i = 0; i < trinormcount; i++) {
            //triN = trinormals[i];
            // Need to implement TriNormal.cpp
        }
    }
    
    return ( hitSphere > 0 || hitTri > 0 || hitTriN > 0);
}