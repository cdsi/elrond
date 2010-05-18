%module xul
%{
#include "xul.h"
%}

%include "glib.i"

#define XUL_APIEXPORT

%include "_xul.h"
