#include "variables.h"

class ReadScene
{
public:
    ReadScene();
    virtual ~ReadScene();
    static bool readVals (std::stringstream &s, const int numvals, float * values);
    static void initCamera (float * values);
    static void readFile (const char * filename);
};