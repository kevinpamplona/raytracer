#include "Intersect.h"
#include "Objects.h"
#include "variables.h"
#include "structs.h"
#include "Sphere.h"
#include "Triangle.h"
/*
Hit Intersect::hit(ray r) {
    
    Hit rayHit;
    
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
    
    //return ( hitSphere > 0 || hitTri > 0 || hitTriN > 0);
    
    return rayHit;
}
*/

Hit Intersect::hit(ray r, bool debug) {
    
    Hit rayHit;
    
    int hitSphere = 0;
    int hitTri = 0;
    int hitTriN = 0;
    
    hitShape nearestSphere;
    nearestSphere.depth = INT_MAX;
    bool sphereFill = false;
    
    
    hitShape nearestTri;
    nearestTri.depth = INT_MAX;
    bool triFill = false;
    
    int primFlag;
    
    if (spherecount > 0) {
        if (debug) {
            cout << "Sphere distances: \n";
        }
        for (int i = 0; i < spherecount; i++) {
            hitShape hs;
            hs.hit = false;
            hs.index = i;
            sphere s = spheres[i];
            hs = Sphere::intersect(s,r);
            if (hs.hit) {
                if (debug) {
                    cout << "\t" << hs.depth << " \n";
                }
                hitSphere++;
                if (sphereFill) {
                    if (hs.depth < nearestSphere.depth) {
                        nearestSphere = hs;
                    }
                }
                else {
                    nearestSphere = hs;
                    sphereFill = true;
                }
            }
        }
    }
    
    if (tricount > 0) {
        for (int i = 0; i < tricount; i++) {
            hitShape hs;
            hs.hit = false;
            hs.index = i;
            tri t = triangles[i];
            hs = Triangle::intersect(t,r);
            if (hs.hit) {
                hitTri++;
                if (triFill) {
                    if (hs.depth < nearestTri.depth) {
                        nearestTri = hs;
                    }
                }
                else {
                    nearestTri = hs;
                    triFill = true;
                }
            }
        }
    }
    
    // Still need to implement
    if (trinormcount > 0) {
        for (int i = 0; i < trinormcount; i++) {
            
        }  
    }
    
    
    bool hitSomething = (hitSphere > 0 || hitTri > 0 || hitTriN > 0);
    if (!hitSomething) {
        misscount++;
        rayHit.hit = false;
        return rayHit;
    }
    
    // 0 - sphere, 1 - tri
    primFlag = Intersect::getNearestObject(nearestSphere, nearestTri);

    if (debug) {
        cout << "primFlag: " << primFlag << " \n";
        cout << "Distance of nearest sphere: " << nearestSphere.depth <<" \n";
        cout << "Distance of nearest triangle: " << nearestTri.depth <<" \n";
    }
    

    
    if (primFlag == 0) {
        spherehitcount++;
        rayHit.hit = true;
        rayHit.prim = 0;
        rayHit.shape = nearestSphere.index;
        return rayHit;
    } else {
        trihitcount++;
        rayHit.hit = true;
        rayHit.prim = 1;
        rayHit.shape = nearestTri.index;
        return rayHit;
    }
}

int Intersect::getNearestObject(hitShape s, hitShape t) {
    float sdepth = s.depth;
    float tdepth = t.depth;
    
    if (sdepth < tdepth) {
        return 0;
    } else if (tdepth < sdepth) {
        return 1;
    } else {
        tiecount++;
        return 0;
    }
}

float Intersect::getDepth(ray r, float t, glm::vec3 p) {
    float depth;
    glm::vec3 q;
    float xd, yd, zd;
    
    q = r.ori + Objects::scale(r.dir, t);
    xd = q.x - p.x;
    yd = q.y - p.y;
    zd = q.z - p.z;
    depth = sqrt(pow(xd,2) + pow(yd,2) + pow(zd,2));
}