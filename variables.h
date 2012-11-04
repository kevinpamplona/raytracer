#include "vertexnormal.h"
#include "sphere.h"
#include "tri.h"
#include "trinormal.h"

#include <glm/glm.hpp>

#include <vector>

// width and height specify image size
extern width;
extern height;

// maximum depth for a ray (level of recursion)
extern depth;

// the output file to which the image should be written
extern filename;

// camera specifiations (should i put in a struct?)
extern lookfromx;
extern lookfromy;
extern lookfromz;
extern lookatx;
extern lookaty;
extern lookatz;
extern upx;
extern upy;
extern upz;
extern fov;

//***************************//
//  Geometry Specifications  //
//***************************//

// specifies the number of vertrices for tri specifications
extern maxverts;

// specifies the number of vertices with normals for tri specifications
extern maxvertnorms;

// pile of inputted vertices
// might need to #include glm file                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
extern vector<glm::vec3> vertices;

// pile of inputted vertices with specified normals
extern vector<vertexnormal> vertnormals;

// pile of inputted spheres
extern vector<sphere> spheres;

// pile of inputted triangles
extern vector<tri> triangles;

// pile of inputted triangles using vertices with specified normals 
extern vector<trinormal> trinormals;

//**************************//
//  Materials Specifiations //
//**************************//

extern float diffuse[3];
extern float specular[3];
extern float shininess;
extern float emission[3];