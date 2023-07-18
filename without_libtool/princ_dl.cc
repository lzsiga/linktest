/* princ_dl.cc */

#include <cstdio>

#include "princ_dl.h"

extern "C" {
Princ *Princ_Create  (const char *name) { return new Princ(name); }
void   Princ_Intro   (const Princ *self) { self->intro(); }
void   Princ_Destroy (Princ *self) { delete self; }
}
