#include "Paint.h"
#include "Objects.h"
#include "Sphere.h"
#include "Intersect.h"
#include <math.h>

bool Paint::computeShadow(glm::vec3 x, glm::vec3 lp) {
    ray r = Objects::makeRay(x, lp);
    
    Hit hit = Intersect::hit(r, false);
    
    if (hit.hit) {
        //cout << "tr \n";
        return true;
    } else {
        //cout << "fa \n";
        return false;
    }
}

glm::vec3 Paint::computeLight(glm::vec3 direction, glm::vec3 lightcolor, glm::vec3 normal, glm::vec3 halfvec, glm::vec3 diffuse, glm::vec3 specular, float shininess, glm::vec3 attenuation, float r, glm::vec3 isect, bool doShadow, glm::vec3 lightpos) {
    
    // doShadow set true for point lights
    if (doShadow) {
        if (Paint::computeShadow(isect, lightpos)) {
            return glm::vec3(0,0,0);
        }
    }
    
    float nDotL = glm::dot(normal, direction);
    glm::vec3 lambert = diffuse * max((float)nDotL,(float)0);
    
    float nDotH = glm::dot(normal, halfvec);
    glm::vec3 phong = specular * pow(max((float)nDotH,(float)0.0), shininess);
    
    /*
    glm::vec3 rd = glm::vec3(1, r, r*r);
    float alpha = glm::dot(rd, attenuation);
    glm::vec3 model = Objects::scale(Objects::scale(lightcolor, 1/alpha), v);
    */
    
    glm::vec3 rd = glm::vec3(1, r, r*r);
    float alpha = rd.x*attenuation.x + rd.y*attenuation.y + rd.z*attenuation.z;
    
    if (alpha != 1) {
        cout << "Error: alpha" << alpha << " \n";;
        exit(1);
    }
    
    if (lightcolor.x != 1 || lightcolor.y != 1 || lightcolor.z != 1 ) {
        cout << "Error: lightcolors \n";;
        exit(1);
    }
    
    glm::vec3 model;
    model.x = (float)lightcolor.x / alpha;
    model.y = (float)lightcolor.y / alpha;
    model.z = (float)lightcolor.z / alpha;
    
    model = glm::clamp(model, 0.0, 1.0);
    //return model*(lambert + phong);
    //return glm::clamp(model*(lambert + phong), 0.0, 1.0);
    
    return model*(lambert + phong);
    
}


Color Paint::computeColor(Hit h) {
        
    Color out;
    glm::vec3 sum;
    glm::vec3 final;
    
    glm::vec3 myambient;
    glm::vec3 myemission;
    glm::vec3 mydiffuse;
    glm::vec3 myspecular;
    float myshininess;
    
    glm::vec3 mynormal;
    glm::vec3 isect = h.isect;     glm::vec3 raydir = h.r.dir;
    
    
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
        glm::vec3 half = glm::normalize(direction + (eye-isect));
        float r = 1;
        sum = sum + Paint::computeLight(direction, d.col, mynormal, half, mydiffuse, myspecular, myshininess, d.atten, r, isect, false, glm::vec3(0,0,0));

    }
    
    for (int j = 0; j < pLights.size(); j++) {
        pLight p = pLights[j];
                
        glm::vec3 direction = glm::normalize(p.pos - isect);
        glm::vec3 half = glm::normalize(direction + (eye-isect));
        float r = glm::distance(p.pos, isect);
        sum = sum + Paint::computeLight(direction, p.col, mynormal, half, mydiffuse, myspecular, myshininess, p.atten, r, isect, false, p.pos);
    }
    
    final = myambient + myemission + sum;
    
    final = glm::clamp(final, 0.0, 1.0);
    
    out.red = final.x;
    out.green = final.y;
    out.blue = final.z;
    return out;
}















