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

// specifies the number of vertrices for tri specifications
extern maxverts;

// specifies the number of vertices with normals for tri specifications
extern maxvertnorms;

// pile of inputted vertices
extern verts[];

// pile of inputted vertices with associated normals
extern vertnorms[];


