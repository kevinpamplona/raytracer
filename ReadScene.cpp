#include "ReadScene.h"
#include "variables.h"
#include "Camera.h"
#include "Objects.h"
// helper function to read input data files
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
    
    string str, cmd;
    ifstream in;
    in.open(filename);
    
    float values[10];
    bool validinput;
    
    if (in.is_open()) {
        
        getline(in, str);
        while (in) {
            //cout << "Reading current line: [" << str << "] \n";
            //cout << "First character in the string is: " << str[0] << " \n";
            // following if-statement ignores comments and blank lines
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                
                stringstream s (str);
                s >> cmd;
                                 
                
                // GENERAL commands
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
                        depth = values[0];
                    }
                }
                else if (cmd == "output") {
                        //s >> filename;
                        //set prior default, update if necessary
                    }
                // EO GENERAL commands
                
                // CAMERA command
                else if (cmd == "camera") {
                    validinput = readVals(s, 10, values);
                    if (validinput) {
                        Camera::initCamera(values);
                    }
                    
                }
                // EO CAMERA command
                
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
                
                else if (cmd == "translate") {}
                else if (cmd == "rotate") {}
                else if (cmd == "scale") {}
                
                else if (cmd == "pushTransform") {}
                else if (cmd == "popTransform") {}
                
                else if (cmd == "directional") {}
                else if (cmd == "point") {}
                else if (cmd == "attenuation") {}
                else if (cmd == "ambient") {}
                
                else if (cmd == "diffuse") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        for (int i=0; i<3; i++) {
                            diffuse[i] = values[i];
                        }
                    }
                }
                else if (cmd == "specular") {
                    validinput = readVals(s, 3, values);
                    if (validinput) {
                        for (int i=0; i<3; i++) {
                            specular[i] = values[i];
                        }
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
                        for (int i=0; i<3; i++) {
                            emission[i] = values[i];
                        }
                    }
                }
                else {
                    cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
            //cout << "Reading current line: [" << str << "] \n";
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