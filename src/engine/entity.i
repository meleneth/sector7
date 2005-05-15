%module Entity
%{
/* Includes the header in the wrapper code */
#include "entity.hpp"
%}

/* Parse the header file to generate wrappers */
%include "entity.hpp"

