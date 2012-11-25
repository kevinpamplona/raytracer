class Camera
{
public:
    Camera();
    virtual ~Camera();
    static ray shootRay(float i, float j);
    static void initCamera(float * values);
    static void init(float * values);
};