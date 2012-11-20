#include "variables.h"
#include "Camera.h"

// helper function to initialize camera variables
void Camera::initCamera(float * values) {
    lookfromx = values[0];
    lookfromy = values[1];
    lookfromz = values[2];
    lookatx = values[3];
    lookaty = values[4];
    lookatz = values[5];
    upx = values[6];
    upy = values[7];
    upz = values[8];
    fovy = glm::radians(values[9]);
    fovx = 2*atan(tan((float)fovy/2)*((float)width/height)); // added radians
}


ray Camera::shootRay(int i, int j) {
    
    
    raycount += 1;
    
    ray r;
    glm::vec3 r_dir;
    
    // correct
    // (width/(float)height)*
    //float alpha = tan((float)fovx/2) * ((j - ((float)width/2))/((float)width/2));
    //float beta = tan((float)fovy/2) * ((((float)height/2)-i)/((float)height/2));
    
    //chloh
    float alpha = tan((float)fovx/2) * ((i - ((float)width/2))/((float)width/2));
    float beta = tan((float)fovy/2) * ((((float)height/2)-j)/((float)height/2));
    
    //float alpha = ((float)width/height) * tan(fovx/2.0) * ( (j - (width/2.0)) / (width/2.0));
    //float beta = tan(fovy/2.0) * ( (height/2.0) - i) / (height/2.0);
    
    //aldi
    //float alpha = float(width) * tan(fovy/2)/ float(height) * (j - (width / 2.0)) / (width / 2.0);
    //float beta = tan(fovy/2) * ((height / 2.0) - i) / (height / 2.0);
        
    r_dir = glm::normalize(alpha*u + beta*v - w);
     
    r.ori = eye;
    r.dir = r_dir;
    
    cout << "\n RAY: (" << i << "," << j << ") \n";
    cout << "\t WIDTH/2: " << ((float)width/2) << " \n";
    cout << "\t HEIGHT/2: " << ((float)height/2) << " \n";
    cout << "\t alpha: " << alpha << "   beta: " << beta << " \n";
    cout << "\t RAY ORI: (" << eye.x << ", " << eye.y << ", " << eye.z << ") \n";
    cout << "\t RAY DIR: (" << r_dir.x << ", " << r_dir.y << ", " << r_dir.z << ") \n";
    
    return r;
}
