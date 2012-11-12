class Camera
{
public:
    Camera();
    virtual ~Camera();
    
    static ray shootRay(int i, int j);
    static void initCamera(float * values);
    static void init(float * values);
};