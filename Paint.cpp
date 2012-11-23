#include "Paint.h"
#include "Objects.h"
#include "Sphere.h"
#include "Intersect.h"
#include <math.h>

//width 165, height 200 --> should not be shaded
//width 235, height 183 --> should be shaded
//width 275, height 145 -->should NOT BE SHADED

// dir light: W 190  H 335

bool Paint::computeShadow(glm::vec3 x, glm::vec3 lightdir, glm::vec3 lightpos, bool lightflag, int m, int n) {
    
    if (lightflag) {
        ray r;
        r.ori = x;
        r.dir = glm::normalize(lightdir);

        //adjusting ray
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
        
        if (m == 190 && n == 335) {
            //cout << "INTERSECTION: (" << x.x << ", " << x.y << ", " << x.z << ") \n";
            //cout << "DIRECTION TO LIGHT: (" << lightdir.x << ", " << lightdir.y << ", " << lightdir.z << ") \n";
        }
        
        r.ori.x += 0.1*r.dir.x;
        r.ori.y += 0.1*r.dir.y;
        r.ori.z += 0.1*r.dir.z;
        
        if (m == 190 && n == 335) {
            //cout << "RORI: (" << r.ori.x << ", " << r.ori.y << ", " << r.ori.z << ") \n";
            //cout << "RDIR: (" << r.dir.x << ", " << r.dir.y << ", " << r.dir.z << ") \n";
        }
        
        Hit hit = Intersect::hit(r, m, n);
        
        if (hit.hit) {
            if (m == 190 && n == 335) {
                //cout << "DIR LIGHT SHOULD SHADE!\n";
            }
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
        if (m == 190 && n == 335) {
            //cout << "Shooting hot pixel\n";
        }
        inShadow = Paint::computeShadow(isect, lightpos, glm::vec3(0,0,0), false, m, n);
    }
    
    float nDotL = glm::dot(normal, direction);
    glm::vec3 lambert = diffuse * max((float)nDotL,(float)0);
    
    float nDotH = glm::dot(normal, halfvec);
    glm::vec3 phong = specular * pow(max((float)nDotH,(float)0.0), shininess);

    glm::vec3 rd = glm::vec3(1, r, r*r);
    float alpha = rd.x*attenuation.x + rd.y*attenuation.y + rd.z*attenuation.z;
    
   // if (alpha != 1) {
   //     cout << "Error: alpha" << alpha << " \n";;
   //     exit(1);
   // }
    
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
    
    bool debug = false;
    
    if (m == 190 && n == 335) {
        debug = true;
        //cout << "DEBUG\n";
    }
    
    if (debug) {
        if (m != 190 && n != 335) {
            cout << "SHOULD NOT BE TRUE\n";
            exit(1);
        }
    }
        
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
    
    ShapeW shape = Objects::makeWrapper(h);
    
    if (shape.flag) {
        
        //if (debug) {
        //    cout << "ERROR: SHOULD NOT BE TRIANGLE\n";
        //    exit(1);
        //}
        
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
    
        //cout << dLights.size();
        
        glm::vec3 direction = glm::normalize(d.pos);
        glm::vec3 half = glm::normalize(direction + (eye-isect));
        float r = 1;
        sum = sum + Paint::computeLight(direction, d.col, mynormal, half, mydiffuse, myspecular, myshininess, d.atten, r,
                                        isect, false, glm::vec3(0,0,0), d.pos, m, n);

    }
    
    for (int j = 0; j < pLights.size(); j++) {
        pLight p = pLights[j];
                
        glm::vec3 direction = glm::normalize(p.pos - isect);
        glm::vec3 half = glm::normalize(direction + (eye-isect));
        float r = glm::distance(p.pos, isect);
        sum = sum + Paint::computeLight(direction, p.col, mynormal, half, mydiffuse, myspecular, myshininess, p.atten, r,
                                        isect, true, glm::normalize(p.pos-isect), p.pos, m, n);
    }
    
    final = myambient + myemission + sum;
    
    final = glm::clamp(final, 0.0, 1.0);
    
    out.red = final.x;
    out.green = final.y;
    out.blue = final.z;
    return out;
}















