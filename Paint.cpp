#include "Paint.h"
#include "Objects.h"
#include "Sphere.h"
#include "Intersect.h"
#include <math.h>

bool Paint::computeShadow(glm::vec3 x, glm::vec3 lightdir, glm::vec3 lightpos, bool lightflag, int m, int n) {
    
    if (lightflag) {
        ray r;
        r.ori = x;
        r.dir = glm::normalize(lightdir);
        
        r.ori.x += 0.1*r.dir.x;
        r.ori.y += 0.1*r.dir.y;
        r.ori.z += 0.1*r.dir.z;
        
        Hit hit = Intersect::hit(r, m, n);
    
        if (hit.depthHit > glm::distance(x,lightpos)) {
            return false;
        }
    
        if (hit.hit) {
            shadowPixels++;
            return true;
        } else {
            return false;
        }
    } else {
        ray r;
        r.ori = x;
        r.dir = glm::normalize(lightdir);
    
        r.ori.x += 0.1*r.dir.x;
        r.ori.y += 0.1*r.dir.y;
        r.ori.z += 0.1*r.dir.z;
        
        Hit hit = Intersect::hit(r, m, n);
        
        if (hit.hit) {
            shadowPixels++;
            return true;
        } else {
            return false;
        }
    }
}

glm::vec3 Paint::computeLight(glm::vec3 direction, glm::vec3 lightcolor, glm::vec3 normal, glm::vec3 halfvec, glm::vec3 diffuse, glm::vec3 specular, float shininess,
                              glm::vec3 attenuation, float r, glm::vec3 isect, bool doShadow, glm::vec3 lightdir, glm::vec3 lightpos, int m, int n) {
    
    bool inShadow = false;
    
    // doShadow set true for point lights
    if (doShadow) {
        inShadow = Paint::computeShadow(isect, glm::normalize(lightdir), lightpos, true, m, n);
    } else {
        inShadow = Paint::computeShadow(isect, lightpos, glm::vec3(0,0,0), false, m, n);
    }
    
    float nDotL = glm::dot(normal, direction);
    glm::vec3 lambert = diffuse * max((float)nDotL,(float)0);
    
    float nDotH = glm::dot(normal, halfvec);
    glm::vec3 phong = specular * pow(max((float)nDotH,(float)0.0), shininess);

    glm::vec3 rd = glm::vec3(1, r, r*r);
    float alpha = rd.x*attenuation.x + rd.y*attenuation.y + rd.z*attenuation.z;

    glm::vec3 model;
    model.x = (float)lightcolor.x / alpha;
    model.y = (float)lightcolor.y / alpha;
    model.z = (float)lightcolor.z / alpha;
    
    model = glm::clamp(model, 0.0, 1.0);
    
    if (inShadow) {
        return glm::vec3(0,0,0);
    } else {
        return model*(lambert + phong);
    }
}


Color Paint::computeColor(Hit h, int m, int n) {
        
    Color out;
    glm::vec3 sum;
    glm::vec3 final;
    
    glm::vec3 myambient;
    glm::vec3 myemission;
    glm::vec3 mydiffuse;
    glm::vec3 myspecular;
    float myshininess;
    
    glm::vec3 mynormal;
    glm::vec3 isect = h.isect;
    glm::vec3 ssect = h.isect;
    
    ShapeW shape = Objects::makeWrapper(h);
    
    if (shape.flag) {
        
        //triangle
        myambient = shape.t.ambient;
        myemission = shape.t.emission;
        mydiffuse = shape.t.diffuse;
        myspecular = shape.t.specular;
        myshininess = shape.t.shininess;
        mynormal = shape.t.normal;
    } else {

        //sphere
        myambient = shape.s.ambient;
        myemission = shape.s.emission;
        mydiffuse = shape.s.diffuse;
        myspecular = shape.s.specular;
        myshininess = shape.s.shininess;
        mynormal = Sphere::getNormal(shape.s, h.isect);
        
        glm::vec4 temp = glm::vec4(isect, 1);
        temp = temp * shape.s.tmat;
        
        isect = glm::vec3(temp);
    }   
    
    for (int i = 0; i < dLights.size(); i++) {
        dLight d = dLights[i];
        
        glm::vec3 direction = glm::normalize(d.pos);
        glm::vec3 half = glm::normalize(direction + (h.r.ori-isect));
        float r = 1;
        sum = sum + Paint::computeLight(direction, d.col, mynormal, half, mydiffuse, myspecular, myshininess, d.atten, r,
                                        isect, false, glm::vec3(0,0,0), d.pos, m, n);

    }
    
    for (int j = 0; j < pLights.size(); j++) {
        pLight p = pLights[j];
        
        glm::vec3 direction = glm::normalize(p.pos - isect);
        glm::vec3 half = glm::normalize(direction + glm::normalize(h.r.ori-isect));
        float r = glm::distance(p.pos, isect);
        sum = sum + Paint::computeLight(direction, p.col, mynormal, half, mydiffuse, myspecular, myshininess, p.atten, r,
                                        isect, true, glm::normalize(p.pos-isect), p.pos, m, n);
        
    }
    
    // recursion
    Color refl;
    glm::vec3 reflection;
    if (myspecular.x == 0 && myspecular.y == 0 && myspecular.z == 0) {
        reflection = glm::vec3(0,0,0);
    } else {
        glm::vec3 v = glm::normalize(h.r.dir - h.r.ori);
        glm::vec3 norm = glm::normalize(mynormal);
        
        ray rf;
        rf.ori = isect;
        rf.dir = glm::normalize(v - 2*glm::dot(v,norm)*norm);

        rf.ori.x += 0.001*rf.dir.x;
        rf.ori.y += 0.001*rf.dir.y;
        rf.ori.z += 0.001*rf.dir.z;
        
        rf.rec = h.r.rec + 1;
        
        if (rf.rec <= recursionDepth) {
        
            Hit rfHit = Intersect::hit(rf, 0, 0);
        
            if (rfHit.hit) {
                reflections++;
                refl = Paint::computeColor(rfHit, 0, 0);
                reflection.x = refl.red;
                reflection.y = refl.green;
                reflection.z = refl.blue;
            } else {
                reflection = glm::vec3(0,0,0);
            }
        } else {
            reflection = glm::vec3(0,0,0);
        }
    }
    
    final = myambient + myemission + sum + myspecular*reflection;
    
    final = glm::clamp(final, 0.0, 1.0);
    
    out.red = final.x;
    out.green = final.y;
    out.blue = final.z;
    return out;
}











