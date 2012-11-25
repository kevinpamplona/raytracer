#include "variables.h"
#include "ReadScene.h"
#include "Camera.h"
#include "Objects.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Intersect.h"
#include "Film.h"
#include "Paint.h"
#include "structs.h"

// width and height specify image size
int width = 0;
int height = 0;

// maximum depth for a ray (level of recursion)
int recursionDepth = 5;

// the output file to which the image should be written
string fileout = "out.txt";
bool nameGiven = false;

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

//Transformations
stack<glm::mat4> trstack;
glm::vec3 scaleV = glm::vec3(0,0,0);

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
int numLights = 0;
int shadowPixels = 0;
int reflections = 0;


//debug
int spherehitcount = 0;
int trihitcount = 0;
int misscount = 0;
int tiecount = 0;

//**************************//
//  Materials Specifiations //
//**************************//
vector<dLight> dLights;
vector<pLight> pLights;
glm::vec3 attenuation = glm::vec3(1,0,0);
glm::vec3 ambient;

//**************************//
//  Materials Specifiations //
//**************************//

glm::vec3 diffuse;
glm::vec3 specular;
float shininess = 1.0;
glm::vec3 emission;

//***************************//
//   Camera Specifications  //
//***************************//
glm::vec3 eye;
glm::vec3 center;
glm::vec3 up;
glm::vec3 w;
glm::vec3 u;
glm::vec3 v;

// FreeImage 
int BPP = 24;

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

    w = glm::normalize(a);
    u = glm::normalize(glm::cross(b,w));
    v = glm::cross(w,u);
}

void printProgress(int i, int j) {
    if (i==floor(width*0.10) && j == height-1) {
        cout << "10%...\n";
    }
    if (i==floor(width*0.20) && j == height-1) {
        cout << "20%...\n";
    }
    if (i==floor(width*0.30) && j == height-1) {
        cout << "30%...\n";
    }
    if (i==floor(width*0.40) && j == height-1) {
        cout << "40%...\n";
    }
    if (i==floor(width*0.50) && j == height-1) {
        cout << "50%...\n";
    }
    if (i==floor(width*0.60) && j == height-1) {
        cout << "60%...\n";
    }
    if (i==floor(width*0.70) && j == height-1) {
        cout << "70%...\n";
    }
    if (i==floor(width*0.80) && j == height-1) {
        cout << "80%...\n";
    }
    if (i==floor(width*0.90) && j == height-1) {
        cout << "90%...\n";
    }
}

void init() {
    cout << "\n\n************************************\n";
    cout << "Reading in scene file... \n";
    cout << "Image size has been set to a " << width << " x " << height << " output. \n";
    cout << "The maximum recursion depth has been set to " << recursionDepth << ". \n";
    cout << "The image will be output to " << fileout << ".png. \n";
    
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
    cout << "A total of " << objcount << " objects have been specified. \n";
    
    cout << "Number of lights: " << numLights << " \n\n";
}

int main (int argc, char * argv[]) {
    FreeImage_Initialise();
    ReadScene::readFile(argv[1]);
    init();
    initCamera();
    
    cout << "Creating bitmap...\n";
    int bitmap[width][height][3];
    
    cout << "Calculating all pixel values...\n";
    
    
    FIBITMAP* IMG = FreeImage_Allocate(width,height,BPP);
    RGBQUAD color;
    if (!bitmap) {
        cout << " Unable to allocate images...\n\n";
        exit(1);
    }
    
    int pw = width/2 + 110;
    int ph = height/2 - 40;
    cout << "PW: " << pw << " \n";
    cout << "PH: " << ph << " \n";

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            printProgress(i,j);
            float m = (float)i + 0.5;
            float n = (float)j - 0.5;
            ray r = Camera::shootRay(m,n);
            r.rec = 0;
            Hit hit = Intersect::hit(r, 0, 0);
            if (hit.hit) {
                hitcount += 1;
                Color col = Paint::computeColor(hit, i, j);
                float r = col.blue;
                float g = col.green;
                float b = col.red;
                color.rgbRed = r * 255.0;
                color.rgbGreen = g * 255.0;
                color.rgbBlue = b * 255.0;
                FreeImage_SetPixelColor(IMG,i,height-j,&color);               
            } else {
                bitmap[i][j][0] = 1; //blue
                bitmap[i][j][1] = 1; //green
                bitmap[i][j][2] = 1; //red
            }
       }
    }
    cout << "Raytacer has shot: " << raycount << " rays. \n\n";
    cout << "Hitcount: " << hitcount << " \n";
    cout << "Spheres hit: " << spherehitcount << " \n";
    cout << "Triangles hit: " << trihitcount << " \n";
    cout << "Missed ray: " << misscount << " \n\n";
    cout << "Ties: " << tiecount << " \n";
    cout << "Pixels in shadow: " << shadowPixels << "\n";
    cout << "Amount of reflected rays: " << reflections << "\n\n";
    FreeImage_DeInitialise();
    return 0;
}