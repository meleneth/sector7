#ifndef ___globalsinc
#define ___globalsinc 1

#include<stdlib.h>
#include<math.h>
#include"console.hpp"
#include"types.hpp"

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 31337
#endif

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

extern Console *console;
Sint32 m_round(double value);

#endif
