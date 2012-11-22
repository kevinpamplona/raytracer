// Transform.cpp: implementation of the Transform class.


#include "Transform.h"


// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.  
  float rad = 0.0174532925*degrees;
  float cosine = cos(rad);
  float sine = sin(rad);
  mat3 firstMatrix = mat3(cosine);
  mat3 secondMatrix = mat3(0, -axis[2], axis[1],
			   axis[2], 0, -axis[0],
			   -axis[1], axis[0], 0);
  secondMatrix = sine*secondMatrix;
  float x = axis[0]; float y = axis[1]; float z = axis[2];
  mat3 thirdMatrix  = mat3(x*x, x*y, x*z,
			   x*y, y*y, y*z,
			   x*z, y*z, z*z);
  thirdMatrix = (1-cosine)*thirdMatrix;
  mat3 ret = firstMatrix+secondMatrix+thirdMatrix;
  ret[0] = glm::normalize(ret[0]);
  ret[1] = glm::normalize(ret[1]);
  ret[2] = glm::normalize(ret[2]);
  return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
  mat3 rotMat = Transform::rotate(degrees, up);
  eye = eye*rotMat;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.  
  vec3 neww = glm::normalize(glm::cross(up, eye));
  eye = eye*rotate(-degrees, neww);
  up = up*rotate(-degrees, neww);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
  //float x = -eye.x;float  y=-eye.y;float  z=-eye.z;
  vec3 w = glm::normalize(eye-center);
  vec3 u = glm::cross(up,w);
  u = glm::normalize(u);
  vec3 v = glm::cross(w,u);
  mat4 R(u[0], u[1], u[2], 0,
	 v[0], v[1], v[2], 0,
	 w[0], w[1], w[2], 0,
	 0,0,0,1);
  mat4 T(1,0,0,-eye[0],
	 0,1,0,-eye[1],
	 0,0,1,-eye[2],
	 0,0,0,1);
  mat4 M = T * R;
  return M;
  
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  
  float d = 1/tan(glm::radians(fovy)/2.0);
  mat4 ret = mat4(1.0);
  ret[0][0] = d/aspect;
  ret[1][1] = d;
  ret[2][2] = -(zNear+zFar)/(zFar-zNear);
  ret[2][3] = -(2.0*zNear*zFar)/(zFar-zNear);
  ret[3][2] = -1;
  ret[3][3] = 0;
  return ret;//should be row maj
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 

  mat4 ret = mat4(1.0);
  ret[0][0] = sx;
  ret[1][1] = sy;
  ret[2][2] = sz;

  //returns row-major translation matrix
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
  // YOUR CODE FOR HW2 HERE
  // Implement translation 
  mat4 ret = mat4(1.0);
  ret[0][3] = tx;
  ret[1][3] = ty;
  ret[2][3] = tz;

  //returns row-major translation matrix
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
  vec3 x = glm::cross(up,zvec) ; 
  vec3 y = glm::cross(zvec,x) ; 
  vec3 ret = glm::normalize(y) ; 
  return ret ; 
}

 
vec3 Transform::scalevec(const vec3 &v, const float s){
  return vec3(v.x*s,v.y*s,v.z*s);
}

mat4 Transform::homrot(const mat3 &m){
  mat4 ret = mat4(1.0);
  int i, j;
  for (int i =0; i<3; i++){
    for (int j =0; j<3; j++){
      ret[i][j]=m[i][j];
    }
  }
  return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
