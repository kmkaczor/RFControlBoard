// Common interface for different screens.
#ifndef _PHYK_SCREEN
#define _PHYK_SCREEN

#include <stdlib.h>
#include "kdevice.h"
#include <string>

class K_SModule : public K_Device
{
    public:
    //K_SModule();
    virtual k_err init();
    //virtual k_err end();
    //virtual int getMaxWidth();
    //virtual int getMaxHeight();
    virtual k_err print(char *);
    virtual k_err println(char *);
};

class K_TModule : public K_Device
{

};
#endif