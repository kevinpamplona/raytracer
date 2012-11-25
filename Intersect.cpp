#include "Intersect.h"
#include "Objects.h"
#include "variables.h"
#include "structs.h"
#include "Sphere.h"
#include "Triangle.h"

Hit Intersect::hit(ray r, int m, int n) {
    
    bool shadow = false;
    
    Hit rayHit;
    rayHit.r = r;
    
    int hitSphere = 0;
    int hitTri = 0;
    int hitTriN = 0;
    
    int triIndex = 0;
    int sphereIndex = 0;
    
    hitShape nearestSphere;
    nearestSphere.depth = INT_MAX;
    bool sphereFill = false;
    
    
    hitShape nearestTri;
    nearestTri.depth = INT_MAX;
    bool triFill = false;
    
    int primFlag;
    
    if (spherecount > 0) {
        for (int i = 0; i < spherecount; i++) {
            hitShape hs;
            hs.hit = false;
            hs.index = i;
            sphere s = spheres[i];
            hs = Sphere::intersect(s,r);
            if (hs.hit) {
                hitSphere++;
                if (sphereFill) {
                    if (hs.depth < nearestSphere.depth) {
                        sphereIndex = i;
                        nearestSphere = hs;
                    }
                }
                else {
                    nearestSphere = hs;
                    sphereIndex = i;
                    sphereFill = true;
                }
            }
        }
    }
    
    if (tricount > 0) {
        for (int i = 0; i < tricount; i++) {
            hitShape hs;
            hs.hit = false;
            tri t = triangles[i];
            hs = Triangle::intersect(t,r);
            if (hs.hit) {
                hitTri++;
                if (triFill) {
                    if (hs.depth < nearestTri.depth) {
                        triIndex = i;
                        nearestTri = hs;
                    }
                }
                else {
                    nearestTri = hs;
                    triIndex = i;
                    triFill = true;
                }
            }
        }
    }
    
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

    if (primFlag == 0) {
        spherehitcount++;
        rayHit.hit = true;
        rayHit.prim = 0;
        rayHit.isect = nearestSphere.isect;
        rayHit.shape = sphereIndex;
        rayHit.depthHit = nearestSphere.depth;
        return rayHit;
    } else {
        trihitcount++;
        rayHit.hit = true;
        rayHit.prim = 1;
        rayHit.isect = nearestTri.isect;
        rayHit.shape = triIndex;
        rayHit.depthHit = nearestTri.depth;
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