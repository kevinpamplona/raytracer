#include "variables.h"

class Film
{
public:
    Film();
    virtual ~Film();
    
    static void write(int change, int i, int j);
    static void output();
};