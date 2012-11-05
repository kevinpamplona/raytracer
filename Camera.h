class Camera
{
public:
    Camera();
    virtual ~Camera();
    
    static ray shootRay(int i, int j);

};