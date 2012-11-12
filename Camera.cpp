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
    fovy = values[9];
    //fovx = fovy*((float)height/width);
    //fovx = 2*atan(tan((float)fovy/2)*((float)height/width));
    fovx = 0;
}

ray Camera::shootRay(int i, int j) {
    
    // Increments counter for how many ray's shot
    raycount += 1;
    
    ray r;
    glm::vec3 dir;
    float alpha, beta;
    //float fovx = fovy;
    //float fovx = (height/width)*fov; // not sure about this
    //float fovy = fov;
    
    /*
    cout << "FOVX: " << fovx << " ";
    cout << "FOVY: " << fovy << " \n";
    */
    
    // Do we need to convert this?
    float m = (fovx/2)/**(M_PI/180)*/;
    float n = (fovy/2)/**(M_PI/180)*/;
    float tanx = tan(m);
    float tany = tan(n);
    
    /*
    cout << "TANX: " << tanx << " ";
    cout << "TANY: " << tany << " \n";
    
    cout << "I: " << i << "\n";
    cout << "J: " << j << "\n";
    cout << "jnum: " << j-(width/2) << "\n";
    cout << "jdem: " << (width/2) << "\n";
    cout << "jfinal: " << (j-(width/2))/(width/2) << "\n";
    */
    
    float testn = j-(width/2);
    float testd = (width/2);
    float testf = ((j-(width/2))/(width/2));
    
    /*
    cout << "testn: " << j-(width/2) << "\n";
    cout << "testd: " << (width/2) << "\n";
    cout << "testf: " << testn/testd << "\n";
    */
     
    float jnum = j-(width/2);
    float jdem = width/2;
    
    float inum = (height/2)-i;
    float idem = height/2;
    
    
    float jval = jnum/jdem;
    float ival = inum/idem;
    
    /*
    cout << "JVAL: " << jval << " ";
    cout << "IVAL: " << ival << " \n";
    */
    
    alpha = tanx*jval;
    beta = tany*ival;
    
    /*
    cout << "ALPHA: " << alpha << " ";
    cout << "BETA: " << beta << " \n";
    */
    
    glm::vec3 nonorm = alpha*u + beta*v - w;
    //cout << "Before normalization: (" << nonorm.x << ", " << nonorm.y << ", " << nonorm.z << ") \n";
    
    dir = glm::normalize(alpha*u+beta*v-w);
    r.dir = dir;
    r.ori = eye;
    return r;
}

