#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <FreeImage.h>

#include "Objects.h"
#include "readfile.h"
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
float lookfromz = 0;
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
vector<glm::vec3> vertices;

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

void testPrint() {
    
    int width = 800;
    int height = 600;
    int BPP = 24;
    
    FIBITMAP* bitmap = FreeImage_Allocate(width,height,BPP);
    RGBQUAD color;
    
    if (!bitmap) {
        exit(1);
    }
    
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            color.rgbRed = 0;
            color.rgbGreen = (double)i / width * 255.0;
            color.rgbBlue = (double)j / height * 255.0;
            
            FreeImage_SetPixelColor(bitmap, i,j,&color);
        }
    }
    
    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0)) {
        cout << "Image successfully saved!\n";
    } else {
        cout << "Image not saved..";
    }
}

void init() {
    cout << "Reading in scene file... \n";
    cout << "Image size has been set to a " << width << " x " << height << " output. \n";
    cout << "The maximum recursion depth has been set to " << depth << ". \n";
    cout << "The image will be output to " << filename << ".png. \n";
    
    cout << "The camera has been instantiated with the following properties: \n";
    cout << "\t POSITION: (" << lookfromx << ", " << lookfromy << ", " << lookfromz << ") \n";
    cout << "\t DIRECTION: (" << lookatx << ", " << lookaty << ", " << lookatz << ") \n";
    cout << "\t UP: (" << upx << ", " << upy << ", " << upz << ") \n";
    cout << "\t FIELD OF VIEW: " << fov << " \n";
    
    cout << "An amount of " << vertexcount << " vertices has been specified with a maximum of " << maxverts << " allowed. \n";
    cout << "An amount of " << vertexnormcount << " vertices with normals has been specified with a maximum of " << maxvertnorms << " allowed. \n"; 
    
    cout << "An amount of " << spherecount << " spheres have been specified. \n";
    cout << "An amount of " << tricount << " triangles have been specified. \n";
    cout << "An amount of " << trinormcount << " triangles with calculated vertex normals have been specified. \n\n";
}


int main (int argc, char * argv[]) {
    FreeImage_Initialise();
    readFile(argv[1]);
    init();
    
    cout << "FreeImage " << FreeImage_GetVersion() << "\n";
    cout << FreeImage_GetCopyrightMessage() << "\n\n";
    testPrint();
    FreeImage_DeInitialise();
    return 0;
}