#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "readfile.h"
#include "variables.h"
#include "Objects.h"

void init() {
    readFile(argv[1]);
    
    cout << "Reading in scene file... \n";
    cout << "Image size has been set to a " << width << " x " << height << " output. /n";
    cout << "The maximum recursion depth has been set to " << depth << ". \n";
    cout << "The image will be output to " << output << ".png. \n";
    
    cout << "The camera has been instantiated with the following properties: \n";
    cout << "\t POSITION: (" << lookfromx << ", " << lookfromy << ", " << lookfromz << ") \n";
    cout << "\t DIRECTION: (" << lookatx << ", " << lookaty << ", " << lookatz << ") \n";
    cout << "\t UP: (" << upx << ", " << upy << ", " << upz << ") \n";
    cout << "\t FIELD OF VIEW: " << fov << " \n";
    
    cout << "An amount of " << vertexcount << " vertices has been specified with a maximum of " << maxverts << " allowed. \n";
    cout << "An amount of " << vertexnormcount << " vertices with normals has been specified with a maximum of " << maxvertnorms << " allowed. \n"; 
    
    cout << "An amount of " << spherecount << " spheres have been specified. \n";
    cout << "An amount of " << tricount << " triangles have been specified. \n";
    cout << "An amount of " << trinormcount << " triangles with calculated vertex normals have been specified. \n";
}


int main (int argc, char * argv[]) {
    init();
    return 0;
}