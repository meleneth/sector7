#ifndef ___globalsinc
#define ___globalsinc 1

#include<stdlib.h>
#include<math.h>

#include"types.hpp"

#define XRES 1024
#define YRES 768

#define HALFXRES (1024/2)
#define HALFYRES (768/2)

#define true 1
#define false 0

#define PI 3.14159265

#ifndef M_PI
#define M_PI 3.14159265
#endif

Sint32 m_round(double value);

#endif
