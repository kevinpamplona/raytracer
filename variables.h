#include <FreeImage.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <climits>
#include "structs.h"

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

// width and height specify image size
extern int width;
extern int height;

// maximum depth for a ray (level of recursion)
extern int depth;

// the output file to which the image should be written
extern string filename;

// camera specifiations (should i put in a struct?)
extern float lookfromx;
extern float lookfromy;
extern float lookfromz;
extern float lookatx;
extern float lookaty;
extern float lookatz;
extern float upx;
extern float upy;
extern float upz;
extern float fovy;
extern float fovx;

extern glm::vec3 eye;
extern glm::vec3 center;
extern glm::vec3 up;
extern glm::vec3 w;
extern glm::vec3 u;
extern glm::vec3 v;

//***************************//
//  Geometry Specifications  //
//***************************//

// specifies the number of vertrices for tri specifications
extern int maxverts;

// specifies the number of vertices with normals for tri specifications
extern int maxvertnorms;

// pile of inputted vertices
// might need to #include glm file                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
extern vector<glm::vec3> vertices;

// pile of inputted vertices with specified normals
extern vector<vertexNormal> vertnormals;

// pile of inputted spheres
extern vector<sphere> spheres;

// pile of inputted triangles
extern vector<tri> triangles;

// pile of inputted triangles using vertices with specified normals 
extern vector<triNormal> trinormals;

extern int vertexcount;
extern int vertexnormcount;
extern int spherecount;
extern int tricount;
extern int trinormcount;
extern int raycount;
extern int objcount;
extern int hitcount;
extern int tiecount;

//debug
extern int spherehitcount;
extern int trihitcount;
extern int misscount;

//**************************//
//  Materials Specifiations //
//**************************//

extern float diffuse[3];
extern float specular[3];
extern float shininess;
extern float emission[3];

//**************************//
//    Final Output Image    //
//**************************//

extern vector<glm::vec3> image;

#endif

