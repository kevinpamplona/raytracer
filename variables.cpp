#include "variables.h"

using namespace std;

// width and height specify image size
float width = 0;
float height = 0;

// maximum depth for a ray (level of recursion)
int depth = 5;

// the output file to which the image should be written
string filename = "output";

// camera specifiations (should i put in a struct?)
float lookfromx = 0;
float lookfromy = 0;
float lookfromz= 0;
float lookatx = 0;
float lookaty = 0;
float lookatz = 0;
float upx = 0;
float upy = 0;
float upz = 0;
float fov = 0;

//***************************//
//  Geometry Specifications  //
//***************************//

// specifies the number of vertrices for tri specifications
int maxverts = 0;

// specifies the number of vertices with normals for tri specifications
int maxvertnorms = 0;

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

int vertexcount = 0;
int vertexnormcount = 0;
int spherecount = 0;
int tricount = 0;
int trinormcount = 0;

//**************************//
//  Materials Specifiations //
//**************************//

float diffuse[3];
float specular[3];
float shininess;
float emission[3];


