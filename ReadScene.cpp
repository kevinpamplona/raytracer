#include "ReadScene.h"
#include "variables.h"
#include "Camera.h"
#include "Objects.h"
#include "Transform.h"


void matransform(stack<mat4> &transfstack, float * values) {
    mat4 transform = transfstack.top() ;
    vec4 valvec = vec4(values[0],values[1],values[2],values[3]) ;
    vec4 newval = valvec * transform ;
    for (int i = 0 ; i < 4 ; i++) values[i] = newval[i] ;
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) {
    mat4 &T = transfstack.top() ;
    T = M * T ;
}

bool ReadScene::readVals(stringstream &s, const int numvals, float * values) {
    for (int i = 0 ; i < numvals ; i++) {
        s >> values[i] ;
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n" ;
            return false ;
        }
    }
    return true ; 
}

void ReadScene::readFile(const char * filename) {
    
    string str, cmd, filen;
    ifstream in;
    in.open(filename);
    
    float values[10];
    bool validinput;
    trstack.push(mat4(1.0));
    
    if (in.is_open()) {
        
        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                
                stringstream s (str);
                s >> cmd;
                
                if (cmd == "size") {
                    validinput = readVals(s, 2, values);
                    if (validinput) {
                        width = values[0];
                        height = values[1];
                    }
                }
                else if (cmd == "maxdepth") {
                    validinput = readVals(s, 1, values);
                    if (validinput) {
                        recursionDepth = values[0];
                    }
                }
                else if (cmd == "output") {
                    s >> filen;
                    filen = s.str();
                    fileout = filen;
                    cout << fileout;
                }
                else if (cmd == "camera") {
                    validinput = readVals(s, 10, values);
                    if (validinput) {
                        Camera::initCamera(values);
                    }
                    
                }
                else if (cmd == "maxverts") {
                    validinput = readVals(s, 1, values);
                    if (validinput) {
                        maxverts = values[0];
                    }
                }
                else if (cmd == "maxvertnorms") {
                    validinput = readVals(s, 1, values);
                    if (validinput) {
                        maxvertnorms = values[0];
                    }
                }
                else if (cmd == "vertex") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        vertexcount += 1;
                        vertices.push_back(Objects::makeVertex(values));
                    }
                }
                else if (cmd == "vertexnormal") {
                    validinput = readVals(s, 6, values);
                    if (validinput) {
                        vertexnormcount += 1;
                        vertnormals.push_back(Objects::makeVertNormal(values));
                    }
                }
                else if (cmd == "sphere") {
                    validinput = readVals(s, 4, values);
                    if (validinput) {
                        objcount += 1;
                        spherecount += 1;
                        spheres.push_back(Objects::makeSphere(values));
                    }
                }
                else if (cmd == "tri") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        objcount += 1;
                        tricount += 1;
                        triangles.push_back(Objects::makeTriangle(values));
                    }
                }
                else if (cmd == "trinormal") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        objcount += 1;
                        trinormcount += 1;
                        trinormals.push_back(Objects::makeTriNormal(values));
                    }
                }
                else if (cmd == "translate") {
                    validinput = readVals(s,3,values);
                    if (validinput) {
                        glm::mat4 trans_mat = Transform::translate(values[0],values[1],values[2]);
                        rightmultiply(trans_mat,trstack);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readVals(s,4,values);
                    if (validinput) {
                        glm::vec3 axis = glm::normalize(vec3(values[0], values[1], values[2]));
                        glm::mat3 temp = Transform::rotate(values[3], axis);
                        glm::mat4 rot_mat = mat4(temp);
                        rightmultiply(rot_mat,trstack);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readVals(s,3,values);
                    if (validinput) {
                        glm::mat4 scale_mat = Transform::scale(values[0],values[1],values[2]);
                        rightmultiply(scale_mat,trstack);
                        scaleV.x = values[0];
                        scaleV.y = values[1];
                        scaleV.z = values[2];
                    } 
                }
                else if (cmd == "pushTransform") {
                    trstack.push(trstack.top());
                }
                else if (cmd == "popTransform") {
                    if (trstack.size() <= 1) {
                        cerr << "Stack has no elements.  Cannot Pop\n" ;
                    } else {
                        trstack.pop() ;
                    }
                }
                else if (cmd == "directional") {
                    validinput = readVals(s, 6, values);
                    if (validinput) {
                        numLights++;
                        dLights.push_back(Objects::makeDLight(values));
                    }
                }
                else if (cmd == "point") {
                    validinput = readVals(s, 6, values);
                    if (validinput) {
                        numLights++;
                        pLights.push_back(Objects::makePLight(values));
                    }
                }
                else if (cmd == "attenuation") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        attenuation.x = values[0];
                        attenuation.y = values[1];
                        attenuation.z = values[2];
                    }
                }
                else if (cmd == "ambient") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        ambient.x = values[0];
                        ambient.y = values[1];
                        ambient.z = values[2];
                    }
                }
                else if (cmd == "diffuse") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        diffuse.x = values[0];
                        diffuse.y = values[1];
                        diffuse.z = values[2];
                    }
                }
                else if (cmd == "specular") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        specular.x = values[0];
                        specular.y = values[1];
                        specular.z = values[2];
                    }
                }
                else if (cmd == "shininess") {
                    validinput = readVals(s, 1, values);
                    if (validinput) {
                        shininess = values[0];
                    }
                }
                else if (cmd == "emission") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        emission.x = values[0];
                        emission.y = values[1];
                        emission.z = values[2];
                    }
                }
                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }
    }
    else {
        cerr << "UNABLE TO OPEN INPUT DATA FILE: " << filename << "\n";
        throw 2;
    }
}

ReadScene::ReadScene()
{
    
}

ReadScene::~ReadScene()
{
    
}
