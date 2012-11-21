#include "variables.h"
#include "ReadScene.h"
#include "Camera.h"
#include "Objects.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersect.h"
#include "Film.h"
#include "structs.h"

// width and height specify image size
int width = 0;
int height = 0;

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
float fovx = 0;
float fovy = 0;

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
int raycount = 0;
int objcount = 0;
int hitcount = 0;

//debug
int spherehitcount = 0;
int trihitcount = 0;
int misscount = 0;
int tiecount = 0;

//**************************//
//  Materials Specifiations //
//**************************//

float diffuse[3];
float specular[3];
float shininess;
float emission[3];

//***************************//
//   Camera Specifications  //
//***************************//
glm::vec3 eye;
glm::vec3 center;
glm::vec3 up;
glm::vec3 w;
glm::vec3 u;
glm::vec3 v;

//
int BPP = 24;

void printVector(glm::vec3 v) {
    cout << "(" << v.x << ", " << v.y << ", " << v.z << ") \n";
}

void initCamera() {
    eye.x = lookfromx;
    eye.y = lookfromy;
    eye.z = lookfromz;
    
    center.x = lookatx;
    center.y = lookaty;
    center.z = lookatz;
    
    up.x = upx;
    up.y = upy;
    up.z = upz;
    
    glm::vec3 a = eye-center;
    glm::vec3 b = up;
    
    cout << "\t a vector: "; printVector(a);
    cout << "\t b vector: "; printVector(b);
    
    w = glm::normalize(a);
    u = glm::normalize(glm::cross(b,w));
    v = glm::cross(w,u);
    
    cout << "The constructed coordinate frame: \n";

    cout << "\t W vector: "; printVector(w);
    cout << "\t U vector: "; printVector(u);
    cout << "\t V vector: "; printVector(v);
    
}

 
// Test function to make sure FreeImage has been imported correctly
void testPrint() {

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
            
            FreeImage_SetPixelColor(bitmap,i,j,&color);
        }
    }
    
    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0)) {
        cout << "Image successfully saved!\n";
    } else {
        cout << "Image not saved..";    
    }
}

void init() {
    cout << "\n\n************************************\n";
    cout << "Reading in scene file... \n";
    cout << "Image size has been set to a " << width << " x " << height << " output. \n";
    cout << "The maximum recursion depth has been set to " << depth << ". \n";
    cout << "The image will be output to " << filename << ".png. \n";
    
    cout << "The camera has been instantiated with the following properties: \n";
    cout << "\t POSITION: (" << lookfromx << ", " << lookfromy << ", " << lookfromz << ") \n";
    cout << "\t DIRECTION: (" << lookatx << ", " << lookaty << ", " << lookatz << ") \n";
    cout << "\t UP: (" << upx << ", " << upy << ", " << upz << ") \n";
    cout << "\t FIELD OF VIEW (X): " << fovx << " \n\n";
    cout << "\t FIELD OF VIEW (Y): " << fovy << " \n\n";
    
    cout << "An amount of " << vertexcount << " vertices has been specified with a maximum of " << maxverts << " allowed. \n";
    cout << "An amount of " << vertexnormcount << " vertices with normals has been specified with a maximum of " << maxvertnorms << " allowed. \n"; 
    
    cout << "An amount of " << spherecount << " spheres have been specified. \n";
    cout << "An amount of " << tricount << " triangles have been specified. \n";
    cout << "An amount of " << trinormcount << " triangles with calculated vertex normals have been specified. \n";
    cout << "A total of " << objcount << " objects have been specified. \n\n";
}

int testRayDir() {
    
    int i = 0;
    int j = 0;
    
    cout << "The camera has been instantiated with the following properties: \n";
    cout << "\t POSITION: (" << lookfromx << ", " << lookfromy << ", " << lookfromz << ") \n";
    cout << "\t DIRECTION: (" << lookatx << ", " << lookaty << ", " << lookatz << ") \n";
    cout << "\t UP: (" << upx << ", " << upy << ", " << upz << ") \n";
    cout << "\t FIELD OF VIEW (Y): " << fovy << " \n\n\n\n\n";
    
    cout << "Calculating coordinate frame... \n";
    glm::vec3 a = eye-center;
    glm::vec3 b = up;
    
    cout << "\t a vector: "; printVector(a);
    cout << "\t b vector: "; printVector(b);
    
    w = glm::normalize(a);
    u = glm::normalize(glm::cross(b,w));
    v = glm::cross(w,u);
    
    cout << "The constructed coordinate frame: \n";
    
    cout << "\t W vector: "; printVector(w);
    cout << "\t U vector: "; printVector(u);
    cout << "\t V vector: "; printVector(v);
    
    cout << "Testing ray at: " << i << " " << j << "\n";
    ray r = Camera::shootRay(i,j);

    cout << "\t RAY ORIGIN: "; printVector(r.ori);
    cout << "\t RAY DIR: "; printVector(r.dir);
}


int main (int argc, char * argv[]) {
    FreeImage_Initialise();
    ReadScene::readFile(argv[1]);
    init();
    initCamera();
    
    cout << "Creating bitmap...\n";
    int bitmap[width][height][3];
    
    cout << "Calculating all pixel values...\n";
    
    int pw = width/2;
    int ph = height/2-12;
    bool debug = false;
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == pw && j == ph) {
                debug = true;
            }
            ray r = Camera::shootRay(i,j);
            Hit hit = Intersect::hit(r, debug);
            debug = false;
            if (hit.hit) {
                hitcount += 1;
                
                if (hit.prim == 0) {
                    bitmap[i][j][0] = 1;
                    bitmap[i][j][1] = 1;
                    bitmap[i][j][2] = 0;
                } else if (hit.prim == 1) {
                    bitmap[i][j][0] = 1;
                    bitmap[i][j][1] = 0;
                    bitmap[i][j][2] = 0;
                }
            } else {
                bitmap[i][j][0] = 0;
                bitmap[i][j][1] = 0;
                bitmap[i][j][2] = 0;
            }
       }
    }
    
    bitmap[pw][ph][0] = 0;
    bitmap[pw][ph][1] = 0;
    bitmap[pw][ph][2] = 1;
    
    cout << "Raytacer has shot: " << raycount << " rays. \n\n";
    cout << "Hitcount: " << hitcount << " \n";
    cout << "Spheres hit: " << spherehitcount << " \n";
    cout << "Triangles hit: " << trihitcount << " \n";
    cout << "Missed ray: " << misscount << " \n\n";
    cout << "Ties: " << tiecount << " \n\n";

    
    FIBITMAP* IMG = FreeImage_Allocate(width,height,BPP);
    RGBQUAD color;
    if (!bitmap) {
        cout << " Unable to allocate images...\n\n";
        exit(1);
    }
    
    
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            float r = bitmap[i][j][0];
            float g = bitmap[i][j][1];
            float b = bitmap[i][j][2];
            
            color.rgbRed = r * 255.0;
            color.rgbGreen = g * 255.0;
            color.rgbBlue = b * 255.0;
                        
            FreeImage_SetPixelColor(IMG,i,height-j,&color);
        }
    }
    
    if (FreeImage_Save(FIF_PNG, IMG, "test.png", 0)) {
        cout << "Image successfully saved!\n\n\n";
    } else {
        cout << "Image not saved..";
    }
    
    cout << "FreeImage " << FreeImage_GetVersion() << "\n";
    cout << FreeImage_GetCopyrightMessage() << ".\n\n";
    FreeImage_DeInitialise();
    return 0;
}