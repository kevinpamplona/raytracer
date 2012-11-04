#include "vertexnormal.h"
#include "sphere.h"
#include "tri.h"
#include "trinormal.h"
#include "vec.h"

#include <string>
#include <vector>

using namespace std;

// width and height specify image size
float width;
float height;

// maximum depth for a ray (level of recursion)
int depth;

// the output file to which the image should be written
string filename;

// camera specifiations (should i put in a struct?)
float lookfromx;
float lookfromy;
float lookfromz;
float lookatx;
float lookaty;
float lookatz;
float upx;
float upy;
float upz;
float fov;

//***************************//
//  Geometry Specifications  //
//***************************//

// specifies the number of vertrices for tri specifications
 int maxverts;

// specifies the number of vertices with normals for tri specifications
 int maxvertnorms;

// pile of inputted vertices
// might need to #include glm file                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
vector<vec> vertices;

// pile of inputted vertices with specified normals
vector<vertexNormal> vertnormals;

// pile of inputted spheres
vector<sphere> spheres;

// pile of inputted triangles
vector<tri> triangles;

// pile of inputted triangles using vertices with specified normals 
vector<triNormal> trinormals;

int vertexcount;
int vertexnormcount;
int spherecount;
int tricount;
int trinormcount;

//**************************//
//  Materials Specifiations //
//**************************//

float diffuse[3];
float specular[3];
float shininess;
float emission[3];

